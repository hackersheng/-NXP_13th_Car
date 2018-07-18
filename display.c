/*
 * @file       display.c   
 * @author     DLSZ
 * @date       2018-01-12
 */

#include "common.h"
#include "include.h"

#define color_cursor1 BLUE
#define color_cursor2 RED
#define color_line_1  WHITE
#define color_line_2  GBLUE
#define color_line_3  WHITE
#define color_line_4  BLUE
/////////////////////////////////  变量表   ////////////////////////////////////
const uint16 *bmp[1];                     // 关键字const用来定义常量
uint16 color[10];
int8 key_clear_flag;
int8 renew_flag; 
uint8 number_display_flag=0; 
uint8 OV7725_yuzhi=100;  
uint32 num_black[16];                   //一维数组，用来存储每格的黑点个数
uint8 width_y=60;

/////////////////////////////////  函数表   ////////////////////////////////////
void bmp_init();                          // bmp图片初始化
void bmp_display();                      // bpm图片显示
void camera_lcd();                      // 摄像头图像显示
void canshu_lcd();                     // 显示一些参数
void LCD_UI();                        // UI
void LCD_UI_0();
void LCD_UI_1();
void LCD_UI_2();
void LCD_UI_3();
void LCD_UI_4();
void LCD_UI_5();
void LCD_UI_6();
void color_change();
void color_init();
int num_color(uint32 number);
void numbre_renew();
void numbre_renew1();
void number_display();
void number_display1();
void width_display();
void img_cut();
void left_right_display();
void left_right_display2();
void beep();
/*******************************************************************************
 * Function Name: bmp_init();
 * Description  : bmp图片初始化
 * Author Data  : 2015/3/12 by Li
 ******************************************************************************/
void bmp_init()
{
    bmp[0]=ScreenBitmap;                // ScreenBitmap
}
/*******************************************************************************
 * Function Name: bmp_display();
 * Description  : bpm图片显示，根据str_new_tab进行切换
 * Author Data  : 2014/3/22 星期四, by Li
 ******************************************************************************/
void bmp_display()
{
    Site_t bmp_site     = {0, 0};                     // 显示图像左上角位置
    Size_t bmp_imgsize  = {128, 128};                // 图像大小
    Size_t bmp_size     = {128, 128};               // 显示区域图像大小

    LCD_Img_RGB565_Z(bmp_site,bmp_size,bmp[0],bmp_imgsize);
}
/*******************************************************************************
 * Function Name: key_lcd_clear();
 * Description  : 按键清屏
 * Author Data  : 2018/3/13 by Lcy
 ******************************************************************************/
void key_lcd_clear()
{
    if( key_clear_flag==1 )
    {
      key_clear_flag=0;
      LCD_clear(BLACK);
    }
} 
/*******************************************************************************
 * Function Name: camera_lcd();
 * Description  : 摄像头图像显示
 * Author Data  : 2018/1/21 by Lcy
 ******************************************************************************/
void camera_lcd()
{
    Site_t site = {0, 0}; 
    Size_t size = {128, use_line};                 // 显示区域图像大小   先列后行
    LCD_Img_gray(site, size,(uint8 *) img1);      // LCD_Img_Binary_Z     LCD_Img_gray_Z
}  
/*******************************************************************************
 * Function Name: canshu_lcd();
 * Description  : 显示一些参数
 * Author Data  : 2018/3/11 by Lcy
 ******************************************************************************/
void canshu_lcd()
{
    Site_t site1 = {5,110};   //x = 5 ,y = 110
    LCD_num(site1,L_speed, WHITE,BLACK);
    Site_t site2 = {55,110};   //x = 55 ,y = 110
    LCD_num(site2,123, WHITE,BLACK);
    Site_t site3 = {90,110};   //x = 100 ,y = 110
    LCD_num(site3,R_speed, WHITE,BLACK);
    Site_t site4 = {55,95};   //x = 55 ,y = 110
    LCD_num(site4,123, WHITE,BLACK);
}
/*******************************************************************************
 * Function Name: void lcd_UI();
 * Input Param  : 无
 * Output Param : 无
 * Description  : UI
 * Author Data  : 2018/3/13  by Lcy
 ******************************************************************************/
void LCD_UI()
{
    color_change();
    switch(flag_key_select)  //flag_key_select
    {
        case 0:
          {
            if( renew_flag==0)
            {
              renew_flag=1;
              key_lcd_clear();
              LCD_UI_0();    //显示菜单
            }
          }
          break;
        case 1:
          {
            key_lcd_clear();
            LCD_UI_1();     //显示赛道信息
          }
          break;
        case 2:
          {
            key_lcd_clear();
            LCD_UI_2();     //显示舵机参数
          }
          break;
        case 3:
          {
            key_lcd_clear();
            LCD_UI_3();     //显示电机参数
          }
          break;
        case 4:
          {
            key_lcd_clear();
            LCD_UI_4();     //显示其他
          }
          break;
        case 5:
          {
            if( renew_flag==0)
            {
              renew_flag=1;
              key_lcd_clear();
              LCD_UI_5();     //发车（停止刷屏）
            }
          }
          break;
        case 6:
          {
            key_lcd_clear();
            LCD_UI_6();     //显示设置
          }
          break;
    }
}
/*******************************************************************************
 * Function Name: void LCD_UI_0()
 * Input Param  : 无
 * Output Param : 无
 * Description  : UI显示菜单
 * Author Data  : 
 ******************************************************************************/
void LCD_UI_0()      
{
    Site_t site;
    Site_t site_m1 = {5,6};
    LCD_str(site_m1,"1 ", WHITE,BLACK);    //
    site.x = 20;
    site.y = 5;
    LCD_FSTR_CH(site,jiantou ,WHITE,BLACK) ;  
    site.x = 35;
    site.y = 5;
    LCD_FSTR_CH(site,track ,WHITE, color[1]) ;    //赛道信息         

    Site_t site_m2 = {5,26};
    LCD_str(site_m2,"2 ", WHITE,BLACK);           //
    site.x = 20;
    site.y = 25;
    LCD_FSTR_CH(site,jiantou ,WHITE,BLACK) ;  
    site.x = 35;
    site.y = 25;
    LCD_FSTR_CH(site,servo ,WHITE, color[2]) ;       //舵机参数

    Site_t site_m3 = {5,46};
    LCD_str(site_m3,"3 ", WHITE,BLACK);           //
    site.x = 20;
    site.y = 45;
    LCD_FSTR_CH(site,jiantou ,WHITE,BLACK) ;  
    site.x = 35;
    site.y = 45;
    LCD_FSTR_CH(site,motor ,WHITE, color[3]) ;      //电机参数

    Site_t site_m4= {5,66};
    LCD_str(site_m4,"4 ", WHITE,BLACK);                //
    site.x = 20;
    site.y = 65;
    LCD_FSTR_CH(site,jiantou ,WHITE,BLACK) ;  
    site.x = 35;
    site.y = 65;
    LCD_FSTR_CH(site,other ,WHITE, color[4]) ;    //其他参数

    Site_t site_m5 = {5,86};
    LCD_str(site_m5,"5 ", WHITE,BLACK);               //
    site.x = 20;
    site.y = 85;
    LCD_FSTR_CH(site,jiantou ,WHITE,BLACK) ;  
    site.x = 35;
    site.y = 85;
    LCD_FSTR_CH(site,start_go ,WHITE, color[5]) ;        //发车   

    Site_t site_m6 = {5,106};
    LCD_str(site_m6,"6 ", WHITE,BLACK);             //
    site.x = 20;
    site.y = 105;
    LCD_FSTR_CH(site,jiantou ,WHITE,BLACK) ;  
    site.x = 35;
    site.y = 105;
    LCD_FSTR_CH(site,set ,WHITE, color[6]) ;        //设置
}
/*******************************************************************************
 * Function Name: void LCD_UI_1()
 * Input Param  : 无
 * Output Param : 无
 * Description  : 显示赛道信息
 * Author Data  : 
 ******************************************************************************/
void LCD_UI_1()   
{
     camera_lcd();         // 摄像头图像显示     
     LCD_line(GBLUE);     //画出边线和中线
//   img_cut();

     Site_t site = {0,72};   //x = 10 ,y = 20
     Size_t size = {128,2};  // W = 50 ,H = 60
     LCD_rectangle(site, size, GBLUE);
     
     if( number_display_flag==1)
        left_right_display();
     else if(number_display_flag==2)
        left_right_display2();
     else if(number_display_flag==3)
        width_display();
     else if(number_display_flag==4)
     {
       Site_t site_m2 = {8,80+16};
       LCD_num_BC(site_m2,elec_L,4,color_line_4, color[9]);
       
       Site_t site_m22 = {88,80+16};
       LCD_num_BC(site_m22,elec_R,4,color_line_4, color[9]);
       
       Site_t site_m3 = {48,80};
       LCD_str(site_m3,"elec", WHITE,color[9]);
       Site_t site_m4 = {48,80+16};
       LCD_num_BC(site_m4,(uint32)(elec_c),4,color_line_4, color[9]);
     }
     else if(number_display_flag==5)
     {
       number_display1();
     }
     else
     {
         Site_t site_m0 = {0,76};
         LCD_FSTR_CH(site_m0,page_up ,WHITE, color[0]) ;     //上一页

         Site_t site_m1 = {0,80+16};
         LCD_str(site_m1,"L_L", WHITE,color[9]);
              
         if(leftval>=0)
         {
           Site_t site_m2 = {0,80+16*2};
           LCD_num_BC(site_m2,elec_L,3,color_line_4, color[9]);
         }
         else
         {
           Site_t site_m21 = {0,80+16*2};
           LCD_str(site_m21,"-", BLUE,BLACK);
           Site_t site_m22 = {8,80+16*2};
           LCD_num_BC(site_m22,abs(leftval),3,color_line_4, color[9]);
         }

         Site_t site_m3 = {32+2,80+16};
         LCD_str(site_m3,"S_D", WHITE,color[9]);
         Site_t site_m4 = {32+2,80+16*2};
         LCD_num_BC(site_m4,(uint32)(speed_now),3,color_line_4, color[9]);     

         Site_t site_m5 = {32*2+2,80+16};
         LCD_str(site_m5,"R_R", WHITE,color[9]); 
                
         if(rightval>=0)
         {
           Site_t site_m2 = {32*2+2,80+16*2};
           LCD_num_BC(site_m2,elec_R,3,color_line_4, color[9]);
         }
         else
         {
           Site_t site_m21 = {32*2+2,80+16*2};
           LCD_str(site_m21,"-", BLUE,BLACK);
           Site_t site_m22 = {32*2+8+2,80+16*2};
           LCD_num_BC(site_m22,abs(rightval),3,color_line_4, color[9]);
         }     
         
         Site_t site_m7 = {32*3 +8 ,80+16};
         LCD_str(site_m7,"D_J", WHITE,color[9]); 
         if(servo_angle>=0)
         {
           LCD_clear_xy(BLACK,96 ,112  );     //清屏
           Site_t site_m8 = {32*3 +8 ,80+16*2};
           LCD_num_BC(site_m8,servo_angle,3,color_line_4, color[9]);
         }
         else
         {
           Site_t site_m21 = {32*3,80+16*2};
           LCD_str(site_m21,"-", BLUE,BLACK);
           Site_t site_m8 = {32*3 +8 ,80+16*2};
           LCD_num_BC(site_m8,abs(servo_angle),3,color_line_4, color[9]);
         }
         
         
         
         Site_t site_m9 = {54,76};
         LCD_str(site_m9,"T", WHITE,color[1]);          //调整图像    

         Site_t site_m10 = {66,76};
         LCD_str(site_m10,"Y", WHITE,color[2]);          //调整阈值

         Site_t site_m18 = {80,76};
         LCD_FSTR_CH(site_m18,page_down ,WHITE, color[3]) ;     //下一页
     }

}
/*******************************************************************************
 * Function Name: void LCD_UI_2()
 * Input Param  : 无
 * Output Param : 无
 * Description  : 舵机参数
 * Author Data  : 
 ******************************************************************************/
void LCD_UI_2()           
{
        //下面显示不可调整的参数
         Site_t site_m1 = {64,0};
         LCD_str(site_m1,"0", color_line_3,BLACK);
         Site_t site_m2 = {100,0};   //x = 10 ,y = 20
         LCD_num_BC(site_m2,0,3, color_line_4,BLACK);

         Site_t site_m3 = {64,16};
         LCD_str(site_m3,"0", color_line_3,BLACK);
         Site_t site_m4 = {100,16};   //x = 10 ,y = 20       
         LCD_num_BC(site_m4,0,3, color_line_4,BLACK);

         Site_t site_m5 = {64,32};
         LCD_str(site_m5,"o_o", color_line_3,BLACK);
         Site_t site_m6 = {100,32};   //x = 10 ,y = 20
         LCD_num_BC(site_m6,roundo_flag,3, color_line_4,BLACK);

         Site_t site_m7 = {64,48};
         LCD_str(site_m7,"o_L", color_line_3,BLACK);
         Site_t site_m8 = {100,48};   //x = 10 ,y = 20
         LCD_num_BC(site_m8,roundo_left_flag,3, color_line_4,BLACK);

         Site_t site_m9 = {64,64};
         LCD_str(site_m9,"o_R",  color_line_3,BLACK);
         Site_t site_m10 = {100,64};   //x = 10 ,y = 20
         LCD_num_BC(site_m10,roundo_right_flag,3, color_line_4,BLACK);

         Site_t site_m11 = {64,80};
         LCD_str(site_m11,"L_O",  color_line_3,BLACK);
         Site_t site_m12 = {100,80};   //x = 10 ,y = 20
         LCD_num_BC(site_m12,roundo_leftout_flag,3, color_line_4,BLACK);

         Site_t site_m13 = {64,96};
         LCD_str(site_m13,"R_O",  color_line_3,BLACK);
         Site_t site_m14 = {100,96};   //x = 10 ,y = 20
         LCD_num_BC(site_m14,roundo_rightout_flag,3, color_line_4,BLACK);
      //下面显示可以调整的参数

         Site_t site_m21 = {0,0};
         LCD_FSTR_CH(site_m21,page_up ,WHITE, color[0]) ;     //上一页

         Site_t site_m22 = {0,16};
         LCD_str(site_m22,"Kp", color_line_1,BLACK);
         Site_t site_m23 = {32,16};   //x = 10 ,y = 20
         LCD_num_BC(site_m23,s_Kp,3, color_line_2,color[1]);

         Site_t site_m24 = {0,32};
         LCD_str(site_m24,"Td", color_line_1,BLACK);
         Site_t site_m25 = {32,32};   //x = 10 ,y = 20
         LCD_num_BC(site_m25,s_Td,3, color_line_2,color[2]);

         Site_t site_m28 = {0,48};
         LCD_str(site_m28,"0o0", color_line_1,BLACK);
         Site_t site_m29 = {32,48};   //x = 10 ,y = 20
         LCD_num_BC(site_m29,0,3, color_line_2,color[3]);

         Site_t site_m30 = {0,64};
         LCD_str(site_m30,"0o0", color_line_1,BLACK);
         Site_t site_m31 = {32,64};   //x = 10 ,y = 20
         LCD_num_BC(site_m31,0,3, color_line_2,color[4]);

         Site_t site_m32 = {0,80};
         LCD_str(site_m32,"cssz", color_line_1,BLACK);
         Site_t site_m33 = {32,80};   //x = 10 ,y = 20
         LCD_num_BC(site_m33,cssz_flag,3, color_line_2,color[5]);

         Site_t site_m34 = {0,96};
         LCD_str(site_m34,"flag", color_line_1,BLACK);
         Site_t site_m35 = {32,96};   //x = 10 ,y = 20
         LCD_num_BC(site_m35,servo_flag,3, color_line_2,color[6]);

         Site_t site_m26 = {0,112};
         LCD_FSTR_CH(site_m26,page_down ,WHITE, color[7]) ;     //下一页
         Site_t site_m27 = {64,112};
         LCD_FSTR_CH(site_m27,break_to ,WHITE, color[8]) ;     //返回主菜单

}
/*******************************************************************************
 * Function Name: void LCD_UI_3()
 * Input Param  : 无
 * Output Param : 无
 * Description  : 电机及其相关参数
 * Author Data  : 
 ******************************************************************************/
void LCD_UI_3()         
{
        //下面显示不可调整的参数

         Site_t site_m1 = {110,0};
         LCD_str(site_m1,"cm", color_line_3,BLACK); 
         
         Site_t site_m221 = {99,0};   
         Site_t site_m222 = {91,0};   
         Site_t site_m223 = {83,0};   
         Site_t site_m224 = {75,0};   
         if(Total_distance<10)
           LCD_num_BC(site_m221,(uint32)Total_distance,1, color_line_4,BLACK);
         else if(Total_distance<100)
           LCD_num_BC(site_m222,(uint32)Total_distance,2, color_line_4,BLACK);
         else if(Total_distance<1000)
           LCD_num_BC(site_m223,(uint32)Total_distance,3, color_line_4,BLACK);
         else    
           LCD_num_BC(site_m224,(uint32)Total_distance,4, color_line_4,BLACK);   
/*
         Site_t site_m3 = {64,16};
         LCD_str(site_m3,"0o0", color_line_3,BLACK);
         Site_t site_m4 = {96,16};   //x = 10 ,y = 20       
         LCD_num_BC(site_m4,0,3, color_line_4,BLACK);

         Site_t site_m5 = {64,32};
         LCD_str(site_m5,"0o0", color_line_3,BLACK);
         Site_t site_m6 = {93,32};   //x = 10 ,y = 20
         LCD_num_BC(site_m6,0,3, color_line_4,BLACK);

         Site_t site_m7 = {64,48};
         LCD_str(site_m7,"0o0", color_line_3,BLACK);
         Site_t site_m8 = {93,48};   //x = 10 ,y = 20
         LCD_num_BC(site_m8,0,3, color_line_4,BLACK);

         Site_t site_m9 = {64,64};
         LCD_str(site_m9,"0o0",  color_line_3,BLACK);
         Site_t site_m10 = {96,64};   //x = 10 ,y = 20
         LCD_num_BC(site_m10,0,3, color_line_4,BLACK);

         Site_t site_m11 = {64,80};
         LCD_str(site_m11,"0o0",  color_line_3,BLACK);
         Site_t site_m12 = {96,80};   //x = 10 ,y = 20
         LCD_num_BC(site_m12,0,3, color_line_4,BLACK);

         Site_t site_m13 = {64,96};
         LCD_str(site_m13,"0o0",  color_line_3,BLACK);
         Site_t site_m14 = {96,96};   //x = 10 ,y = 20
         LCD_num_BC(site_m14,0,3, color_line_4,BLACK);
*/
      //下面显示可以调整的参数
         Site_t site_m21 = {0,0};
         LCD_FSTR_CH(site_m21,page_up ,WHITE, color[0]) ;     //上一页

         Site_t site_m22 = {0,16};
         LCD_str(site_m22,"Kp", color_line_1,BLACK);
         Site_t site_m23 = {32,16};   //x = 10 ,y = 20
         LCD_num_BC(site_m23,m_kp,3, color_line_2,color[1]);

         Site_t site_m24 = {0,32};
         LCD_str(site_m24,"Td", color_line_1,BLACK);
         Site_t site_m25 = {32,32};   //x = 10 ,y = 20
         LCD_num_BC(site_m25,m_td,3, color_line_2,color[2]);

         Site_t site_m28 = {0,48};
         LCD_str(site_m28,"0o0", color_line_1,BLACK);
         Site_t site_m29 = {32,48};   //x = 10 ,y = 20
         LCD_num_BC(site_m29,0,3, color_line_2,color[3]);

         Site_t site_m30 = {0,64};
         LCD_str(site_m30,"0o0", color_line_1,BLACK);
         Site_t site_m31 = {32,64};   //x = 10 ,y = 20
         LCD_num_BC(site_m31,0,3, color_line_2,color[4]);

         Site_t site_m32 = {0,80};
         LCD_str(site_m32,"0o0", color_line_1,BLACK);
         Site_t site_m33 = {32,80};   //x = 10 ,y = 20
         LCD_num_BC(site_m33,0,3, color_line_2,color[5]);

         Site_t site_m34 = {0,96};
         LCD_str(site_m34,"gear", color_line_1,BLACK);
         Site_t site_m35 = {32,96};   //x = 10 ,y = 20
         LCD_num_BC(site_m35,speedmax,3, color_line_2,color[6]);

        
         Site_t site_m26 = {0,16*7};
         LCD_FSTR_CH(site_m26,page_down ,WHITE, color[7]) ;     //下一页
         Site_t site_m27 = {64,16*7};
         LCD_FSTR_CH(site_m27,break_to ,WHITE, color[8]) ;     //返回主菜单

}
/*******************************************************************************
 * Function Name: void LCD_UI_4()
 * Input Param  : 无
 * Output Param : 无
 * Description  : 其他参数
 * Author Data  : 
*******************************************************************************/
void LCD_UI_4()           
{
         //下面显示不可调整的参数
/*
         Site_t site_m1 = {64,0};
         LCD_str(site_m1,"0o0", color_line_3,BLACK);      
         Site_t site_m2 = {96,0};   //x = 10 ,y = 20
         LCD_num_BC(site_m2,0,3, color_line_4,BLACK);

         Site_t site_m3 = {64,16};
         LCD_str(site_m3,"0o0", color_line_3,BLACK);
         Site_t site_m4 = {96,16};   //x = 10 ,y = 20       
         LCD_num_BC(site_m4,0,3, color_line_4,BLACK);

         Site_t site_m5 = {64,32};
         LCD_str(site_m5,"0o0", color_line_3,BLACK);
         Site_t site_m6 = {93,32};   //x = 10 ,y = 20
         LCD_num_BC(site_m6,0,3, color_line_4,BLACK);

         Site_t site_m7 = {64,48};
         LCD_str(site_m7,"0o0", color_line_3,BLACK);
         Site_t site_m8 = {93,48};   //x = 10 ,y = 20
         LCD_num_BC(site_m8,0,3, color_line_4,BLACK);

         Site_t site_m9 = {64,64};
         LCD_str(site_m9,"0o0",  color_line_3,BLACK);
         Site_t site_m10 = {96,64};   //x = 10 ,y = 20
         LCD_num_BC(site_m10,0,3, color_line_4,BLACK);

         Site_t site_m11 = {64,80};
         LCD_str(site_m11,"0o0",  color_line_3,BLACK);
         Site_t site_m12 = {96,80};   //x = 10 ,y = 20
         LCD_num_BC(site_m12,0,3, color_line_4,BLACK);

         Site_t site_m13 = {64,96};
         LCD_str(site_m13,"0o0",  color_line_3,BLACK);
         Site_t site_m14 = {96,96};   //x = 10 ,y = 20
         LCD_num_BC(site_m14,0,3, color_line_4,BLACK);
*/
      //下面显示可以调整的参数
         Site_t site_m21 = {0,0};
         LCD_FSTR_CH(site_m21,page_up ,WHITE, color[0]) ;     //上一页

         Site_t site_m22 = {0,16};
         LCD_str(site_m22,"sta", color_line_1,BLACK);
         Site_t site_m23 = {32,16};   //x = 10 ,y = 20
         LCD_num_BC(site_m23,start_spot,3, color_line_2,color[1]);

         Site_t site_m24 = {0,32};
         LCD_str(site_m24,"end", color_line_1,BLACK);
         Site_t site_m25 = {32,32};   //x = 10 ,y = 20
         LCD_num_BC(site_m25,end_spot,3, color_line_2,color[2]);

         Site_t site_m28 = {0,48};
         LCD_str(site_m28,"0", color_line_1,BLACK);
         Site_t site_m29 = {32,48};   //x = 10 ,y = 20
         LCD_num_BC(site_m29,0,3, color_line_2,color[3]);

         Site_t site_m30 = {0,64};
         LCD_str(site_m30,"0", color_line_1,BLACK);
         Site_t site_m31 = {32,64};   //x = 10 ,y = 20
         LCD_num_BC(site_m31,0,3, color_line_2,color[4]);

         Site_t site_m32 = {0,80};
         LCD_str(site_m32,"rou", color_line_1,BLACK);
         Site_t site_m33 = {32,80};   //x = 10 ,y = 20
         LCD_num_BC(site_m33,special_roundo,3, color_line_2,color[5]);

         Site_t site_m34 = {0,96};
         LCD_str(site_m34,"c_m", color_line_1,BLACK);
         Site_t site_m35 = {32,96};   //x = 10 ,y = 20
         LCD_num_BC(site_m35,c_mode,3, color_line_2,color[6]);

        
         Site_t site_m26 = {0,16*7};
         LCD_FSTR_CH(site_m26,page_down ,WHITE, color[7]) ;     //下一页
         Site_t site_m27 = {64,16*7};
         LCD_FSTR_CH(site_m27,break_to ,WHITE, color[8]) ;     //返回主菜单

}
/*******************************************************************************
 * Function Name: void LCD_UI_5()
 * Input Param  : 无
 * Output Param : 无
 * Description  :
 * Author Data  : 
 ******************************************************************************/
void LCD_UI_5()           
{
         Site_t site_m28 = {32,90};
         LCD_FSTR_CH(site_m28,stop ,WHITE,  color[1]) ;     //停车
         Site_t site_m27 = {32,110};
         LCD_FSTR_CH(site_m27,break_to ,WHITE,  color[2]) ;     //返回主菜单
}

/*******************************************************************************
 * Function Name: void LCD_UI_6()
 * Input Param  : 无
 * Output Param : 无
 * Description  : 主要用于查看其他信息
 * Author Data  : 
*******************************************************************************/
void LCD_UI_6()          
{
        //下面显示不可调整的参数

         Site_t site_m1 = {64,0};
         LCD_str(site_m1,"time", color_line_3,BLACK);        
         Site_t site_m2 = {96,0};   //x = 10 ,y = 20
         LCD_num_BC(site_m2,system_time,3, color_line_4,BLACK);

         Site_t site_m3 = {64,16};
         LCD_str(site_m3,"ca_b", color_line_3,BLACK);
         Site_t site_m4 = {96,16};   //x = 10 ,y = 20       
         LCD_num_BC(site_m4,camera_boundary,3, color_line_4,BLACK);

         Site_t site_m5 = {64,32};
         LCD_str(site_m5,"yzhi", color_line_3,BLACK);
         Site_t site_m6 = {96,32};   //x = 10 ,y = 20
         LCD_num_BC(site_m6,OV7725_yuzhi,3, color_line_4,BLACK);

         Site_t site_m7 = {64,48};
         LCD_str(site_m7,"line", color_line_3,BLACK);
         Site_t site_m8 = {96,48};   //x = 10 ,y = 20
         LCD_num_BC(site_m8,alone_line,3, color_line_4,BLACK);

         Site_t site_m9 = {64,64};
         LCD_str(site_m9,"zdjs",  color_line_3,BLACK);
         Site_t site_m10 = {96,64};   //x = 10 ,y = 20
         LCD_num_BC(site_m10,jiasu,3, color_line_4,BLACK);

         Site_t site_m11 = {64,80};
         LCD_str(site_m11,"hnjs",  color_line_3,BLACK);
         Site_t site_m12 = {96,80};   //x = 10 ,y = 20
         LCD_num_BC(site_m12,roundo_jiasu,3, color_line_4,BLACK);

         Site_t site_m13 = {64,96};
         LCD_str(site_m13,"hwjs",  color_line_3,BLACK);
         Site_t site_m14 = {96,96};   //x = 10 ,y = 20
         LCD_num_BC(site_m14,roundo_jiansu,3, color_line_4,BLACK);

      //下面显示可以调整的参数
         Site_t site_m21 = {0,0};
         LCD_FSTR_CH(site_m21,page_up ,WHITE, color[0]) ;     //上一页

         Site_t site_m22 = {0,16};
         LCD_str(site_m22,"twin", color_line_1,BLACK);
         Site_t site_m23 = {32,16};   //x = 10 ,y = 20
         LCD_num_BC(site_m23,bumper_car_flag,3, color_line_2,color[1]);

         Site_t site_m24 = {0,32};
         LCD_str(site_m24,"gs1", color_line_1,BLACK);
         Site_t site_m25 = {32,32};   //x = 10 ,y = 20
         LCD_num_BC(site_m25,gongshi1,3, color_line_2,color[2]);

         Site_t site_m28 = {0,48};
         LCD_str(site_m28,"gs2", color_line_1,BLACK);
         Site_t site_m29 = {32,48};   //x = 10 ,y = 20
         LCD_num_BC(site_m29,gongshi2,3, color_line_2,color[3]);

         Site_t site_m30 = {0,64};
         LCD_str(site_m30,"jl1", color_line_1,BLACK);
         Site_t site_m31 = {32,64};   //x = 10 ,y = 20
         LCD_num_BC(site_m31,dis_hcjj1,4, color_line_2,color[4]);

         Site_t site_m32 = {0,80};
         LCD_str(site_m32,"jl2", color_line_1,BLACK);
         Site_t site_m33 = {32,80};   //x = 10 ,y = 20
         LCD_num_BC(site_m33,dis_hcjj2,4, color_line_2,color[5]);

         Site_t site_m34 = {0,96};
         LCD_str(site_m34,"gear", color_line_1,BLACK);
         Site_t site_m35 = {32,96};   //x = 10 ,y = 20
         LCD_num_BC(site_m35,speedmax,3, color_line_2,color[6]);

        
         Site_t site_m26 = {0,16*7};
         LCD_FSTR_CH(site_m26,page_down ,WHITE, color[7]) ;     //下一页
         Site_t site_m27 = {64,16*7};
         LCD_FSTR_CH(site_m27,break_to ,WHITE, color[8]) ;     //返回主菜单

}

/*******************************************************************************
  * Function Name: color_change()
  * Input Param  : 无
  * Output Param : 无
  * Description  : 颜色改变
  * Author Data  : 2018/3/13  by Lcy
  *****************************************************************************/
void color_change()
{
    int8 i;
    uint16 color_cursor;
    i=flag_key_l_u_0; //flag_key_l_u_0
    
   if(tx_test>40)
     color_cursor=color_cursor2;    //红色
   else
     color_cursor=color_cursor1;
   
   switch (flag_key_select)  //flag_key_select
    {
    case 0:
      {
        i=flag_key_l_u_0;   //flag_key_l_u_0
        color[i]= color_cursor;
      }
      break;
    case 1:
      {
        i=flag_key_l_u_1;  //flag_key_l_u_1
        color[i]= color_cursor;
      }
      break;
    case 2:
      {
        i=flag_key_l_u_2;  //flag_key_l_u_2
        color[i]=color_cursor;
      }
      break;
    case 3:
      {
        i=flag_key_l_u_3;  //flag_key_l_u_3
        color[i]= color_cursor;
      }
      break;
    case 4:
      {
        i=flag_key_l_u_4;  //flag_key_l_u_4
        color[i]= color_cursor;
      }
      break;
    case 5:
      {
        i=flag_key_l_u_5;  //flag_key_l_u_5
        color[i]= color_cursor;
      }
      break;
    case 6:
      {
        i=flag_key_l_u_6;  //flag_key_l_u_6
        color[i]= color_cursor;
      }
      break;
    }

}

/*******************************************************************************
  * Function Name: color_init();
  * Input Param  : 无
  * Output Param : 无
  * Description  : 颜色初始化
  * Author Data  : 2018/3/13  by Lcy
  *****************************************************************************/
void color_init()
{
     color[0]=BLACK;
     color[1]=BLACK;
     color[2]=BLACK;
     color[3]=BLACK;
     color[4]=BLACK;
     color[5]=BLACK;
     color[6]=BLACK;
     color[7]=BLACK;
     color[8]=BLACK;
     color[9]=BLACK;
}

/*******************************************************************************
 * Function Name: count_spot()
 * Input Param  : 起始行，起始列，结束行，结束列，存储数据
 * Author Data  : 2018/1/17 Lcy
*例如:      num_black[0]=count_spot(1,1,2,100)                    
 ******************************************************************************/
int count_spot( int H_start, int W_start, int H_end, int W_end)
{
    int i,j;
    uint32 sum=0;
      
    for(i=H_start;   i<H_end;     i++)
    {
        for(j=W_start;  j<W_end;     j++)
        {
            if(  img1[i][j]==0 )
            {
                sum=sum+1;
            }     
        }       
    }   
    return sum;
}
/*******************************************************************************
* Function Name: img_cut();
* Description  : 图像分割，将图像分成3*3
* Author Data  : 2018/1/17
*******************************************************************************/
void img_cut()
{
  //  9宫格
  /*
     Site_t site1 = {0,22};   //
     Size_t size1 = {128,1};  // 
     LCD_rectangle(site1, size1, BLUE);  
     
     Site_t site2 = {0,47};   //
     Size_t size2 = {128,1};  // 
     LCD_rectangle(site2, size2, BLUE); 
     
     Site_t site3 = {43,0};   //
     Size_t size3 = {1,70};  // 
     LCD_rectangle(site3, size3, BLUE);  
     
     Site_t site4 = {85,0};   //
     Size_t size4 = {1,70};  // 
     LCD_rectangle(site4, size4, BLUE); 
  */
  //  16宫格
     Site_t site1 = {0,17};   //
     Size_t size1 = {128,1};  // 
     LCD_rectangle(site1, size1, BLUE);  
     
     Site_t site2 = {0,35};   //
     Size_t size2 = {128,1};  // 
     LCD_rectangle(site2, size2, BLUE); 
     
     Site_t site3 = {0,53};   //
     Size_t size3 = {128,1};  // 
     LCD_rectangle(site3, size3, BLUE);  
     
     Site_t site4 = {34,0};   //
     Size_t size4 = {1,70};  // 
     LCD_rectangle(site4, size4, BLUE); 
     
     Site_t site5 = {65,0};   //
     Size_t size5 = {1,70};  // 
     LCD_rectangle(site5, size5, BLUE);  
     
     Site_t site6 = {96,0};   //
     Size_t size6 = {1,70};  // 
     LCD_rectangle(site6, size6, BLUE); 
  
}

/*******************************************************************************
* Function Name: number_display();
* Description  : 
* Author Data  : 2018/1/17
*******************************************************************************/
void number_display()
{
    Site_t site1 = {10,80};        //x = 10 ,y = 80         
    LCD_num(site1,num_black[0],num_color(num_black[0]),BLACK);

    Site_t site2 = {50,80};        //x = 50 ,y = 80
    LCD_num(site2,num_black[1],num_color(num_black[1]),BLACK);

    Site_t site3 = {90,80};        //x = 90 ,y = 80
    LCD_num(site3,num_black[2],num_color(num_black[2]),BLACK);      

    Site_t site4 = {10,93};       //x = 10 ,y = 93
    LCD_num(site4,num_black[3],num_color(num_black[3]),BLACK);

    Site_t site5 = {50,93};       //x = 50 ,y = 93
    LCD_num(site5,num_black[4],num_color(num_black[4]),BLACK);

    Site_t site6 = {90,93};       //x = 90 ,y = 93
    LCD_num(site6,num_black[5],num_color(num_black[5]),BLACK);   

    Site_t site7 = {10,106};       //x = 10 ,y = 106
    LCD_num(site7,num_black[6],num_color(num_black[6]),BLACK);

    Site_t site8 = {50,106};       //x = 50 ,y = 106
    LCD_num(site8,num_black[7],num_color(num_black[7]),BLACK);

    Site_t site9 = {90,106};       //x = 90 ,y = 106
    LCD_num(site9,num_black[8],num_color(num_black[8]),BLACK);   
}
/*******************************************************************************
* Function Name: number_display1();
* Description  : 
* Author Data  : 2018/5/7 by Lcy
*******************************************************************************/
void number_display1()
{   
    Site_t site1 = {4,72};        //x = 10 ,y = 80         
    LCD_num(site1,num_black[0],num_color(num_black[0]),BLACK);

    Site_t site2 = {36,72};        //x = 50 ,y = 80
    LCD_num(site2,num_black[1],num_color(num_black[1]),BLACK);

    Site_t site3 = {68,72};        //x = 90 ,y = 80
    LCD_num(site3,num_black[2],num_color(num_black[2]),BLACK); 
    
    Site_t site10 = {100,72};        //x = 90 ,y = 80
    LCD_num(site10,num_black[3],num_color(num_black[3]),BLACK); 

    Site_t site4 = {4,85};       //x = 10 ,y = 93
    LCD_num(site4,num_black[4],num_color(num_black[4]),BLACK);

    Site_t site5 = {36,85};       //x = 50 ,y = 93
    LCD_num(site5,num_black[5],num_color(num_black[5]),BLACK);

    Site_t site6 = {68,85};       //x = 90 ,y = 93
    LCD_num(site6,num_black[6],num_color(num_black[6]),BLACK); 
    
    Site_t site11 = {100,85};        //x = 90 ,y = 80
    LCD_num(site11,num_black[7],num_color(num_black[7]),BLACK);    

    Site_t site7 = {4,98};       //x = 10 ,y = 106
    LCD_num(site7,num_black[8],num_color(num_black[8]),BLACK);

    Site_t site8 = {36,98};       //x = 50 ,y = 106
    LCD_num(site8,num_black[9],num_color(num_black[9]),BLACK);

    Site_t site9 = {68,98};       //x = 90 ,y = 106
    LCD_num(site9,num_black[10],num_color(num_black[10]),BLACK);   
    
    Site_t site12 = {100,98};        //x = 90 ,y = 80
    LCD_num(site12,num_black[11],num_color(num_black[11]),BLACK);
    
    Site_t site71 = {4,111};       //x = 10 ,y = 106
    LCD_num(site71,num_black[12],num_color(num_black[12]),BLACK);

    Site_t site81 = {36,111};       //x = 50 ,y = 106
    LCD_num(site81,num_black[13],num_color(num_black[13]),BLACK);

    Site_t site91 = {68,111};       //x = 90 ,y = 106
    LCD_num(site91,num_black[14],num_color(num_black[14]),BLACK);   
    
    Site_t site121 = {100,111};        //x = 90 ,y = 80
    LCD_num(site121,num_black[15],num_color(num_black[15]),BLACK);
  
}
/*******************************************************************************
* Function Name: width_display();
* Description  : 
* Author Data  : 2018/1/17
*******************************************************************************/
void width_display()
{
    Site_t site1 = {10,80};        //x = 10 ,y = 80         
    LCD_num(site1,width_y-1,WHITE,BLACK);
    Site_t site2 = {35,80};        //x = 35 ,y = 80
    LCD_num(site2,leftline_x[width_y-1],BLUE,BLACK);
    Site_t site3 = {60,80};        //x = 60 ,y = 80
    LCD_num(site3,rightline_x[width_y-1],BLUE,BLACK);
    Site_t site4 = {96,80};        //x = 10 ,y = 80         
    LCD_num(site4,width_x[width_y-1],BLUE,BLACK);
    
    Site_t site5 = {10,93};       //x = 10 ,y = 93
    LCD_num(site5,width_y,WHITE,BLACK);
    Site_t site6 = {35,93};       //x = 35 ,y = 93
    LCD_num(site6,leftline_x[width_y],BLUE,BLACK);
    Site_t site7 = {60,93};       //x = 35 ,y = 93
    LCD_num(site7,rightline_x[width_y],BLUE,BLACK);
    Site_t site8 = {95,93};        //x = 10 ,y = 80         
    LCD_num(site8,width_x[width_y],BLUE,BLACK);

   
    Site_t site9 = {10,106};       //x = 10 ,y = 106
    LCD_num(site9,width_y+1,WHITE,BLACK);
    Site_t site10 = {35,106};       //x = 50 ,y = 106
    LCD_num(site10,leftline_x[width_y+1],BLUE,BLACK);
    Site_t site11 = {60,106};       //x = 50 ,y = 106
    LCD_num(site11,rightline_x[width_y+1],BLUE,BLACK);
    Site_t site12 = {95,106};        //x = 10 ,y = 80         
    LCD_num(site12,width_x[width_y+1],BLUE,BLACK);

}
/*******************************************************************************
* Function Name: left_right_display();
* Description  : 
* Author Data  : 2018/4/23
*******************************************************************************/
void left_right_display()
{
    Site_t site1 = {10,80};        //x = 10 ,y = 80         
    LCD_num(site1,left1,WHITE,BLACK);
    Site_t site2 = {80,80};        //x = 50 ,y = 80
    LCD_num(site2,right1,BLUE,BLACK);


    Site_t site3 = {10,93};       //x = 10 ,y = 93
    LCD_num(site3,left2,WHITE,BLACK);
    Site_t site4 = {80,93};       //x = 50 ,y = 93
    LCD_num(site4,right2,BLUE,BLACK);

   
    Site_t site5 = {10,106};       //x = 10 ,y = 106
    LCD_num(site5,left3,WHITE,BLACK);
    Site_t site6 = {80,106};       //x = 50 ,y = 106
    LCD_num(site6,right3,BLUE,BLACK);

}
/*******************************************************************************
* Function Name: left_right_display2();
* Description  : 
* Author Data  : 2018/6/10
*******************************************************************************/
void left_right_display2()
{
    Site_t site1 = {0,80};        //x = 10 ,y = 80         
    LCD_num(site1,left_1,WHITE,BLACK);
    Site_t site2 = {64,80};        //x = 50 ,y = 80
    LCD_num(site2,right_1,BLUE,BLACK);

    Site_t site3 = {0,93};       //x = 10 ,y = 93
    LCD_num(site3,left_2,WHITE,BLACK);
    Site_t site4 = {64,93};       //x = 50 ,y = 93
    LCD_num(site4,right_2,BLUE,BLACK);
  
    Site_t site5 = {0,106};       //x = 10 ,y = 106
    LCD_num(site5,left_3,WHITE,BLACK);
    Site_t site6 = {64,106};       //x = 50 ,y = 106
    LCD_num(site6,right_3,BLUE,BLACK);
    
    Site_t site7 = {32,80};        //x = 10 ,y = 80         
    LCD_num(site7,left_4,WHITE,BLACK);
    Site_t site8 = {96,80};        //x = 50 ,y = 80
    LCD_num(site8,right_4,BLUE,BLACK);

    Site_t site9 = {32,93};       //x = 10 ,y = 93
    LCD_num(site9,left_5,WHITE,BLACK);
    Site_t site10 = {96,93};       //x = 50 ,y = 93
    LCD_num(site10,right_5,BLUE,BLACK);
  
    Site_t site11 = {32,106};       //x = 10 ,y = 106
    LCD_num(site11,left_6,WHITE,BLACK);
    Site_t site12 = {96,106};       //x = 50 ,y = 106
    LCD_num(site12,right_6,BLUE,BLACK);

}
/*******************************************************************************
* Function Name: int num_color(uint32 number);
* Description  : 
* Author Data  : 2018/1/17
*******************************************************************************/
int num_color(uint32 number)
{
    if(number>400 )
    {
        return RED;
    }
    else
    {
        return WHITE;
    }
}
/*******************************************************************************
* Function Name: void numbre_renew();
* Description  : 计算黑点
* Author Data  : 2018/1/17
*******************************************************************************/
void numbre_renew()
{
    num_black[0]=count_spot(0,4,22,43);
    num_black[1]=count_spot(0,44,22,85);
    num_black[2]=count_spot(0,86,22,125);
    num_black[3]=count_spot(23,4,47,43);
    num_black[4]=count_spot(23,44,47,85);
    num_black[5]=count_spot(23,86,47,125);
    num_black[6]=count_spot(48,4,70,43);
    num_black[7]=count_spot(48,44,70,85);  //最后一行，第70行既数组69中坏了一点，一直为黑
    num_black[8]=count_spot(48,86,70,125);
}
/*******************************************************************************
* Function Name: void numbre_renew1();
* Description  : 计算黑点
* Author Data  : 2018/5/17
*******************************************************************************/
void numbre_renew1()
{
    num_black[0]=count_spot (  0,  4, 17, 34 );
    num_black[1]=count_spot (  0, 34, 17, 65 );
    num_black[2]=count_spot (  0, 65, 17, 96 );
    num_black[3]=count_spot (  0, 96, 17, 125);
    num_black[4]=count_spot ( 17,  4, 35, 34 );
    num_black[5]=count_spot ( 17, 34, 35, 65 );
    num_black[6]=count_spot ( 17, 65, 35, 96 );
    num_black[7]=count_spot ( 17, 96, 35, 125);  
    num_black[8]=count_spot ( 35,  4, 53, 34 );
    num_black[9]=count_spot ( 35, 34, 53, 65 );
    num_black[10]=count_spot( 35, 65, 53, 96 );
    num_black[11]=count_spot( 35, 96, 53, 125);
    num_black[12]=count_spot( 53,  4, 70, 34 );
    num_black[13]=count_spot( 53, 34, 70, 65 );
    num_black[14]=count_spot( 53, 65, 70, 96 );
    num_black[15]=count_spot( 53, 96, 70, 125);
    
}
/*******************************************************************************
* Function Name: void led_led();
* Description  : 灯
* Author Data  : 2018/6/10
*******************************************************************************/
void led_led()
{
 if(huiche_flag==3)
  {
    led (LED0,LED_ON);
    led (LED1,LED_ON);
    led (LED2,LED_ON);
    led (LED3,LED_OFF);  
  }
  else if(huiche_flag==2)
  {
    led (LED0,LED_ON);
    led (LED1,LED_ON);
    led (LED2,LED_OFF);
    led (LED3,LED_OFF); 
  }
  else if(huiche_flag==1)
  {
    led (LED0,LED_ON);
    led (LED1,LED_OFF);
    led (LED2,LED_OFF);
    led (LED3,LED_OFF);
  }
  else if(huiche_flag==0)
  {
    led (LED0,LED_OFF);
    led (LED1,LED_OFF);
    led (LED2,LED_OFF);
    led (LED3,LED_OFF);
  }
}
/*******************************************************************************
* Function Name: void beep();
* Description  : 蜂鸣器
* Author Data  : 2018/6/18
*******************************************************************************/
void beep()
{
   if(roundo_left_flag==1||roundo_right_flag==1||roundo_leftout_flag==1||roundo_rightout_flag==1)
     gpio_set (PTE11,0);  
   
   else if(ramp_flag==3||ramp_flag==2)
     gpio_set (PTE11,0);
   
   else if(huiche_flag==3||huiche_flag==2&&leftval!=0&&rightval!=0)
     gpio_set (PTE11,0);
   
   else
     gpio_set (PTE11,1);

}