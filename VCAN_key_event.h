#ifndef _VCAN_KEY_EVNET_H_
#define _VCAN_KEY_EVNET_H_

#include "common.h"
#include "VCAN_key.h"



extern void key_event_init();                              //��ʼ��������Ϣ
extern void deal_key_event(void);                          //��������Ϣ���Զ��л�ѡ�е����֣��Զ������ֽ��мӼ���

extern void deal_key_up();
extern void deal_key_down();
extern void deal_key_left();
extern void deal_key_right();
extern void deal_key_select();
extern void deal_key_left_1();
extern void deal_key_right_1();

extern int8 flag_key_select;
extern int8 flag_key_l_u_0;
extern int8 flag_key_l_u_1;
extern int8 flag_key_l_u_2;
extern int8 flag_key_l_u_3;
extern int8 flag_key_l_u_4;
extern int8 flag_key_l_u_5;
extern int8 flag_key_l_u_6;

#endif  //_VCAN_KEY_EVNET_H_