/*
 * @file       system_init.c   
 * @author     DLSZ
 * @date       2018-01-13
 */
#include "include.h"
#include "common.h"
/////////////////////////////////  ������   ////////////////////////////////////
uint8 imgbuff[CAMERA_SIZE];               // ����洢����ͼ�������
uint8 system_flag=0;

/////////////////////////////////  ������   ////////////////////////////////////
void sys_init(void);                     // ϵͳ��ʼ��
void motor_init();                      // �����ʼ��
void parameter_init();                 // ������ʼ��   

/*******************************************************************************
* Function Name: sys_init();
* Description  : ϵͳ��ʼ��
* Author Data  : 2018/1/13
*******************************************************************************/
void sys_init(void)
{
    Site_t site  = {2, 2};                  //��ʾͼ�����Ͻ�λ��                
    
/************************       ���� K60 �����ȼ�        ***********************/
    NVIC_SetPriorityGrouping(6);            //�������ȼ�����,4bit ��ռ���ȼ�,û�������ȼ�    ����ͷ���ж���ߣ�pit��֮��dma��֮
    NVIC_SetPriority(PORTA_IRQn,0);         //�������ȼ�     ����ͷ���жϺͳ��ж�
    NVIC_SetPriority(DMA0_IRQn ,1);          //�������ȼ�     ����ͷ���ݴ���
    NVIC_SetPriority(PIT2_IRQn ,2);          //�������ȼ�     ���߶�ʱ   
    NVIC_SetPriority(PIT0_IRQn ,3);          //�������ȼ�     �����ж�
    NVIC_SetPriority(UART4_RX_TX_IRQn,4);   //���ڽ����ж� 
  
/******************************  LCD Һ���� ��ʼ��  ****************************/ 
    
    LCD_init();    
    
    led_init (LED0);
    led_init (LED1);
    led_init (LED2);
    led_init (LED3);
    gpio_init (PTE11, GPO,1);           //�������ܽų�ʼ��
    gpio_init (PTE2, GPO,1); 
    gpio_init (PTE3, GPO,1);
    gpio_init (PTE4, GPO,1);
    gpio_init (PTE5, GPO,1);   
    gpio_init (boma1,GPI,0);          //��ʼ�����뿪�� 
    gpio_init (boma2,GPI,0);          //��ʼ�����뿪�� 
    gpio_init (boma3,GPI,0);          //��ʼ�����뿪�� 
    gpio_init (boma4,GPI,0);          //��ʼ�����뿪��     
/******************************  LCD   ͼƬ  ��ʼ�� ****************************/       
    bmp_init();
    bmp_display();
       
/******************************  ���  ���   ��ʼ�� ***************************/
    LCD_str(site,"servo_init...", BLACK,WHITE);
    ftm_pwm_init(S3010_FTM, S3010_CH,S3010_HZ,servo_mid);   // ���

    LCD_str(site,"motor_init...", BLACK,WHITE);
    motor_init(); // ���
/****************************    ��������ʼ��     ******************************/
    LCD_str(site,"encoder_init...", BLACK,WHITE);
    ftm_quad_init(FTM1);
    ftm_quad_init(FTM2);  
/*******************       ���뿪�ء������� ��ʼ��     *************************/    
    LCD_str(site,"dial_s_init...", BLACK,WHITE);  //���뿪�س�ʼ��
    
    LCD_str(site,"buzzer_init...", BLACK,WHITE);
  
/******************************  ����ͷ   ��ʼ��  ******************************/    
    LCD_str   (site,"Cam init ing",FCOLOUR,BCOLOUR);
    camera_init(imgbuff);                             // ����ͷ��ʼ�����ɼ���imgbuff
    LCD_str   (site,"Cam init OK!",FCOLOUR,BCOLOUR);
    
/******************************  AD�ɼ�   ��ʼ��  ******************************/   
    adc_init (ELEC_L);
    adc_init (ELEC_R);
    
/***********************   ������Ϣ ��ʼ��    **********************************/
    LCD_str(site,"key_init....", BLACK,WHITE);
    key_event_init();
    pit_init_ms(PIT0,10);                                               //pit ��ʱ�ж�(���ڰ�����ʱɨ��)
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);                  //���� PIT0 ���жϷ�����Ϊ PIT0_IRQHandler
    enable_irq(PIT0_IRQn);
    
/*****************************       PIT��ʱ        ****************************/
    LCD_str(site,"time_init...", BLACK,WHITE);
    pit_init_ms(PIT2,1);       //pit2 ��ʱ�жϣ����߶�ʱ
    set_vector_handler(PIT2_VECTORn ,PIT2_IRQHandler);                 //���� PIT2 ���жϷ�����Ϊ PIT2_IRQHandler
    enable_irq(PIT2_IRQn);

/******************************  �����жϷ�����  *****************************/ 

    set_vector_handler(PORTA_VECTORn , PORTA_IRQHandler);    //���� PORTA ���жϷ�����Ϊ PORTA_IRQHandler
    set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);     //���� DMA0 ���жϷ�����Ϊ PORTA_IRQHandler 
         
    set_vector_handler(PORTB_VECTORn , portb_handler);                  //���������ⲿ�жϷ�����Ϊportb_handler
    
    uart_init (UART4, 9600);        //��ʼ������4��������Ϊ115200
    set_vector_handler(UART4_RX_TX_VECTORn,UART_interrupt);               //���ô��ڽ����жϺ���   
    uart_rx_irq_en(UART4);                                  //�����ڽ����ж�
    
    parameter_init(); 
    LCD_clear(BLACK);       
 }

/*******************************************************************************
* Function Name: motor_init();
* Description  : �����ʼ��
* Author Data  : 2018/1/21
*******************************************************************************/ 
void motor_init()
{
    ftm_pwm_init(MOTOR_FTM, MOTOR_L_Q,MOTOR_HZ,0);     // ����ǰ
    ftm_pwm_init(MOTOR_FTM, MOTOR_L_H,MOTOR_HZ,0);     // ������
    ftm_pwm_init(MOTOR_FTM, MOTOR_R_Q,MOTOR_HZ,0);     // �ҵ��ǰ
    ftm_pwm_init(MOTOR_FTM, MOTOR_R_H,MOTOR_HZ,0);     // �ҵ����
}
/*******************************************************************************
* Function Name: parameter_init();
* Description  : ������ʼ��
* Author Data  : 2018/4/13
*******************************************************************************/ 
void parameter_init()
{
  gpio_set (PTE2,gpio_get(boma1));
  gpio_set (PTE4,gpio_get(boma2));
  gpio_set (PTE3,gpio_get(boma3));
  gpio_set (PTE5,gpio_get(boma4));
  
  if(gpio_get(boma1)==0)
    jiasu=5;
  if(gpio_get(boma2)==0)
    jiasu=10;
  if(gpio_get(boma3)==0)
    roundo_jiasu=5;
  if(gpio_get(boma4)==1)
  {
    speedmax=45;
    speedmax2=45;
  }
  
  roundo_jiansu=10+jiasu;
  flash_init();//flash��ʼ��
  read_flash();//��ȡflash�洢�Ĳ���
}

 
