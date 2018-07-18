/*
 * @file       move.c   
 * @author     DLSZ
 * @date       2018-01-21
 */

#include "common.h"
#include "include.h"

uint8 speedmax=48;
uint8 speedmax2=48;
uint8 car_mode=1; 
/////////////////////////////////  变量表   ////////////////////////////////////
uint8 motor_flag=0;
uint8 servo_flag=0;
uint8 start_stop_flag=0;
uint8 stop_time=0;
uint8 start_stop_time=0;
uint8 ramp_flag=0;
uint8 start_spot_last;

/////////////////////////////////  函数表   ////////////////////////////////////
void car_move();                                    // Acar运动  
void motor_move(int32 L_speed , int32 R_speed);    // 电机运动
void servo_move(int32 x);                         // 舵机运动
void car_stop();
void car_start_key();
void car_stop_key();
void slow();
void start_stop();
void ramp();
     
/*******************************************************************************
 * Function Name: car_move();
 * Description  : Acar运动
 * Author Data  : 2018/1/21 by Lcy
 ******************************************************************************/     
void car_move()
{
    if(motor_flag==4)
    {
       alone_line=64;     
    }
    servo_control();

    ramp();
    if(ramp_flag==3)
    {
     speedmax=60;
    }
    else if(ramp_flag==2)
    {
     speedmax=30;
    }
     else if(ramp_flag==1)
    {
     speedmax=speedmax2;
    }
    servo_move(servo_mid-servo_angle); 
    
    speed_input();
    if(motor_flag!=0)
    {
      motor_control();
    }
    motor_move(L_speed, R_speed);   
}  
/*******************************************************************************
 * Function Name: motor_move();
 * Description  : 电机运动
 * Author Data  : 2018/1/21 by Lcy
 ******************************************************************************/
void motor_move(int32 L_sp , int32 R_sp)
{
  if(motor_flag==0)
  {
    ftm_pwm_duty(MOTOR_FTM, MOTOR_L_Q,0);       
    ftm_pwm_duty(MOTOR_FTM, MOTOR_L_H,0);   

    ftm_pwm_duty(MOTOR_FTM, MOTOR_R_Q,0);       
    ftm_pwm_duty(MOTOR_FTM, MOTOR_R_H,0);  
  }
  else if(motor_flag==1)
  {
    L_sp=constrain_int32(L_sp,0,8000);    //要限值返回赋予值
    R_sp=constrain_int32(R_sp,0,8000);
    
    ftm_pwm_duty(MOTOR_FTM, MOTOR_L_Q,L_sp);       
    ftm_pwm_duty(MOTOR_FTM, MOTOR_L_H,0);   

    ftm_pwm_duty(MOTOR_FTM, MOTOR_R_Q,R_sp);       
    ftm_pwm_duty(MOTOR_FTM, MOTOR_R_H,0);       
  }
  else if(motor_flag==4)
  {      
    if((leftval>0)&&(rightval>0))
    {
      ftm_pwm_duty(MOTOR_FTM, MOTOR_L_Q,0);       
      ftm_pwm_duty(MOTOR_FTM, MOTOR_L_H,speedmax*80);   

      ftm_pwm_duty(MOTOR_FTM, MOTOR_R_Q,0);       
      ftm_pwm_duty(MOTOR_FTM, MOTOR_R_H,speedmax*80);  
    }
    else if((leftval<=0)&&(rightval<=0))
    {
      ftm_pwm_duty(MOTOR_FTM, MOTOR_L_Q,0);       
      ftm_pwm_duty(MOTOR_FTM, MOTOR_L_H,50);   

      ftm_pwm_duty(MOTOR_FTM, MOTOR_R_Q,0);       
      ftm_pwm_duty(MOTOR_FTM, MOTOR_R_H,50);  
    }     
  }
  else if(motor_flag==8)
  {      
    if((leftval>0)&&(rightval>0))
    {
      ftm_pwm_duty(MOTOR_FTM, MOTOR_L_Q,0);       
      ftm_pwm_duty(MOTOR_FTM, MOTOR_L_H,speedmax*20);   

      ftm_pwm_duty(MOTOR_FTM, MOTOR_R_Q,0);      
      ftm_pwm_duty(MOTOR_FTM, MOTOR_R_H,speedmax*20);  
    }
    else if((leftval<=0)&&(rightval<=0))
    {
      ftm_pwm_duty(MOTOR_FTM, MOTOR_L_Q,0);       
      ftm_pwm_duty(MOTOR_FTM, MOTOR_L_H,50);   

      ftm_pwm_duty(MOTOR_FTM, MOTOR_R_Q,0);       
      ftm_pwm_duty(MOTOR_FTM, MOTOR_R_H,50);  
    }     
  }
  else
  {
    ftm_pwm_duty(MOTOR_FTM, MOTOR_L_Q,0);       
    ftm_pwm_duty(MOTOR_FTM, MOTOR_L_H,0);   

    ftm_pwm_duty(MOTOR_FTM, MOTOR_R_Q,0);       
    ftm_pwm_duty(MOTOR_FTM, MOTOR_R_H,0);  
  }
}    
/*******************************************************************************
 * Function Name: servo_move();
 * Description  : 舵机运动
 * Author Data  : 2018/1/21 by Lcy
 ******************************************************************************/
void servo_move(int32 x)
{  
  if(servo_flag==0)
  {
    ftm_pwm_duty(S3010_FTM,S3010_CH,servo_mid);            //舵机
  }
  else if(servo_flag==1)
  {
    x=constrain_int32(x,servo_mid-servo_range,servo_mid+servo_range);
    ftm_pwm_duty(S3010_FTM,S3010_CH,x);                   //舵机
  }
  else
  {
    ftm_pwm_duty(S3010_FTM,S3010_CH,servo_mid);           //舵机
  }   
}
/*******************************************************************************
 * Function Name: car_stop();
 * Description  : 停车
 * Author Data  : 2018/1/21 by Lcy
 ******************************************************************************/
void car_stop()
{
    time_en=0;
    motor_flag=4;
    motor_move(0,0);
    KEY_MSG_t keyinfo;
    LCD_clear(BLACK);
    
    Site_t site;
    site.x = 8;
    site.y = 40;
    LCD_FSTR_CH(site,fly ,WHITE, BLACK) ;    // 跑飞
    Site_t site1;
    site1.x = 8;
    site1.y = 70;
    LCD_FSTR_CH(site1,go_on ,WHITE, BLACK) ;    // 继续
    
    while(!(get_key_msg(& keyinfo)))     //按一下按键进入，否则不退出
    {
    }
    LCD_clear(BLACK);
    motor_flag=0;
    servo_flag=0;
}
/*******************************************************************************
 * Function Name: start_stop();
 * Description  : 起跑线开车停车
 * Author Data  : 2018/3/31 by Lcy
 ******************************************************************************/
void start_stop()
{
  uint8 LL=0;
  uint8 RR=0;

  for(int i = 62; i > 5; --i)
  {
    if( (img1[30][i]+img1[30][i+1]+img1[30][i+2])==255 )
    {
      LL+=1;
    }    
  }
  for(int i = 62; i > 5; --i)
  {
    if( (img1[31][i]+img1[31][i+1]+img1[31][i+2])==255 )
    {
      LL+=1;
    }    
  }
  for(int i = 66; i < 123; ++i)
  {
    if( (img1[30][i]+img1[30][i-1]+img1[30][i-2])==255 )
    {
      RR+=1;
    }    
  }
  for(int i = 66; i < 123; ++i)
  {
    if( (img1[31][i]+img1[31][i-1]+img1[31][i-2])==255 )
    {
      RR+=1;
    }    
  }
  if( LL>5&&RR>5)
  {
    motor_flag=6;
  }   
   
}
/*******************************************************************************
 * Function Name: uart_start_stop();
 * Description  : 串口开车停车
 * Author Data  : 2018/4/09 by Lcy
 ******************************************************************************/
void uart_start_stop(uint8 i)
{
  if(i==0)
  { 
    motor_flag=4;
    time_en=0;  
  }    
  else if(i==1)   
  {
    LCD_clear(BLACK);
    DELAY_MS(1000);
    flag_key_select=5;
    flag_key_l_u_0=0;
    motor_flag=1;
    servo_flag=1;
    time_en=1;
    ramp_flag=0;
    system_time=0;
    Total_distance=0;
    ftm_quad_clean(FTM1);               //清空脉冲
    ftm_quad_clean(FTM2);
    alone_line=64; 
  }
}
/*******************************************************************************
 * Function Name: car_start_key();
 * Description  : 按键发车
 * Author Data  : 2018/3/13 by Lcy
 ******************************************************************************/
void car_start_key()
{
  LCD_clear(BLACK);
  motor_flag=1;
  servo_flag=1;
  time_en=1;
  ramp_flag=0;
  system_time=0;
  Total_distance=0;
  ftm_quad_clean(FTM1);               //清空脉冲
  ftm_quad_clean(FTM2);
  alone_line=64; 
}
/*******************************************************************************
 * Function Name: car_stop_key();
 * Description  : 按键停车
 * Author Data  : 2018/3/13 by Lcy
 ******************************************************************************/
void car_stop_key()
{
  motor_flag=0;
  servo_flag=0;
  time_en=0;
}
/*******************************************************************************
 * Function Name: void ramp();
 * Description  : 坡道
 * Author Data  : 2018/4/22 by Lcy
 ******************************************************************************/
void ramp()
{ 
  if(roundo_left_flag==0&&roundo_right_flag==0&&ramp_flag==0&&servo_flag==1)
  {
    if(elec_R>380&&elec_L>380&&num_black[0]<350&&num_black[1]<100&&num_black[2]<100&&num_black[3]<350&&
       num_black[4]<300&&num_black[5]<100&&num_black[6]<100&&num_black[7]<300&&
       num_black[8]<100&&num_black[9]<200&&num_black[10]<200&&num_black[11]<100&&
       num_black[12]<100&&num_black[13]<200&&num_black[14]<200&&num_black[15]<100)
    {
      ramp_flag=3;
      start_spot_last=start_spot;
      start_spot=55;
    }
    else if(elec_R>450&&elec_L>220&&num_black[0]<450&&num_black[1]<100&&num_black[2]<100&&num_black[3]<200&&
       num_black[4]<300&&num_black[5]<100&&num_black[6]<100&&num_black[7]<200&&
       num_black[8]<100&&num_black[9]<200&&num_black[10]<200&&num_black[11]<100&&
       num_black[12]<100&&num_black[13]<200&&num_black[14]<200&&num_black[15]<100)
    {
      ramp_flag=3;
      start_spot_last=start_spot;
      start_spot=55;
    }
    else if(elec_R>220&&elec_L>450&&num_black[0]<200&&num_black[1]<100&&num_black[2]<100&&num_black[3]<450&&
       num_black[4]<200&&num_black[5]<100&&num_black[6]<100&&num_black[7]<300&&
       num_black[8]<100&&num_black[9]<200&&num_black[10]<200&&num_black[11]<100&&
       num_black[12]<100&&num_black[13]<200&&num_black[14]<200&&num_black[15]<100)
    {
      ramp_flag=3;
      start_spot_last=start_spot;
      start_spot=55;
    }
    else
    {}
  }
  else if(ramp_flag==3)
  {
    if(num_black[12]>50&&num_black[15]>50)
    {
      ramp_flag=2;
      dist_spd=0;
    }
  }
  else if(ramp_flag==2)
  {
    if(left1>56||right1>56)
    {
      ramp_flag=1;
      dist_xpd=0;
      time_pdjg=system_time;
      start_spot=start_spot_last;
    }
  }   
}
/*******************************************************************************
 * Function Name: slow();
 * Description  : 减速运动
 * Author Data  : 2018/1/21 by Lcy
 ******************************************************************************/
void slow()
{
  if(servo_angle>0)
  {
    slow_left=0;
    slow_right=(speed_now-10)/10;  //10影响转弯半径
  }
  else if(servo_angle<0)
  {
    slow_left=(speed_now-10)/10;
    slow_right=0;
  }
  else
  {
    slow_left=0;
    slow_right=0;
  }       
}





