#ifndef _SYSTEM_INIT_H
#define _SYSTEM_INIT_H

/*
 * Include ϵͳ��ʼ����ͷ�ļ�
 */

#define MOTOR_HZ      10000     //���Ƶ��   
#define S3010_HZ      (50)  
#define servo_mid     695       //��С������
#define servo_range   80        //�����Χ
#define ELEC_L        ADC0_SE17        //����
#define ELEC_R        ADC0_SE18        //�ҵ��
#define boma1         PTE6         //���뿪��1
#define boma2         PTE7         //���뿪��2
#define boma3         PTE8         //���뿪��3
#define boma4         PTE9         //���뿪��4
///////////////////  �����ⲿ����   ///////////////////////////
//extern
extern void sys_init(void);

///////////////////  �����ⲿ����   ///////////////////////////
extern uint8 imgbuff[CAMERA_SIZE];             //����洢����ͼ�������
extern uint8 img[CAMERA_H][CAMERA_W];
extern uint8 system_flag;



#endif  //__SYS_INIT_H__