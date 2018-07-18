/*
 * @file       special.c   
 * @author     DLSZ
 * @date       2018-04-23
 */

#include "include.h"
#include "common.h"

/////////////////////////////////  特殊元素变量  ///////////////////////////////
uint8 roundo_flag=0;
uint8 roundo_left=0;
uint8 roundo_right=0;
uint8 roundo_left_flag=0;
uint8 roundo_right_flag=0;
uint8 roundo_leftout_flag=0;
uint8 roundo_rightout_flag=0;
uint8 roundo_jiasu=0;
uint8 roundo_jiansu=0;

uint8 special_roundo=1;
uint8 hdw_right=0;
uint8 hdw_left=0;

void special_element();
void roundo();
void roundo_out();
void bjkuan();

/*******************************************************************************
 * Function Name: void round();
 * Description  : 环岛
 * Author Data  : 2018/3/25 by Lcy
 ******************************************************************************/
void roundo()
{
  //////////////左进环岛电感条件////////////////////////////
     if(elec_L>700&&elec_R>700&&left1>right1&&rightline_x[62-left1]<=rightline_x[70-left1]&&right3==0)//中间位置
      {   
        roundo_left_flag=2; 
        speedmax=speedmax2-roundo_jiansu;
      }
      else if(elec_L>800&&elec_R>300&&elec_R<400&&elec_L-elec_R>400&&left1>right1&&right2-left2>18&&right1>15
          &&rightline_x[62-left1]<=rightline_x[70-left1]&&right3==0)//偏右位置
      {   
        roundo_left_flag=2; 
        speedmax=speedmax2-roundo_jiansu;
      }
      else if(elec_L>400&&elec_R>680&&left1<right1&&leftline_x[62-right1]<leftline_x[70-right1]&&right3==0)//偏左位置
      {  
        roundo_left_flag=2; 
        speedmax=speedmax2-roundo_jiansu;
      }

    //////////////右进环岛电感条件////////////////////////////
      if(elec_L>700&&elec_R>700&&left1<right1&&leftline_x[62-right1]>=leftline_x[70-right1]&&left3==0)//中间位置
      {   
        roundo_right_flag=2; 
        speedmax=speedmax2-roundo_jiansu;
      }
      else if(elec_L>300&&elec_R>800&&elec_L<400&&elec_R-elec_L>400&&left1<right1&&left2-right2>18&&left1>15
          &&leftline_x[62-right1]>=leftline_x[70-right1]&&left3==0)//偏左位置
      {   
        roundo_right_flag=2; 
        speedmax=speedmax2-roundo_jiansu;
      }
      else if(elec_L>680&&elec_R>400&&left1>right1&&rightline_x[62-left1]>rightline_x[70-left1]&&left3==0)//偏右位置
      {   
        roundo_right_flag=2; 
        speedmax=speedmax2-roundo_jiansu;
      }
}
/*******************************************************************************
 * Function Name: void round_out();
 * Description  : 出环岛
 * Author Data  : 2018/3/24 by Lcy
 ******************************************************************************/
void roundo_out()
{
  ////////////////////左出环岛开始画线条件//////////////////////////
  if(rightline_x[23]-leftline_x[23]==124&&
     rightline_x[24]-leftline_x[24]==124&&
     rightline_x[25]-leftline_x[25]==124&&
     roundo_left==1&&roundo_left_flag==0)
  {
    speedmax=speedmax2;
    roundo_leftout_flag=1; 
  }
   ////////////////////右出环岛开始画线条件//////////////////////////
  if(rightline_x[23]-leftline_x[23]==124&&
     rightline_x[24]-leftline_x[24]==124&&
     rightline_x[25]-leftline_x[25]==124&&
     roundo_right==1&&roundo_right_flag==0)
  {
    speedmax=speedmax2;
    roundo_rightout_flag=1;
  }
}
/*******************************************************************************
 * Function Name: void special_element();
 * Description  : 特殊元素判定
 * Author Data  : 2018/3/26 by Lcy
 ******************************************************************************/
void special_element()
{
  //bjkuan();
  if(special_roundo==1)
  {
    if(roundo_flag==0)
    {
      roundo();
    } 
    if( roundo_flag==1)   //只有之前判断了环岛才有出环岛
    {
      roundo_out();
    }
    //////////////////左进环岛画线开始条件////////////////////////////
    if(roundo_left_flag==2&&left1>48)
    {
      roundo_flag=1;
      roundo_left=1;
      roundo_left_flag=1;
      roundo_right_flag=0;
      dist_hdjc=0;
      speedmax=speedmax2;
    }
     //////////////////右进环岛画线开始条件////////////////////////////
    if(roundo_right_flag==2&&right1>48)
    {
      roundo_flag=1;
      roundo_right=1;
      roundo_left_flag=0;
      roundo_right_flag=1;
      dist_hdjc=0; 
      speedmax=speedmax2;
    }
  }
   //////////////////左进环岛的画线////////////////////////////
  if(roundo_left_flag==1)
  {
      oval_ox=use_line-left1-1;
      if(left1<40)
        oval_ox=69-left1-left2;
      oval_oy=leftline_x[oval_ox];
      oval(oval_ox,oval_oy,1);
      if(num_black[11]>110&&elec_L<850/*&&num_black[5]>80*/)
      {
        roundo_left_flag=0; 
        dist_rhd=0;
        speedmax=speedmax2+roundo_jiasu;  
      }
  } 
   //////////////////左出环岛的画线////////////////////////////
  else if(roundo_leftout_flag==1)
  {  
   
      oval_ox=use_line-left1-1;
      if(oval_ox>30)
        oval_ox=45;
      oval_oy=3;
      oval(oval_ox,oval_oy,1);
      if(left1>59||elec_R>650||elec_L>650)
      {
        roundo_leftout_flag=0;
        roundo_flag=0;
        roundo_left=0;
        special_roundo=0;
        dist_hdjj=Total_distance;
      }
  }
   //////////////////右进环岛的画线////////////////////////////
  else if(roundo_right_flag==1)
  {   
      oval_ox=use_line-right1-1;
      if(right1<40/*&&rightline_x[70-right1]-rightline_x[68-right1]<10*/)
        oval_ox=69-right1-right2;
      oval_oy=rightline_x[oval_ox];
      oval(oval_ox,oval_oy,-1);
      if(num_black[8]>500)
      {   
        roundo_right_flag=0;
        dist_rhd=0;
        speedmax=speedmax2+roundo_jiasu;
      }
  } 
   //////////////////右出环岛的画线////////////////////////////
  else if(roundo_rightout_flag==1)
  {  
      oval_ox=use_line-right1-1;
      if(oval_ox>30)
        oval_ox=45;
      oval_oy=126;
      oval(oval_ox,oval_oy,-1);
      if(right1>59||elec_R>650||elec_L>650)
      {
        roundo_rightout_flag=0;
        roundo_flag=0;
        roundo_right=0;
        special_roundo=0;
        dist_hdjj=Total_distance;
      } 
  }
  
}
/*******************************************************************************
 * Function Name: void bjkuan();
 * Description  : 
 * Author Data  : 
 ******************************************************************************/
void bjkuan() 
{   
  int i;
  hdw_right=0;
  hdw_left=0;

   for(i =right1; i >6;i--)
   { 
      if (rightline_x[i-1]- rightline_x[i]>=0)
      {
        hdw_right=1;
        i=5;
      }
   }
   for(i =left1; i >6;i--)
   { 
      if (leftline_x[i]-leftline_x[i-1]>=0)
      {
        hdw_left=1;
        i=5;
      }
    }
}
/*******************************************************************************
 * Function Name: void cross();
 * Description  : 十字路口
 * Author Data  : 2018/3/25 by Lcy
 ******************************************************************************/

/*******************************************************************************
 * Function Name: void cross_out();
 * Description  : 出十字路口
 * Author Data  : 2018/3/25 by Lcy
 ******************************************************************************/

