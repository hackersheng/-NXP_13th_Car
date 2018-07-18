#ifndef __CONTROL_H__
#define __CONTROL_H__

/*
 * Include ����ϵͳ��ͷ�ļ�
 */
   
///////////////////  �����ⲿ����   ///////////////////////////
//extern
extern void servo_control();
extern void canshu_control();

///////////////////  �����ⲿ����   ///////////////////////////
extern int32 servo_angle;
extern int32 servo_angle_new;

extern float s_kp;
extern float s_td;
extern int32 s_Kp;
extern int32 s_Td;

/*
 * Include �ٶȿ��� ͷ�ļ�
 */

#define Pule_to_Dtc_Proportion  60        //���嵽·��ת������ ·�̵�λΪ ����    

///////////////////  �����ⲿ����   ///////////////////////////
//extern
extern void speed_distance();
extern void speed_input();
extern void motor_control();
   
///////////////////  �����ⲿ����   ///////////////////////////
extern uint8 cssz_flag;  //��������
extern int32 speed_now;
extern int32 L_speed;
extern int32 R_speed;
extern float slow_left;                     //����ٱ�
extern float slow_right;                   //�Ҽ��ٱ�
extern uint8 jiasu;
extern uint32 m_kp;
extern uint32 m_td;

extern long int rightval;
extern long int leftval;
extern int32 Total_distance;        //��·��


#endif  //__CONTROL_H__