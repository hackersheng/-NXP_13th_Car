#ifndef __DISPLAY_H__
#define __DISPLAY_H__

/*
 * Include Һ����ʾ��ͷ�ļ�
 */

///////////////////  �����ⲿ����   ///////////////////////////
//extern
extern void bmp_init();
extern void bmp_display();
extern void LCD_UI();                        // UI
extern void color_init();
extern int count_spot( int H_start, int W_start, int H_end, int W_end);
extern void numbre_renew();
extern void numbre_renew1();
extern void led_led();
extern void beep();
///////////////////  �����ⲿ����   ///////////////////////////
extern uint16 color[10];
extern int8 key_clear_flag;
extern int8 renew_flag;
extern uint8 number_display_flag; 
extern uint8 OV7725_yuzhi;
extern uint32 num_black[16];
extern uint8 width_y;



#endif  //__DISPALY_H__

