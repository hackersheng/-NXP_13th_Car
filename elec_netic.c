/*
 * @file       eles_netic.c   
 * @author     DLSZ
 * @date       2018-05-15
 */

#include "common.h"
#include "include.h"

/////////////////////////////////  变量表   ////////////////////////////////////
uint32 elec_c=0;
uint32 elec_L=0;                      //
uint32 elec_R=0;
uint32 elec_L1,elec_L2,elec_L3,elec_L4,elec_L5;
uint32 elec_R1,elec_R2,elec_R3,elec_R4,elec_R5;

/////////////////////////////////  函数表   ////////////////////////////////////
void elec_get_mess();                      //获取电感采集值


/*******************************************************************************
 * Function Name: elec_get_mess();
 * Description  : 获取电感采集值
 * Author Data  : 2018/5/15 by DLSZ
 ******************************************************************************/
void elec_get_mess()
{ 
  elec_L1=adc_once(ELEC_L, ADC_10bit);
  
  elec_R1=adc_once(ELEC_R, ADC_10bit);
  
  elec_L=(elec_L1+elec_L2+elec_L3+elec_L4)/4;
  if(elec_L>9999)
    elec_L=9999;
  
  elec_R=(elec_R1+elec_R2+elec_R3+elec_R4)/4;  
  if(elec_R>9999)
    elec_R=9999;  
  
  elec_c=(elec_L*elec_R)/abs(elec_L-elec_R);
  
  elec_L2=elec_L1;
  elec_L3=elec_L2;
  elec_L4=elec_L3;
  elec_L5=elec_L4;
  
  elec_R2=elec_R1;
  elec_R3=elec_R2;
  elec_R4=elec_R3;
  elec_R5=elec_R4;

}