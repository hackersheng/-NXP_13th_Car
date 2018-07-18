/*
 * @file       interrupt.c   
 * @author     DLSZ
 * @date       2018-04-08
 */

#include "common.h"
#include "include.h"
  
char info=0;

/*!
 *  @brief      PIT2中断服务函数
 *  @since      v5.0
 */
void PIT2_IRQHandler()        //主要中断循环
{
    static uint8  part=0;
    if(system_flag==1)
    {
      part++;

      //循环计数控制，（只用于舵机、速度控制），总中断还是一秒进入一次
      switch(part)
      {
        case 1:
            speed_distance();
          break;
        case 2:
            car_move();           //先进行舵机控制
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
     time_system();   //记录系统时间
   }
   PIT_Flag_Clear(PIT2);
}



/*!
 *  @brief      PORTA中断服务函数
 *  @since      v5.0
 */
void PORTA_IRQHandler()
{
    uint8  n;    //引脚号
    uint32 flag;

    while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //清中断标志位

    n = 29;                                             //场中断
    if(flag & (1 << n))                                 //PTA29触发中断
    {
        camera_vsync();
    }
#if ( CAMERA_USE_HREF == 1 )                            //使用行中断
    n = 28;
    if(flag & (1 << n))                                 //PTA28触发中断
    {
        camera_href();
    }
#endif

}

/*!
 *  @brief      PORTE中断服务函数
 *  @since      v5.0
 */
void PORTE_IRQHandler()
{
    uint8  n;    //引脚号
    uint32 flag;

    flag = PORTE_ISFR;
    PORTE_ISFR  = ~0;                                   //清中断标志位

    n = 27;
    if(flag & (1 << n))                                 //PTE27触发中断
    {
        nrf_handler();
    }
}

/*!
 *  @brief      DMA0中断服务函数
 *  @since      v5.0
 */
void DMA0_IRQHandler()
{
    camera_dma();
}
 
/*!
 *  @brief      PIT0中断服务函数
 *  @since      v5.0
 */
void PIT0_IRQHandler()
{
    key_IRQHandler();
    PIT_Flag_Clear(PIT0);
} 

/*******************************************************************************
* Function Name: UART_interrupt();
* Description  : 串口接收中断处理
* Author Data  : 2018/4/09   
*******************************************************************************/
void UART_interrupt()      
{
 /* 
  if(UART_S1_REG(UARTN[UART4]) & UART_S1_RDRF_MASK)   //接收数据寄存器满
  {
    uart_getchar(UART4,&info);
    deal_info(info);
  }
 */ 
  if(uart_query (UART4) == 1)   //接收数据寄存器满
  {
    uart_getchar(UART4,&info);
    deal_info(info);
  }
}


void portb_handler()
{
 // PORT_FUNC(B,22,measure_distance);        //A  24
}