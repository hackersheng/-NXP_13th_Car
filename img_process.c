/*
 * @file       image_process.c   
 * @author     DLSZ
 * @date       2018-01-13
 */
   
#include "common.h"
#include "include.h"

float  quan_4[use_line]=
{
   0.10,  0.11,  0.12,  0.13,  0.14,  0.16,  0.18,  0.20,  0.22,  0.24,
   0.27,  0.30,  0.33,  0.36,  0.39,  0.43,  0.47,  0.51,  0.55,  0.59,
   0.64,  0.69,  0.74,  0.79,  0.84,  0.90,  0.96,  1.02,  1.08,  1.14,
   1.14,  1.08,  1.02,  0.96,  0.90,  0.84,  0.79,  0.74,  0.69,  0.64,
   0.59,  0.55,  0.51,  0.47,  0.43,  0.39,  0.36,  0.33,  0.30,  0.27,
   0.24,  0.22,  0.20,  0.18,  0.16,  0.14,  0.13,  0.12,  0.11,  0.10,
   0.10,  0.10,  0.10,  0.10,  0.10,  0.10,  0.10,  0.10,  0.10,  0.10, 
};
float  quan_3[use_line]=
{
   0.10,  0.11,  0.12,  0.13,  0.14,  0.16,  0.18,  0.20,  0.22,  0.24,
   0.27,  0.30,  0.33,  0.36,  0.39,  0.43,  0.47,  0.51,  0.55,  0.59,
   0.64,  0.69,  0.74,  0.79,  0.84,  0.90,  0.96,  1.02,  1.08,  1.14,
   1.21,  1.28,  1.35,  1.42,  1.49,  1.57,  1.65,  1.73,  1.81,  1.89,
   1.98,  2.07,  2.16,  2.25,  2.34,  2.44,  2.54,  2.64,  2.74,  2.84,
   2.95,  3.06,  3.17,  3.28,  3.39,  3.51,  3.63,  3.75,  3.87,  3.99,
   4.12,  4.25,  4.38,  4.51,  4.64,  5.0,   5.1,   5.2,   5.3,   5.4, 
};
float  quan_2[use_line]=
{
   0.10,  0.11,  0.12,  0.13,  0.14,  0.16,  0.18,  0.20,  0.22,  0.24,
   0.27,  0.30,  0.33,  0.36,  0.39,  0.43,  0.47,  0.51,  0.55,  0.59,
   0.64,  0.69,  0.74,  0.79,  0.84,  0.90,  0.96,  1.02,  1.08,  1.14,
   1.21,  1.28,  1.35,  1.42,  1.49,  1.57,  1.65,  1.73,  1.81,  1.89,
   1.98,  2.07,  2.16,  2.25,  2.34,  2.44,  2.54,  2.64,  2.74,  2.84,
   2.95,  3.06,  3.17,  3.28,  3.39,  4.51,  4.63,  4.75,  4.87,  4.99,
   6.12,  6.25,  6.38,  6.51,  6.64,  5.0,   5.1,   5.2,   5.3,   5.4, 
};
float  quan_1[use_line]=
{
   0.10,  0.11,  0.12,  0.13,  0.14,  0.16,  0.18,  0.20,  0.22,  0.24,
   0.27,  0.30,  0.33,  0.36,  0.39,  0.43,  0.47,  0.51,  0.55,  0.59,
   0.64,  0.69,  0.74,  0.79,  0.84,  0.90,  0.96,  1.02,  1.08,  1.14,
   1.21,  1.28,  1.35,  1.42,  1.49,  1.57,  1.65,  1.73,  1.81,  1.89,
   1.98,  2.07,  2.16,  2.25,  2.34,  2.44,  2.54,  2.64,  2.74,  2.84,
   3.95,  4.06,  4.17,  4.28,  4.39,  4.51,  4.63,  4.75,  4.87,  4.99,
   6.12,  6.25,  6.38,  6.51,  6.64,  5.0,   5.1,   5.2,   5.3,   5.4, 
};

/////////////////////////////////  变量表   ////////////////////////////////////
uint8 img1[use_line][128];                      // 二维数组，用来储存解压后的图像
uint8 leftline_x[use_line];                    // 一维数组，用来储存左边界横向坐标
uint8 rightline_x[use_line];                  // 一维数组，用来储存右边界横向坐标
uint8 midline_x[use_line];                   // 一维数组，用来储存中线横向坐标
uint8 width_x[use_line]; 
uint8 alone_line=64;                        //增大往左
uint8 special_flag=0;
uint8 start_spot=10;
uint8 end_spot=use_line-5;
uint8 c_mode=1;
uint8 youxiao=0;
uint8 yunsuan=0;

uint8 oval_ox=0;
uint8 oval_oy=0;

uint16 gongshi1=100;
uint16 gongshi2=300;

/////////////////////////////////  变量表   ////////////////////////////////////
uint8 left1=0;
uint8 left2=0;
uint8 left3=0;
uint8 right1=0;
uint8 right2=0;
uint8 right3=0;

uint8 left_1=0;
uint8 left_2=0;
uint8 left_3=0;
uint8 left_4=0;
uint8 left_5=0;
uint8 left_6=0;
uint8 right_1=0;
uint8 right_2=0;
uint8 right_3=0;
uint8 right_4=0;
uint8 right_5=0;
uint8 right_6=0;
   
/////////////////////////////////  函数表   ////////////////////////////////////
void img_ps();                            // 图像处理
void dis_line();                         // 画线
void line_init();
void oval(uint8 oval_x,uint8 oval_y,int8 zf);
void find_mid();                        // 找中线
void width_col();
void sos();
int sum_servo_angle();
int sum_servo();
void special();
void special2();


/*******************************************************************************
 * Function Name: img_ps();
 * Description  : 图像处理
 * Author Data  : 2018/1/13 by Lcy
 ******************************************************************************/
void img_ps()
{
    if(c_mode==1)
    {
      img_unzip_1((uint8 *) img1, (uint8 *) imgbuff);
    }
    else if(c_mode==2)
    {
      img_unzip_2((uint8 *) img1, (uint8 *) imgbuff);
    }
    else if(c_mode==3)
    {
      img_unzip_3((uint8 *) img1, (uint8 *) imgbuff);
    }
    else
    {
      img_unzip_1((uint8 *) img1, (uint8 *) imgbuff);
    }

    dis_line();
    numbre_renew1();
    special();
    special2();
    special_element();
    sos(); 
    find_mid();
    width_col();
    system_flag=1;
    if(Total_distance<dis_qdhc||huiche_cishu==2|| huiche_cishu==3)
      servo_angle_new=sum_servo();
    else
      servo_angle_new=sum_servo_angle();
}
/*******************************************************************************
 * Function Name: dis_line();
 * Description  : 画线
 * Author Data  : 2018/1/14 by Lcy
 ******************************************************************************/
void dis_line()
{
    for(int i = 0; i < use_line; ++i)
    {
        img1[i][0]=0;       
        img1[i][1]=0;
        img1[i][2]=0;
        img1[i][3]=0;
        img1[i][127]=0;   
        img1[i][126]=0;     
        img1[i][125]=0;     
    }        
}
/*******************************************************************************
 * Function Name: oval();
 * Description  : 画椭圆
 * Author Data  : 2018/4/22 by Lcy Xjl Wk
 ******************************************************************************/
void oval(uint8 oval_x,uint8 oval_y,int8 zf)
{
  float x0,y0,x1,y1;
  y0=oval_y;
  x0=69;
  x1=69-oval_x;
  
  uint8 x,y;
  if(zf<0)
  {
    y1=oval_y;
    for(float i=pi/2;i<=pi;i+=0.03)
    {
        y=(uint8)(y0+y1*cosf(i));
        x=(uint8)(x0-x1*sinf(i));
        y=constrain_int16(y,5+oval_x/5,106); //5+oval_x/5
        x=constrain_int16(x,2,69);
        img1[x][y]=0;
        img1[x-1][y]=0;
        img1[x][y-1]=0;
        img1[x-2][y]=0;
        img1[x][y-2]=0;
        img1[x-1][y-1]=0;
        img1[x-2][y-2]=0;
        img1[x-1][y-2]=0;
        img1[x-2][y-1]=0;
    }  
  }
  if(zf>0)
  {
    y1=128-oval_y;
    for(float i=pi/2;i<=pi;i+=0.03)
    {
        y=(uint8)(y0-y1*cosf(i));
        x=(uint8)(x0-x1*sinf(i));  
        y=constrain_int16(y,22,123-oval_x/5);//123-oval_x/5
        x=constrain_int16(x,2,69);
        img1[x][y]=0;
        img1[x-1][y]=0;
        img1[x][y+1]=0;
        img1[x-2][y]=0;
        img1[x][y+2]=0;
        img1[x-1][y+1]=0;
        img1[x-2][y+2]=0;
        img1[x-1][y+2]=0;
        img1[x-2][y+1]=0;
        
    }  
  }
}
/*******************************************************************************
 * Function Name: line_init();
 * Description  : 数组初始化
 * Author Data  : 2018/4/14 by Lcy
 ******************************************************************************/
void line_init()
{
    for(int i = 0; i < use_line; ++i)
    {   
        leftline_x[i]=1;                    // 一维数组，用来储存左边界横向坐标
        rightline_x[i]=127;                // 一维数组，用来储存右边界横向坐标 
        midline_x[i]=64;                  // 一维数组，用来储存中线横向坐标        
    }        
}
/*******************************************************************************
 * Function Name: food_mid1();
 * Description  : 找中线
 * Author Data  : 2018/1/21 by Lcy
 ******************************************************************************/
void find_mid1()
{
    int i,j;
    int old_mid=0;
    uint8 find_ok=0;
    
    line_init();
    for( j = 2; j < 125; j++)
    {      
        if(img1[use_line-1][j]==0&&img1[use_line-1][j+1]==0&&img1[use_line-1][j+2]==255)
        {
            leftline_x[use_line-1]=j;
            break;
        }
    }
    for( j = 126; j > 2; j--)
    {      
        if(img1[use_line-1][j]==0&&img1[use_line-1][j-1]==0&&img1[use_line-1][j-2]==255 )
        {
            rightline_x[use_line-1]=j;
            break;
        }
    }
    midline_x[use_line-1]=(rightline_x[use_line-1]+leftline_x[use_line-1])/2;   
    old_mid=midline_x[use_line-1];
    
    for( i = use_line-2; i >= 0; i--)
    {         
         for( j=old_mid;j>=2;j--)
         {
            if(img1[i][j]==0&&img1[i][j+1]==0&&img1[i][j+2]==255)                   
            {              
                leftline_x[i]=j;
                find_ok+=1;
                break;            
            }        
         }       
         for(j=old_mid;j<=126;j++)
         {
            if(img1[i][j]==0&&img1[i][j-1]==0&&img1[i][j-2]==255)           
            {
                rightline_x[i]=j;
                find_ok+=1;
                break;
            }               
         }
         if(find_ok==2)
         {
            if(img1[i][(rightline_x[i]+leftline_x[i])/2]==0||(abs(midline_x[i+1]-leftline_x[i])<6)||(abs(midline_x[i+1]-rightline_x[i])<6))
              break;
            midline_x[i]=(rightline_x[i]+leftline_x[i])/2; 
            old_mid=midline_x[i];      
            find_ok=0;
         }
         else
           break;     
     }
}
/*******************************************************************************
 * Function Name: food_mid2();
 * Description  : 找中线
 * Author Data  : 2018/6/2 by Lcy
 ******************************************************************************/
void find_mid2()
{
  
}
/*******************************************************************************
 * Function Name: food_mid3();
 * Description  : 找中线
 * Author Data  : 2018/6/12 by Lcy
 ******************************************************************************/
void find_mid3()
{

}
/*******************************************************************************
 * Function Name: void width_col();
 * Description  : 宽度
 * Author Data  : 2018/4/20 by Lcy
 ******************************************************************************/
void width_col()
{
    for(int i = 0; i < use_line; ++i)
    {
      width_x[i]=rightline_x[i]-leftline_x[i];  
    }  
}
/*******************************************************************************
 * Function Name: void sos();
 * Description  : 急停
 * Author Data  : 2018/1/21 by Lcy
 ******************************************************************************/
void sos()
{
     if(elec_L==0&&elec_R==0&&servo_flag==1)
      car_stop();
}
/*******************************************************************************
 * Function Name: sum_servo_angle();
 * Description  : 新算法算偏差
 * Author Data  : 2018/6/10 by Lcy
 ******************************************************************************/
int sum_servo_angle()
{
    int32 sum=0;
    youxiao=0;
    yunsuan=0;
    
    for(int i = end_spot; i > start_spot; --i)
    {   
       if(leftline_x[i]!=1&&rightline_x[i]!=127)
       {
          sum=sum+(int32)((midline_x[i]-alone_line)*quan_1[i]);
          yunsuan+=1;
          if(midline_x[i]!=64)
            youxiao+=1;
       }
       else
          i = start_spot;
    } 

    return (int32)(sum*(float)(0.10+(float)(gongshi1*(end_spot-start_spot-yunsuan)+(speedmax-15)*(yunsuan-youxiao)+(float)(gongshi2*(end_spot-start_spot)/youxiao))/1000)); 

}
/*******************************************************************************
 * Function Name: sum_servo();
 * Description  : 起跑线算偏差
 * Author Data  : 2018/7/10
 ******************************************************************************/
/*
int sum_servo()
{
    int32 sum=0;
    midline_x[end_spot]=64;
    
    for(int i = end_spot; i > start_spot; --i)
    {   
       if(leftline_x[i]!=1&&rightline_x[i]!=127&&abs(midline_x[i]-midline_x[i+1])<5)
       {
          sum=sum+(int32)((midline_x[i]-alone_line)*quan_1[i]);
       }
       else
          i = start_spot;
    } 
    return sum;

}
*/
/*
int sum_servo()
{
    int32 sum=0;
    
    for(int i = start_spot; i < end_spot; ++i)
    {   
       if(leftline_x[i]!=1&&rightline_x[i]!=127&&abs(midline_x[i-1]-midline_x[i])<5)
       {
          sum=sum+(int32)((midline_x[i]-alone_line)*quan_1[i]);
       }
       else
          i = end_spot;
    } 
    return sum;
}
*/
int sum_servo()
{
    int32 sum=0;
    youxiao=0;
    yunsuan=0;
    
    for(int i = end_spot; i > start_spot; --i)
    {   
       if(leftline_x[i]!=1&&rightline_x[i]!=127)
       {
          sum=sum+(int32)((midline_x[i]-alone_line)*quan_4[i]);
          yunsuan+=1;
          if(midline_x[i]!=64)
            youxiao+=1;
       }
       else
          i = start_spot;
    } 
    return (int32)(sum*(float)(2+(float)(gongshi1*(end_spot-start_spot-yunsuan)+(speedmax-15)*(yunsuan-youxiao)+(float)(gongshi2*(end_spot-start_spot)/youxiao))/1000)); 

}
/*******************************************************************************
 * Function Name: food_mid();
 * Description  : 根据车模式找中线
 * Author Data  : 2018/6/2 by Lcy
 ******************************************************************************/
void find_mid() 
{
    if(car_mode==1)
    {
      find_mid1();
    }
    else if(car_mode==2)
    {
      find_mid2();
    }
    else
    {
      find_mid3();
    }
}
/*******************************************************************************
 * Function Name: special();
 * Description  : 特殊情况感应
 * Author Data  : 2018/1/25 by Lcy
 ******************************************************************************/
void special()
{
  int i;
  left1=0;
  left2=0;
  left3=0;
  right1=0;
  right2=0;
  right3=0;
  
  for(i = use_line-1; i >=6; --i)
  {
    if (leftline_x[i]==2&&img1[i][4]==255)
    {
      left1=left1+1;
    }
    if(leftline_x[i]!=2)
    {
      break;
    }
  }
  for( i=i ; i >=6; --i)
  {
    if (leftline_x[i]!=2&&img1[i][leftline_x[i]+2]==255)
    {
      left2=left2+1;
    }
    if(leftline_x[i]==2)
    {
      break;
    }
  }
  for( i=i ; i >=6; --i)
  {
    if (leftline_x[i]==2&&img1[i][4]==255)
    {
      left3=left3+1;
    }
    if(leftline_x[i]!=2)
    {
      break;
    }
  }

  
  for(i = use_line-1; i >=6; --i)
  {
    if (rightline_x[i]==126&&img1[i][124]==255)
    {
      right1=right1+1;
    }
    if(rightline_x[i]!=126)
    {
      break;
    }
  }
  for( i=i ; i >=6; --i)
  {
    if (rightline_x[i]!=126&&img1[i][rightline_x[i]-2]==255)
    {
      right2=right2+1;
    }
    if(rightline_x[i]==126)
    {
      break;
    }
  }
  for( i=i ; i >=6; --i)
  {
    if (rightline_x[i]==126&&img1[i][124]==255)
    {
      right3=right3+1;
    }
    if(rightline_x[i]!=126)
    {
      break;
    }
  } 

}
/*******************************************************************************
 * Function Name: special2();
 * Description  : 
 * Author Data  : 2018/7/5 by DLSZ
 ******************************************************************************/
void special2()
{
  int i;
  int yan=0;       //-1，下降沿，连续，+1，上升沿，连续，-2，下降沿，间断
  uint8 then=1;    //继续
  left_1=0;
  left_2=0;
  left_3=0;
  left_4=0;
  left_5=0;
  left_6=0;
  right_1=0;
  right_2=0;
  right_3=0;
  right_4=0;
  right_5=0;
  right_6=0;
  
  /* 左1 */
  for(i = use_line-1; i >=20; --i)
  {
    left_1+=1;
    if(leftline_x[i]-leftline_x[i-1]>0&&leftline_x[i]-leftline_x[i-1]<5)//上升沿，连续
    {
      yan=1;break;
    }
    if(leftline_x[i-1]-leftline_x[i]>5&&leftline_x[i-1]-leftline_x[i]<20)//下降沿，间断
    {
      yan=-2;break;
    }
    if(leftline_x[i]==1)
    {
      yan=0;then=0;break;
    }
  }
  /* 左2 */
  for( i=i-1 ; i >=0; --i)
  {
    if(leftline_x[i]==1)
    {
      yan=0;then=0;break;
    }
    if(leftline_x[i-1]-leftline_x[i]>=0&&yan==1&&then==1)//下降沿，连续
    {
      yan=-1;break;
    }
    if(leftline_x[i]-leftline_x[i-1]>0&&leftline_x[i]-leftline_x[i-1]<4&&yan==-2&&then==1)//上升沿，连续
    {
      yan=1;break;
    }
    left_2+=1;
  }
  /* 左3 */
  for( i=i-1 ; i >=0; --i)
  {
    if(leftline_x[i]==1)
    {
      yan=0;then=0;break;
    }
    if(leftline_x[i-1]-leftline_x[i]>4&&leftline_x[i-1]-leftline_x[i]<15&&yan==-1&&then==1)//下降沿，间断
    {
      yan=-2;break;
    }
    if(leftline_x[i-1]-leftline_x[i]>=0&&yan==1&&then==1)//下降沿，连续
    {
      yan=-1;break;
    }
    left_3+=1;
  }
  /* 左4 */
  for( i=i-1 ; i >=0; --i)
  {
    if(leftline_x[i]==1)
    {
      yan=0;then=0;break;
    }
    if(leftline_x[i]-leftline_x[i-1]>0&&leftline_x[i]-leftline_x[i-1]<3&&yan==-2&&then==1)//上升沿，连续
    {
      yan=1;break;
    }
    if(leftline_x[i-1]-leftline_x[i]>3&&leftline_x[i-1]-leftline_x[i]<10&&yan==-1&&then==1)//下降沿，间断
    {
      yan=-2;break;
    }
    left_4+=1;
  }
  /* 左5 */
  for( i=i-1 ; i >=0; --i)
  {
    if(leftline_x[i]==1)
    {
      yan=0;then=0;break;
    }
    if(leftline_x[i-1]-leftline_x[i]>=0&&yan==1&&then==1)//下降沿，连续
    {
      yan=-1;break;
    }
    if(leftline_x[i]-leftline_x[i-1]>0&&leftline_x[i]-leftline_x[i-1]<2&&yan==-2&&then==1)//上升沿，连续
    {
      yan=1;break;
    }
    left_5+=1;
  }
  /* 左6 */
  for( i=i-1 ; i >=0; --i)
  {
    if(leftline_x[i]==1)
    {
      yan=0;then=0;break;
    }
    if(leftline_x[i-1]-leftline_x[i]>2&&leftline_x[i-1]-leftline_x[i]<8&&yan==-1&&then==1)//下降沿，间断
    {
      yan=-2;break;
    }
    if(leftline_x[i-1]-leftline_x[i]>=0&&yan==1&&then==1)//下降沿，连续
    {
      yan=-1;break;
    }
    left_6+=1;
  }

/******************************************************************************/  
  yan=0;
  then=1;
/******************************************************************************/ 
  
  /* 右1 */
  for(i = use_line-1; i >=20; --i)
  {
    right_1+=1;
    if(rightline_x[i-1]-rightline_x[i]>0&&rightline_x[i-1]-rightline_x[i]<5)//上升沿，连续
    {
      yan=1;break;
    }
    if(rightline_x[i]-rightline_x[i-1]>5&&rightline_x[i]-rightline_x[i-1]<20)//下降沿，间断
    {
      yan=-2;break;
    }
    if(rightline_x[i]==127)
    {
      yan=0;then=0;break;
    }
  }
  /* 右2 */
  for( i=i-1 ; i >=0; --i)
  {
    if(rightline_x[i]==127)
    {
      yan=0;then=0;break;
    }
    if(rightline_x[i]-rightline_x[i-1]>=0&&yan==1&&then==1)//下降沿，连续
    {
      yan=-1;break;
    }
    if(rightline_x[i-1]-rightline_x[i]>0&&rightline_x[i-1]-rightline_x[i]<4&&yan==-2&&then==1)//上升沿，连续
    {
      yan=1;break;
    }
    right_2+=1;
  }
  /* 右3 */
  for( i=i-1 ; i >=0; --i)
  {
    if(rightline_x[i]==127)
    {
      yan=0;then=0;break;
    }
    if(rightline_x[i]-rightline_x[i-1]>4&&rightline_x[i]-rightline_x[i-1]<15&&yan==-1&&then==1)//下降沿，间断
    {
      yan=-2;break;
    }
    if(rightline_x[i]-rightline_x[i-1]>=0&&yan==1&&then==1)//下降沿，连续
    {
      yan=-1;break;
    }
    right_3+=1;
  }
  /* 右4 */
  for( i=i-1 ; i >=0; --i)
  {
    if(rightline_x[i]==127)
    {
      yan=0;then=0;break;
    }
    if(rightline_x[i-1]-rightline_x[i]>0&&rightline_x[i-1]-rightline_x[i]<3&&yan==-2&&then==1)//上升沿，连续
    {
      yan=1;break;
    }
    if(rightline_x[i]-rightline_x[i-1]>3&&rightline_x[i]-rightline_x[i-1]<10&&yan==-1&&then==1)//下降沿，间断
    {
      yan=-2;break;
    }
    right_4+=1;
  }
  /* 右5 */
  for( i=i-1 ; i >=0; --i)
  {
    if(rightline_x[i]==127)
    {
      yan=0;then=0;break;
    }
    if(rightline_x[i]-rightline_x[i-1]>=0&&yan==1&&then==1)//下降沿，连续
    {
      yan=-1;break;
    }
    if(rightline_x[i-1]-rightline_x[i]>0&&rightline_x[i-1]-rightline_x[i]<2&&yan==-2&&then==1)//上升沿，连续
    {
      yan=1;break;
    }
    right_5+=1;
  }
  /* 右6 */
  for( i=i-1 ; i >=0; --i)
  {
    if(rightline_x[i]==127)
    {
      yan=0;then=0;break;
    }
    if(rightline_x[i]-rightline_x[i-1]>2&&rightline_x[i]-rightline_x[i-1]<8&&yan==-1&&then==1)//下降沿，间断
    {
      yan=-2;break;
    }
    if(rightline_x[i]-rightline_x[i-1]>=0&&yan==1&&then==1)//下降沿，连续
    {
      yan=-1;break;
    }
    right_6+=1;
  }  
}