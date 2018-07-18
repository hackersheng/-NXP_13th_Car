/*
 * @file       interrupt.c   
 * @author     DLSZ
 * @date       2018-04-08
 */

#include "common.h"
#include "include.h"
  
char info=0;

/*!
 *  @brief      PIT2�жϷ�����
 *  @since      v5.0
 */
void PIT2_IRQHandler()        //��Ҫ�ж�ѭ��
{
    static uint8  part=0;
    if(system_flag==1)
    {
      part++;

      //ѭ���������ƣ���ֻ���ڶ�����ٶȿ��ƣ������жϻ���һ�����һ��
      switch(part)
      {
        case 1:
            speed_distance();
          break;
        case 2:
            car_move();           //�Ƚ��ж������
          break;
          
        default:
          part=0;
          break;
      }
     if(time_time!=0)
     {
        time_time-=1;
        if(time_time==0)
        {
          time_flag=0;
        }
     }
     time_system();   //��¼ϵͳʱ��
   }
   PIT_Flag_Clear(PIT2);
}



/*!
 *  @brief      PORTA�жϷ�����
 *  @since      v5.0
 */
void PORTA_IRQHandler()
{
    uint8  n;    //���ź�
    uint32 flag;

    while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //���жϱ�־λ

    n = 29;                                             //���ж�
    if(flag & (1 << n))                                 //PTA29�����ж�
    {
        camera_vsync();
    }
#if ( CAMERA_USE_HREF == 1 )                            //ʹ�����ж�
    n = 28;
    if(flag & (1 << n))                                 //PTA28�����ж�
    {
        camera_href();
    }
#endif

}

/*!
 *  @brief      PORTE�жϷ�����
 *  @since      v5.0
 */
void PORTE_IRQHandler()
{
    uint8  n;    //���ź�
    uint32 flag;

    flag = PORTE_ISFR;
    PORTE_ISFR  = ~0;                                   //���жϱ�־λ

    n = 27;
    if(flag & (1 << n))                                 //PTE27�����ж�
    {
        nrf_handler();
    }
}

/*!
 *  @brief      DMA0�жϷ�����
 *  @since      v5.0
 */
void DMA0_IRQHandler()
{
    camera_dma();
}
 
/*!
 *  @brief      PIT0�жϷ�����
 *  @since      v5.0
 */
void PIT0_IRQHandler()
{
    key_IRQHandler();
    PIT_Flag_Clear(PIT0);
} 

/*******************************************************************************
* Function Name: UART_interrupt();
* Description  : ���ڽ����жϴ���
* Author Data  : 2018/4/09   
*******************************************************************************/
void UART_interrupt()      
{
 /* 
  if(UART_S1_REG(UARTN[UART4]) & UART_S1_RDRF_MASK)   //�������ݼĴ�����
  {
    uart_getchar(UART4,&info);
    deal_info(info);
  }
 */ 
  if(uart_query (UART4) == 1)   //�������ݼĴ�����
  {
    uart_getchar(UART4,&info);
    deal_info(info);
  }
}


void portb_handler()
{
 // PORT_FUNC(B,22,measure_distance);        //A  24
}