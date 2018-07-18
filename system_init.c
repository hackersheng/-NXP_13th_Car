/*
 * @file       system_init.c   
 * @author     DLSZ
 * @date       2018-01-13
 */
#include "include.h"
#include "common.h"
/////////////////////////////////  变量表   ////////////////////////////////////
uint8 imgbuff[CAMERA_SIZE];               // 定义存储接收图像的数组
uint8 system_flag=0;

/////////////////////////////////  函数表   ////////////////////////////////////
void sys_init(void);                     // 系统初始化
void motor_init();                      // 电机初始化
void parameter_init();                 // 参数初始化   

/*******************************************************************************
* Function Name: sys_init();
* Description  : 系统初始化
* Author Data  : 2018/1/13
*******************************************************************************/
void sys_init(void)
{
    Site_t site  = {2, 2};                  //显示图像左上角位置                
    
/************************       配置 K60 的优先级        ***********************/
    NVIC_SetPriorityGrouping(6);            //设置优先级分组,4bit 抢占优先级,没有亚优先级    摄像头场中断最高，pit次之，dma次之
    NVIC_SetPriority(PORTA_IRQn,0);         //配置优先级     摄像头行中断和场中断
    NVIC_SetPriority(DMA0_IRQn ,1);          //配置优先级     摄像头数据传输
    NVIC_SetPriority(PIT2_IRQn ,2);          //配置优先级     总线定时   
    NVIC_SetPriority(PIT0_IRQn ,3);          //配置优先级     按键中断
    NVIC_SetPriority(UART4_RX_TX_IRQn,4);   //串口接收中断 
  
/******************************  LCD 液晶屏 初始化  ****************************/ 
    
    LCD_init();    
    
    led_init (LED0);
    led_init (LED1);
    led_init (LED2);
    led_init (LED3);
    gpio_init (PTE11, GPO,1);           //蜂鸣器管脚初始化
    gpio_init (PTE2, GPO,1); 
    gpio_init (PTE3, GPO,1);
    gpio_init (PTE4, GPO,1);
    gpio_init (PTE5, GPO,1);   
    gpio_init (boma1,GPI,0);          //初始化拨码开关 
    gpio_init (boma2,GPI,0);          //初始化拨码开关 
    gpio_init (boma3,GPI,0);          //初始化拨码开关 
    gpio_init (boma4,GPI,0);          //初始化拨码开关     
/******************************  LCD   图片  初始化 ****************************/       
    bmp_init();
    bmp_display();
       
/******************************  电机  舵机   初始化 ***************************/
    LCD_str(site,"servo_init...", BLACK,WHITE);
    ftm_pwm_init(S3010_FTM, S3010_CH,S3010_HZ,servo_mid);   // 舵机

    LCD_str(site,"motor_init...", BLACK,WHITE);
    motor_init(); // 电机
/****************************    编码器初始化     ******************************/
    LCD_str(site,"encoder_init...", BLACK,WHITE);
    ftm_quad_init(FTM1);
    ftm_quad_init(FTM2);  
/*******************       拨码开关、蜂鸣器 初始化     *************************/    
    LCD_str(site,"dial_s_init...", BLACK,WHITE);  //拨码开关初始化
    
    LCD_str(site,"buzzer_init...", BLACK,WHITE);
  
/******************************  摄像头   初始化  ******************************/    
    LCD_str   (site,"Cam init ing",FCOLOUR,BCOLOUR);
    camera_init(imgbuff);                             // 摄像头初始化，采集到imgbuff
    LCD_str   (site,"Cam init OK!",FCOLOUR,BCOLOUR);
    
/******************************  AD采集   初始化  ******************************/   
    adc_init (ELEC_L);
    adc_init (ELEC_R);
    
/***********************   按键消息 初始化    **********************************/
    LCD_str(site,"key_init....", BLACK,WHITE);
    key_event_init();
    pit_init_ms(PIT0,10);                                               //pit 定时中断(用于按键定时扫描)
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);                  //设置 PIT0 的中断服务函数为 PIT0_IRQHandler
    enable_irq(PIT0_IRQn);
    
/*****************************       PIT定时        ****************************/
    LCD_str(site,"time_init...", BLACK,WHITE);
    pit_init_ms(PIT2,1);       //pit2 定时中断，总线定时
    set_vector_handler(PIT2_VECTORn ,PIT2_IRQHandler);                 //设置 PIT2 的中断服务函数为 PIT2_IRQHandler
    enable_irq(PIT2_IRQn);

/******************************  配置中断服务函数  *****************************/ 

    set_vector_handler(PORTA_VECTORn , PORTA_IRQHandler);    //设置 PORTA 的中断服务函数为 PORTA_IRQHandler
    set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);     //设置 DMA0 的中断服务函数为 PORTA_IRQHandler 
         
    set_vector_handler(PORTB_VECTORn , portb_handler);                  //超声波的外部中断服务函数为portb_handler
    
    uart_init (UART4, 9600);        //初始化串口4，波特率为115200
    set_vector_handler(UART4_RX_TX_VECTORn,UART_interrupt);               //设置串口接收中断函数   
    uart_rx_irq_en(UART4);                                  //开串口接收中断
    
    parameter_init(); 
    LCD_clear(BLACK);       
 }

/*******************************************************************************
* Function Name: motor_init();
* Description  : 电机初始化
* Author Data  : 2018/1/21
*******************************************************************************/ 
void motor_init()
{
    ftm_pwm_init(MOTOR_FTM, MOTOR_L_Q,MOTOR_HZ,0);     // 左电机前
    ftm_pwm_init(MOTOR_FTM, MOTOR_L_H,MOTOR_HZ,0);     // 左电机后
    ftm_pwm_init(MOTOR_FTM, MOTOR_R_Q,MOTOR_HZ,0);     // 右电机前
    ftm_pwm_init(MOTOR_FTM, MOTOR_R_H,MOTOR_HZ,0);     // 右电机后
}
/*******************************************************************************
* Function Name: parameter_init();
* Description  : 参数初始化
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
  flash_init();//flash初始化
  read_flash();//读取flash存储的参数
}

 
