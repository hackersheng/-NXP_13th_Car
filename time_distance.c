/*
 * @file       time_distance.c   
 * @author     DLSZ
 * @date       2018-04-12
 */

#include "include.h"
#include "common.h"

uint16 dis_hcjj1=800;             //�ᳵʶ���� 
uint16 dis_hcjj2=800;             //�ᳵʶ���� 
/////////*******������־�������******//////////
uint32 dist_qdhc=0;                  //���ᳵ
uint32 dist_hdjc=0;                  //�������
uint32 dist_rhd=0;                   //�뻷��
uint32 dist_chd=0;                   //������
uint32 dist_spd=0;                   //���µ�
uint32 dist_xpd=0;                   //���µ�
uint32 dist_hdjj=0;                  //������� 
uint32 dist_hcjj=0;                  //�ᳵʶ����
uint32 dist_hcjl=0;                  //�ᳵ����
uint32 dist_hzjl=0;                  //��������

/////////*******�������ʱ������******//////////
uint32 time_hcdd=0;           //�ᳵ�ȴ�
uint32 time_pdjg=0;           //�µ����  

/////////////////////////////////  ������   ////////////////////////////////////
uint32 system_time=0;          //����ʱ��
uint8 time_en=0;            //��ʱʹ�ܱ�ʶλ
uint32 time_time=0;        //��ʱ
uint8 time_flag=0;


/*******************************************************************************
 * Function Name: time_system();
 * Description  : ϵͳʱ��
 * Author Data  : 2018/5/15 by DLSZ
 ******************************************************************************/
void time_system()
{
   static int i=0;
   if(time_en)
   {
     i++;
     if(i==1000)
     {
       system_time=system_time+1; //ϵͳʱ���ʱ
       i=0;
     }
   }
   switch(system_time)   //��λ�� s
   {
       case 1000 :
       break; 
       case 2000 :      
       break;       //ͣ��
   }
}

/*******************************************************************************
 * Function Name: time_open(uint32 time);
 * Description  : ����һ�μ�ʱ
 * Author Data  : 2018/5/15 by DLSZ
 ******************************************************************************/
int time_open(uint32 time)
{
  if(time_time==0&&time_flag!=1)
  {
    time_time=time;
  }
  
  if(time_time==0)    
    return 1;
  else
    return 0;
}
/*******************************************************************************
 * Function Name: time_dis_limit();
 * Description  : ʱ��,��������    �������ñ�־λ
 * Author Data  : 2018/5/15 by DLSZ
 ******************************************************************************/
void time_dis_limit()
{
  /* �µ� */
  if(ramp_flag==3&&dist_spd==0)
    dist_spd=Total_distance;
  if(ramp_flag==3&&(Total_distance-dist_spd>dis_spd))
  {
    ramp_flag=2;
    dist_spd=0;
  }
  if(ramp_flag==2&&dist_xpd==0)
    dist_xpd=Total_distance;
  if(ramp_flag==2&&(Total_distance-dist_xpd>dis_xpd))
  {
    ramp_flag=1; 
    dist_xpd=0;
    time_pdjg=system_time;
    start_spot=start_spot_last;
  }
  
  if((system_time-time_pdjg>tim_pdjg)&&(time_pdjg>0))
  {
    ramp_flag=0;
    time_pdjg=0;
  }

  /* ���� */
  if(((roundo_left_flag==2)||(roundo_right_flag==2))&&(dist_hdjc==0))
    dist_hdjc=Total_distance;
  
  if((Total_distance-dist_hdjc>dis_hdjc)&&(dist_hdjc>0))
  {
    dist_hdjc=0;
    roundo_left_flag=0;
    roundo_right_flag=0;
    speedmax=speedmax2;
  }
  
  
  if(((roundo_left_flag==1)||(roundo_right_flag==1))&&(dist_rhd==0))
    dist_rhd=Total_distance;
  
  if((Total_distance-dist_rhd>dis_rhd)&&(dist_rhd>0))
  {
    dist_rhd=0;
    roundo_left_flag=0;
    roundo_right_flag=0;
    speedmax=speedmax2+5;
  }
  
  if(((roundo_leftout_flag==1)||(roundo_rightout_flag==1))&&(dist_chd==0))
    dist_chd=Total_distance; 
  
  if((Total_distance-dist_chd>dis_chd)&&(dist_chd>0))
  {
    dist_chd=0;
    roundo_leftout_flag=0;
    roundo_rightout_flag=0;
    roundo_flag=0;
    roundo_left=0;
    roundo_right=0;
    dist_hdjj=Total_distance;
    special_roundo=0;
  }
  if((Total_distance-dist_hdjj>dis_hdjj)&&(dist_hdjj>0))
  {
    special_roundo=1;
    dist_hdjj=0;
  }
  /* �ᳵ */
  if(huiche_flag==2&&dist_hcjl==0)
  {
    dist_hcjl=Total_distance;
  }
  if((Total_distance-dist_hcjl>dis_hcjl)&&(dist_hcjl>0))
  {
    dist_hcjl=0;
    huiche_flag=1;
    dist_hcjj=Total_distance;
    dist_hzjl=Total_distance;
  }
  if((Total_distance-dist_hcjj>dis_hcjj2)&&(dist_hcjj>0))
  {
    huiche_flag=0;
    dist_hcjj=0;
    you_can_start=0;
  }
  if((Total_distance-dist_hzjl>dis_hzjl)&&(dist_hzjl>0))
  {
    speedmax=speedmax2;
    dist_hzjl=0;
  }
}