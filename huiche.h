#ifndef __HUICHE_H__
#define __HUICHE_H__

/*
 * Include �ᳵͷ�ļ�
 */

/////////*******����ͨ�Ŵ���******//////////
#define Start         'Z'   //����
#define Stop          'Y'   //ͣ��
#define Arrive        'U'   //����ᳵ��
#define Test          'W'   //ͣ��

///////////////////  �����ⲿ����   ///////////////////////////
//extern
extern void huiche();
extern void bumper_car(); 
extern void deal_info(char mes);

///////////////////  �����ⲿ����   ///////////////////////////
extern uint8 huiche_flag;
extern uint8 tx_test;
extern uint8 you_can_start;
extern uint8 huiche_cishu;
extern uint8 bumper_car_flag;

// extern uint8 ywdmeiwupan;
// extern uint8 zwdmeiwupan;
// extern uint8 buguize_ywd;
// extern uint8 buguize_zwd;
// extern uint8 yzdmeiwupan;
// extern uint8 zzdmeiwupan;
// extern uint8 buguize_yzd;
// extern uint8 buguize_zzd;
#endif  //__HUICHE_H__