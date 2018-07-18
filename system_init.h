#ifndef _SYSTEM_INIT_H
#define _SYSTEM_INIT_H

/*
 * Include 系统初始化的头文件
 */

#define MOTOR_HZ      10000     //电机频率   
#define S3010_HZ      (50)  
#define servo_mid     695       //减小是往右
#define servo_range   80        //舵机范围
#define ELEC_L        ADC0_SE17        //左电感
#define ELEC_R        ADC0_SE18        //右电感
#define boma1         PTE6         //拨码开关1
#define boma2         PTE7         //拨码开关2
#define boma3         PTE8         //拨码开关3
#define boma4         PTE9         //拨码开关4
///////////////////  函数外部声明   ///////////////////////////
//extern
extern void sys_init(void);

///////////////////  变量外部声明   ///////////////////////////
extern uint8 imgbuff[CAMERA_SIZE];             //定义存储接收图像的数组
extern uint8 img[CAMERA_H][CAMERA_W];
extern uint8 system_flag;



#endif  //__SYS_INIT_H__