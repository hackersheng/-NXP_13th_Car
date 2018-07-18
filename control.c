/*
 * @file       control.c   
 * @author     DLSZ
 * @date       2018-03-11
 */

#include "common.h"
#include "include.h"

uint8 cssz_flag=0;  //参数设置
/////////////////////////////////  舵机变量表   ////////////////////////////////
int32 servo_angle;
int32 servo_angle_new;   
   
int32 s_error[3];
float s_kp=0.045,s_td=0.060;
int32 s_Kp,s_Td;

/////////////////////////////////  电机变量表   ////////////////////////////////
int32 speed;
int32 speed_now;
int32 L_speed;
int32 R_speed;
int16 L_want;
int16 R_want;
float slow_left;                     //左减速比
float slow_right;                    //右减速比
uint8 jiasu=0;

int32 m_error_L[3];
int32 m_error_R[3];
int32 m_error_L1[2];
int32 m_error_R1[2];
uint32 m_kp=90,m_td=160;

long int rightval;
long int leftval;
int16 Car_Speed_ave;
int16 Car_Speed_average[8];
int16 Distance_Current_Pule=0;   //本次行驶脉冲
int32 Total_distance;            //总路程

/////////////////////////////////  函数表   ////////////////////////////////////
void servo_control();
void canshu_control();

/*******************************************************************************
 * Function Name: servo_control();
 * Description  : 舵机控制
 * Author Data  : 2018/4/13 by Lcy
 ******************************************************************************/
void servo_control()
{
  if(cssz_flag==0)
    canshu_control();
  
  s_error[2]=s_error[1];
  s_error[1]=s_error[0];
  s_error[0]=servo_angle_new;
  servo_angle=(int32)(s_kp*s_error[0]+s_td*(s_error[0]-s_error[1]));  
  
  if(abs(servo_angle)<3)
    servo_angle=0;
  
  // 转换方便显示
  s_Kp=(int32)(s_kp*1000);
  s_Td=(int32)(s_td*1000);
}

/*******************************************************************************
 * Function Name: speed_input();
 * Description  : 闭环速度设置
 * Author Data  : 2018/5/15 by DLSZ
 ******************************************************************************/
void speed_input()
{
    if(yunsuan>=53&&abs(servo_angle)<8)
    {
      speed=speedmax+jiasu;
    }
    else
    { 
      speed=speedmax;
    }
    slow();

    m_error_L1[1]=m_error_L1[0];
    m_error_L1[0]=(int32)(abs(servo_angle)*slow_left);

    m_error_R1[1]=m_error_R1[0];
    m_error_R1[0]=(int32)(abs(servo_angle)*slow_right);  

    L_want=speed-(int32)(0.09*m_error_L1[0]+0.04*(m_error_L1[0]-m_error_L1[1]));
    R_want=speed-(int32)(0.09*m_error_R1[0]+0.04*(m_error_R1[0]-m_error_R1[1]));  

    if(L_want<0)
    {
      L_want=0;
    }
    if(R_want<0)
    {
      R_want=0;
    }
}
/*******************************************************************************
 * Function Name: motor_control();
 * Description  : 电机控制
 * Author Data  : 2018/5/15 by DLSZ
 ******************************************************************************/
void motor_control()
{
    m_error_L[2]=m_error_L[1];
    m_error_L[1]=m_error_L[0];
    m_error_L[0]=L_want-leftval;
    
    m_error_R[2]=m_error_R[1];    
    m_error_R[1]=m_error_R[0];
    m_error_R[0]=R_want-rightval;
    
    L_speed=L_speed+(int32)(m_kp*m_error_L[0]+m_td*(m_error_L[0]-m_error_L[1]));
    R_speed=R_speed+(int32)(m_kp*m_error_R[0]+m_td*(m_error_R[0]-m_error_R[1]));

    L_speed=constrain_int32(L_speed,0,speedmax*200);    //要限值返回赋予值
    R_speed=constrain_int32(R_speed,0,speedmax*200);
    
}
/*******************************************************************************
 * Function Name: speed_distance();
 * Description  : 获取速度与行程
 * Author Data  : 2018/5/15 by DLSZ
 ******************************************************************************/
void speed_distance()
{
    static int16 Speed_pre,Spees_pre_pre,Car_Speed;
    uint8 i=0;
    float number=0;

    Spees_pre_pre=Speed_pre;
    Speed_pre=Car_Speed;

    leftval  =  ftm_quad_get(FTM1);      //获取脉冲
    rightval = -ftm_quad_get(FTM2);

    speed_now=(int32)((rightval+leftval)/2);
    Car_Speed=(rightval+leftval)/2;    //左右轮速度求平均
    Car_Speed_ave=(Car_Speed +Speed_pre+Spees_pre_pre)/3;   //速度滤波
    Car_Speed_average[0]=Car_Speed_ave;

    for(i=7;i>0;i--)     //存储编码器的值
    {
     Car_Speed_average[i]=Car_Speed_average[i-1];
    }

    Distance_Current_Pule+=Car_Speed;  //本次行驶脉冲累计

    if(Distance_Current_Pule>(Pule_to_Dtc_Proportion))    //脉冲转化为路程
    {
      number= (Distance_Current_Pule/Pule_to_Dtc_Proportion);
      Total_distance+= number ;       //总路程累加
      Distance_Current_Pule-=(Pule_to_Dtc_Proportion*number);  //脉冲计数对应减少
    }
    ftm_quad_clean(FTM1);               //清空脉冲
    ftm_quad_clean(FTM2);
}
/*******************************************************************************
 * Function Name: canshu_control();
 * Description  : 参数控制
 * Author Data  : 2018/6/5 by DLSZ
 ******************************************************************************/
void canshu_control()
{
  if(speedmax==45)
  {
    s_kp=0.045;    m_kp=90;
    s_td=0.060;    m_td=160;
  }
  else if(speedmax==46)
  {
    s_kp=0.046;    m_kp=87;
    s_td=0.062;    m_td=154;
  }
  else if(speedmax==47)
  {
    s_kp=0.047;    m_kp=84;
    s_td=0.064;    m_td=148;
  }
  else if(speedmax==48)
  {
    s_kp=0.048;    m_kp=75;
    s_td=0.066;    m_td=100;
  }
  else if(speedmax==49)
  {
    s_kp=0.049;    m_kp=78;
    s_td=0.068;    m_td=136;
  }
  else if(speedmax==50)
  {
    s_kp=0.050;    m_kp=55;
    s_td=0.070;    m_td=80;
  }
  else if(speedmax==51)
  {
    s_kp=0.051;    m_kp=71;
    s_td=0.072;    m_td=122;
  }
  else if(speedmax==52)
  {
    s_kp=0.052;    m_kp=67;
    s_td=0.074;    m_td=114;
  }
  else if(speedmax==53)
  {
    s_kp=0.053;    m_kp=63;
    s_td=0.076;    m_td=106;
  }
  else if(speedmax==54)
  {
    s_kp=0.054;    m_kp=59;
    s_td=0.078;    m_td=98;
  }
  else if(speedmax==55)
  {
    s_kp=0.055;    m_kp=55;
    s_td=0.080;    m_td=90;
  }
  else
  {
    s_kp=0.040,    m_kp=100;
    s_td=0.050;    m_td=180;
  } 
}

/*
void canshu_control()
{
  if(speedmax==45)
  {
    s_kp=0.045;    m_kp=90;
    s_td=0.060;    m_td=160;
  }
  else if(speedmax==46)
  {
    s_kp=0.046;    m_kp=87;
    s_td=0.062;    m_td=154;
  }
  else if(speedmax==47)
  {
    s_kp=0.047;    m_kp=84;
    s_td=0.064;    m_td=148;
  }
  else if(speedmax==48)
  {
    s_kp=0.048;    m_kp=81;
    s_td=0.066;    m_td=142;
  }
  else if(speedmax==49)
  {
    s_kp=0.049;    m_kp=78;
    s_td=0.068;    m_td=136;
  }
  else if(speedmax==50)
  {
    s_kp=0.050;    m_kp=75;
    s_td=0.070;    m_td=130;
  }
  else if(speedmax==51)
  {
    s_kp=0.051;    m_kp=71;
    s_td=0.072;    m_td=122;
  }
  else if(speedmax==52)
  {
    s_kp=0.052;    m_kp=67;
    s_td=0.074;    m_td=114;
  }
  else if(speedmax==53)
  {
    s_kp=0.053;    m_kp=63;
    s_td=0.076;    m_td=106;
  }
  else if(speedmax==54)
  {
    s_kp=0.054;    m_kp=59;
    s_td=0.078;    m_td=98;
  }
  else if(speedmax==55)
  {
    s_kp=0.055;    m_kp=55;
    s_td=0.080;    m_td=90;
  }
  else
  {
    s_kp=0.040,    m_kp=100;
    s_td=0.050;    m_td=180;
  } 
}
*/
