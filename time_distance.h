#ifndef _TIME_DISTANCE_H
#define _TIME_DISTANCE_H

/*
 * Include 系统时间 头文件
 */

/////////*******定义各种距离限制******//////////
#define dis_qdhc     100              //起点会车
#define dis_hdjc     50              //环岛检测 
#define dis_rhd      65              //入环岛
#define dis_chd      50              //出环岛
#define dis_spd      50              //上坡道
#define dis_xpd      50              //下坡道
#define dis_hdjj     150             //环岛间距
#define dis_hcjl     100             //会车行进距离
#define dis_hzjl     40              //回正距离
extern  uint16 dis_hcjj1;           //第一段会车识别间距
extern  uint16 dis_hcjj2;           //第二段会车识别间距
/////////*******定义各种时间限制******//////////
#define tim_hcdd     4               //会车等待
#define tim_pdjg     2               //坡道间隔

///////////////////  函数外部声明   ///////////////////////////
//extern
extern void time_system();
extern int time_open(uint32 time);
extern void time_dis_limit();

///////////////////  变量外部声明   ///////////////////////////
extern uint32 system_time;         //单次开机系统时间
extern uint8 time_en;              //计时使能标识位
extern uint32 time_time;           //计时
extern uint8 time_flag;


/////////*******定义各种距离限制******//////////
extern uint32 dist_qdhc;             //起点会车
extern uint32 dist_zjhc;             //中间会车
extern uint32 dist_zdhc;             //终点会车
extern uint32 dist_hdjc;             //环岛检测
extern uint32 dist_rhd;              //入环岛
extern uint32 dist_chd;              //出环岛
extern uint32 dist_spd;              //上坡道
extern uint32 dist_xpd;              //下坡道
extern uint32 dist_hdjj;             //环岛间距
extern uint32 dist_hctz;             //会车停止的位置

/////////*******定义各种时间限制******//////////
extern uint32 time_hcdd;           //会车等待
extern uint32 time_pdjg;           //坡道间隔 

#endif  //__SYSTEM_TIME_H__