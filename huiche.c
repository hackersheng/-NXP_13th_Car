/*
 * @file       huiche.c   
 * @author     DLSZ
 * @date       2018-04-05
 */

#include "common.h"
#include "include.h"

/////////////////////////////////  ������   ////////////////////////////////////
uint8 huiche_flag=0;  
uint8 tx_test=0;  
uint8 you_can_start=0;
uint8 huiche_cishu=0;
uint8 bumper_car_flag=0;

uint8 ywdmeiwupan;
uint8 zwdmeiwupan;
uint8 buguize_ywd;
uint8 buguize_zwd;
uint8 yzdmeiwupan;
uint8 zzdmeiwupan;
uint8 buguize_yzd;
uint8 buguize_zzd;
/////////////////////////////////  ������   ////////////////////////////////////
void zdhuiche();  //ֱ���ᳵ���
void wdhuiche();  //����ᳵ���
void huiche();    //�ᳵִ��

void bumper_car();                         //������
void deal_wupan();
/*******************************************************************************
 * Function Name: wdhuiche();
 * Description  : ����ᳵ��ʶ��
 * Author Data  : 2018/6/5 by DLSZ
 ******************************************************************************/
void wdhuiche() 
{
    if(/*servo_angle<-20&&*/right1<33&&right_1<43&&right_4<17&&ywdmeiwupan==1&&
       ((right_2<3&&right_3>2&&right_3<12)||
        (right_3<3&&right_2>3&&right_2<12))&&
         right_1+right_2+right_3<48)
    {
      huiche_flag=3;
    }
    else if(/*servo_angle>20&&*/left1<33&&left_1<43&&left_4<17&&zwdmeiwupan==1&&
            ((left_2<3&&left_3>2&&left_3<12)||
             (left_3<3&&left_2>3&&left_2<12))&&
              left_1+left_2+left_3<48) 
    {
      huiche_flag=3;
    }

}
/*******************************************************************************
 * Function Name: zdhuiche();
 * Description  : ֱ���ᳵ��ʶ��
 * Author Data  : 2018/6/5 by DLSZ
 ******************************************************************************/
void zdhuiche()   
{ 
    if(left1>30&&left1<45&&right1>30&&right1<45&&right_1<48&&left_1<48&&
       ((left_2<2&&right_2<2&&left_3<6&&right_3<6&&left_3>1&&right_3>1)||
        (left_3<2&&right_3<2&&left_2<6&&right_2<6&&left_2>1&&right_2>1)||
        (left_2<2&&left_3>1&&left_3<8&&right_3<2&&right_2>1&&right_3<8)||
        (right_2<2&&right_3>1&&right_3<8&&left_2>1&&left_2<8&&left_3<2))) //ֱ
    {
      huiche_flag=3;
    }
    else if(servo_angle<20&&servo_angle>=0&&
      30<left_1&&left_1<45&&left_4<8/*&&zzdmeiwupan==1*/&&
      ((left_2<2&&left_3>1&&left_3<8)||
      (left_3<2&&left_2>1&&left_2<8))) //ƫ��
    {
      huiche_flag=3;
    }
  
    else if(servo_angle>-20&&servo_angle<=0&&
      30<right_1&&right_1<45&&right_4<8/*&&yzdmeiwupan==1*/&&
       ((right_2<2&&right_3>1&&right_3<8)||
       (right_3<2&&right_2>1&&right_2<8))) //ƫ��
    {
      huiche_flag=3;
    }

}
/*******************************************************************************
 * Function Name: huiche();
 * Description  : �ᳵִ��
 * Author Data  : 2018/6/5 by DLSZ
 ******************************************************************************/
void huiche()  
{
    if(huiche_flag==0&&((ramp_flag==0||ramp_flag==1))&&roundo_flag==0)
    {  
        deal_wupan();
        wdhuiche();
        zdhuiche();
       
    }
  
    if(huiche_flag==3&&servo_flag==1)
    { 
       c_mode=2;
       if(you_can_start==0)   
       {    
          motor_flag=4;
          if(leftval==0&&rightval==0)
          {
            alone_line=64;
            huiche_flag=2;
            c_mode=2;
            uart_putchar (UART4,'C');
            huiche_cishu+=1;
            if( huiche_cishu==2)
              huiche_cishu=3;
          }
       } 
       if(you_can_start==1)   
        {
          alone_line=64;
          huiche_flag=2;
          c_mode=2;
          uart_putchar (UART4,'C');
          huiche_cishu+=1;
        }
    }
    else if(huiche_flag==2)
    { 
      if(you_can_start==1)
      {
        alone_line=64;
        motor_flag=1;
        if( huiche_cishu==1|| huiche_cishu==2)
        speedmax=speedmax2-10;
        else
         speedmax=speedmax2+5; 
      }  
    }
    else if(huiche_flag==1)
    { 
      c_mode=1;
      if(huiche_cishu==2|| huiche_cishu==3)
        motor_flag=8;
    }
}
/*******************************************************************************
 * Function Name: bumper_car();
 * Description  : ������
 * Author Data  : 2018/4/5 by DLSZ
 ******************************************************************************/
void bumper_car()
{
  if(bumper_car_flag==1)
  {
      if(Total_distance>dis_hcjj1)
      {
          huiche();
      }  
      else
      {
         if(Total_distance<dis_qdhc)
            c_mode=2;     //����������
         else
            c_mode=1;     //����
      }     
  }
  else
  {
    bumper_car_flag=0;
    c_mode=1;
  }
}

/*******************************************************************************
 * Function Name: deal_info();
 * Description  : ������Ϣ
 * Author Data  : 2018/4/9 by Lcy
 ******************************************************************************/
void  deal_info(char mess)
{ 
  if(mess==Test) //���ͨѶ
  {
    if(tx_test>40) 
      tx_test=41;
    else 
    {
      tx_test++;
    }
  }
  if(tx_test>40)
  {
    if(mess==Start)    //����
    {
      uart_start_stop(1);      
    }
    else if(mess==Stop) //ͣ��
    {
      uart_start_stop(0);
    }
    else if(mess==Arrive) //���Ѿ�����ᳵ�� �����������
    {
      you_can_start=1;
    }
  }
}
/*******************************************************************************
 * Function Name: deal_wupan();
 * Description  : �ᳵ������ʶ��
 * Author Data  : 2018/6/5 by DLSZ
 ******************************************************************************/
void deal_wupan()
{
  int i;
for(i=70-right1;i>30;--i)
  {
    if((rightline_x[i-1]==rightline_x[i]==rightline_x[i+1])||(rightline_x[i]-rightline_x[i-1]>20))
    {
      buguize_ywd=1;
    i=10;
    }
    else 
    {
      buguize_ywd=0;
    }
  }
  for(i=70-left1;i>30;--i)
  {
    if((leftline_x[i]==leftline_x[i-1]==leftline_x[i+1])||(leftline_x[i-1]-leftline_x[i]>20))
    {
      buguize_zwd=1;
      i=10;
    }
      else 
      {
      buguize_zwd=0;
      }
  }
  for(i=70-right1;i>25;--i)
  {
    if(buguize_ywd==0&&rightline_x[i-1]-rightline_x[i]>0&&rightline_x[i-2]-rightline_x[i-3]>0&&rightline_x[i-2]-rightline_x[i-3]<15)
    {
      ywdmeiwupan=1;
    i=10;
    }
    else
    {
      ywdmeiwupan=0;
    }
  }
  for(i=70-left1;i>25;--i)
  {
    if(buguize_zwd==0&&leftline_x[i]-leftline_x[i-1]>0&&leftline_x[i-3]-leftline_x[i-2]>0&&leftline_x[i-3]-leftline_x[i-2]<15)
    {
      zwdmeiwupan=1;
    i=10;
    }
    else
    {
      zwdmeiwupan=0;
    }
  }
  
  ////////////////////����ᳵֱ������///////////////////
for(i=70-right1;i>30;--i)
  {
    if((rightline_x[i-1]==rightline_x[i]==rightline_x[i+1])||(rightline_x[i]-rightline_x[i-1]>13))
    {
      buguize_yzd=1;
    i=10;
    }
    else 
    {
      buguize_yzd=0;
    }
  }
  for(i=70-left1;i>30;--i)
  {
    if((leftline_x[i]==leftline_x[i-1]==leftline_x[i+1])||(leftline_x[i-1]-leftline_x[i]>13))
    {
      buguize_zzd=1;
      i=10;
    }
      else 
      {
      buguize_zzd=0;
      }
  }

  
  for(i=70-right1;i>25;--i)
  {
    if(buguize_yzd==0&&rightline_x[i-1]-rightline_x[i]>0&&rightline_x[i-2]-rightline_x[i-3]>0&&rightline_x[i-2]-rightline_x[i-3]<13)
    {
      yzdmeiwupan=1;
    i=10;
    }
    else
    {
      yzdmeiwupan=0;
    }
  }
  for(i=70-left1;i>25;--i)
  {
    if(buguize_zzd==0&&leftline_x[i]-leftline_x[i-1]>0&&leftline_x[i-3]-leftline_x[i-2]>0&&leftline_x[i-3]-leftline_x[i-2]<13)
    {
      zzdmeiwupan=1;
    i=10;
    }
    else
    {
      zzdmeiwupan=0;
    }
  }
}