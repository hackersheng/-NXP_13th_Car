#ifndef __MOVE_H__
#define __MOVE_H__

/*
 * Include ��� ����˶�ͷ�ļ�
 */

#define MOTOR_FTM  FTM0

#define MOTOR_L_Q  FTM_CH7     
#define MOTOR_L_H  FTM_CH6
#define MOTOR_R_Q  FTM_CH4
#define MOTOR_R_H  FTM_CH5

 
#define S3010_FTM   FTM3
#define S3010_CH    FTM_CH0
   
///////////////////  �����ⲿ����   ///////////////////////////
//extern
extern void car_move();                                  // Acar�˶�  
extern void motor_move(int32 L_speed , int32 R_speed);  // ����˶�
extern void servo_move(int32 x);                      // ����˶�
extern void car_stop();
extern void car_start_key();
extern void car_stop_key();
extern void start_stop();
extern void slow();
extern void uart_start_stop(uint8 i);
   

///////////////////  �����ⲿ����   ///////////////////////////
extern uint8 motor_flag;
extern uint8 servo_flag;
extern uint8 speedmax;
extern uint8 speedmax2;
extern uint8 car_mode;
extern uint8 start_stop_flag;
extern uint8 start_stop_time;
extern uint8 ramp_flag;
extern uint8 start_spot_last;

#endif  //__MOVE_H__