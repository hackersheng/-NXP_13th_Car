#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

/*
 * Include �ж�ͷ�ļ�
 */
  
///////////////////  �����ⲿ����   ///////////////////////////
//extern
extern void PIT2_IRQHandler();        //��Ҫ�ж�ѭ��
extern void PORTA_IRQHandler();
extern void DMA0_IRQHandler();
extern void PIT0_IRQHandler();
extern void PORTE_IRQHandler();
extern void UART_interrupt();
extern void portb_handler();
   

///////////////////  �����ⲿ����   ///////////////////////////
extern char info;

#endif  //__INTERRUPT_H__