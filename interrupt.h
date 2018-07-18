#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

/*
 * Include 中断头文件
 */
  
///////////////////  函数外部声明   ///////////////////////////
//extern
extern void PIT2_IRQHandler();        //主要中断循环
extern void PORTA_IRQHandler();
extern void DMA0_IRQHandler();
extern void PIT0_IRQHandler();
extern void PORTE_IRQHandler();
extern void UART_interrupt();
extern void portb_handler();
   

///////////////////  变量外部声明   ///////////////////////////
extern char info;

#endif  //__INTERRUPT_H__