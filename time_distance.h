#ifndef _TIME_DISTANCE_H
#define _TIME_DISTANCE_H

/*
 * Include ϵͳʱ�� ͷ�ļ�
 */

/////////*******������־�������******//////////
#define dis_qdhc     100              //���ᳵ
#define dis_hdjc     50              //������� 
#define dis_rhd      65              //�뻷��
#define dis_chd      50              //������
#define dis_spd      50              //���µ�
#define dis_xpd      50              //���µ�
#define dis_hdjj     150             //�������
#define dis_hcjl     100             //�ᳵ�н�����
#define dis_hzjl     40              //��������
extern  uint16 dis_hcjj1;           //��һ�λᳵʶ����
extern  uint16 dis_hcjj2;           //�ڶ��λᳵʶ����
/////////*******�������ʱ������******//////////
#define tim_hcdd     4               //�ᳵ�ȴ�
#define tim_pdjg     2               //�µ����

///////////////////  �����ⲿ����   ///////////////////////////
//extern
extern void time_system();
extern int time_open(uint32 time);
extern void time_dis_limit();

///////////////////  �����ⲿ����   ///////////////////////////
extern uint32 system_time;         //���ο���ϵͳʱ��
extern uint8 time_en;              //��ʱʹ�ܱ�ʶλ
extern uint32 time_time;           //��ʱ
extern uint8 time_flag;


/////////*******������־�������******//////////
extern uint32 dist_qdhc;             //���ᳵ
extern uint32 dist_zjhc;             //�м�ᳵ
extern uint32 dist_zdhc;             //�յ�ᳵ
extern uint32 dist_hdjc;             //�������
extern uint32 dist_rhd;              //�뻷��
extern uint32 dist_chd;              //������
extern uint32 dist_spd;              //���µ�
extern uint32 dist_xpd;              //���µ�
extern uint32 dist_hdjj;             //�������
extern uint32 dist_hctz;             //�ᳵֹͣ��λ��

/////////*******�������ʱ������******//////////
extern uint32 time_hcdd;           //�ᳵ�ȴ�
extern uint32 time_pdjg;           //�µ���� 

#endif  //__SYSTEM_TIME_H__