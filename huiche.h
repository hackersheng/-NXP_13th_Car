#ifndef __HUICHE_H__
#define __HUICHE_H__

/*
 * Include 会车头文件
 */

/////////*******定义通信代号******//////////
#define Start         'Z'   //发车
#define Stop          'Y'   //停车
#define Arrive        'U'   //到达会车区
#define Test          'W'   //停车

///////////////////  函数外部声明   ///////////////////////////
//extern
extern void huiche();
extern void bumper_car(); 
extern void deal_info(char mes);

///////////////////  变量外部声明   ///////////////////////////
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