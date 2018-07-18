#ifndef __CONTROL_H__
#define __CONTROL_H__

/*
 * Include 控制系统的头文件
 */
   
///////////////////  函数外部声明   ///////////////////////////
//extern
extern void servo_control();
extern void canshu_control();

///////////////////  变量外部声明   ///////////////////////////
extern int32 servo_angle;
extern int32 servo_angle_new;

extern float s_kp;
extern float s_td;
extern int32 s_Kp;
extern int32 s_Td;

/*
 * Include 速度控制 头文件
 */

#define Pule_to_Dtc_Proportion  60        //脉冲到路程转化比例 路程单位为 厘米    

///////////////////  函数外部声明   ///////////////////////////
//extern
extern void speed_distance();
extern void speed_input();
extern void motor_control();
   
///////////////////  变量外部声明   ///////////////////////////
extern uint8 cssz_flag;  //参数设置
extern int32 speed_now;
extern int32 L_speed;
extern int32 R_speed;
extern float slow_left;                     //左减速比
extern float slow_right;                   //右减速比
extern uint8 jiasu;
extern uint32 m_kp;
extern uint32 m_td;

extern long int rightval;
extern long int leftval;
extern int32 Total_distance;        //总路程


#endif  //__CONTROL_H__