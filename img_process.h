#ifndef __IMAGE_PROCESSING_H__
#define __IMAGE_PROCESSING_H__

/*
 * Include  ͼ�����ͷ�ļ�
 */

#define use_line  70 
#define pi  3.14  
///////////////////  �����ⲿ����   ///////////////////////////
//extern  
extern void img_ps();
extern int  sum_servo_angle();
extern void oval(uint8 oval_x,uint8 oval_y,int8 zf);



///////////////////  �����ⲿ����   ///////////////////////////
extern uint8 img1[use_line][128];                // һά���飬���������ѹ���ͼ��
extern uint8 leftline_x[use_line];              // һά���飬����������߽��������
extern uint8 rightline_x[use_line];            // һά���飬���������ұ߽��������
extern uint8 midline_x[use_line];             // һά���飬�����������ߺ�������
extern uint8 width_x[use_line]; 

extern uint8 alone_line;
extern uint8 start_spot;
extern uint8 end_spot;
extern uint8 c_mode;
extern uint8 youxiao;
extern uint8 yunsuan;

extern uint8 left1;
extern uint8 left2;
extern uint8 left3;
extern uint8 right1;
extern uint8 right2;
extern uint8 right3;
extern uint8 oval_ox;
extern uint8 oval_oy;

extern uint16 gongshi1;
extern uint16 gongshi2;

extern uint8 left_1;
extern uint8 left_2;
extern uint8 left_3;
extern uint8 left_4;
extern uint8 left_5;
extern uint8 left_6;
extern uint8 right_1;
extern uint8 right_2;
extern uint8 right_3;
extern uint8 right_4;
extern uint8 right_5;
extern uint8 right_6; 

#endif  //__IMAGE_PROCESSING_H__