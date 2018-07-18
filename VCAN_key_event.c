/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       VCAN_key_event.h
 * @brief      KEY 事件函数实现
 * @author     山外科技
 * @version    v5.0
 * @date       2014-01-04
 */

#include "VCAN_key_event.h"
#include "VCAN_UI_VAR.h"
#include  "include.h"                
//#include "NRF24L0.h"
//#include "NRF24L0_MSG.h"

int8 flag_key_select=0;
int8 flag_key_l_u_0=0;
int8 flag_key_l_u_1=0;
int8 flag_key_l_u_2=0;
int8 flag_key_l_u_3=0;
int8 flag_key_l_u_4=0;
int8 flag_key_l_u_5=0;
int8 flag_key_l_u_6=0;
uint8 test_time=0;


void key_event_init()
{
    //初始化 全部 按键
    key_init(KEY_MAX);

    //初始化临时变量
  //  var_init();
#if nrf_debug
    //同步全部数据并显示
    var_syn(VAR_MAX);       //同步全部 ,必须先同步再显示全部，因为有可能同步失败。
    var_display(VAR_MAX);   //显示全部
#endif
}

void deal_key_event_vcan()
{
    KEY_MSG_t keymsg;

    while(get_key_msg(& keymsg))     //获得按键就进行处理
    {
        if(keymsg.status == KEY_DOWN)
        {
            switch(keymsg.key)
            {
            case KEY_U:
                var_value(VAR_ADD);
                break;

            case KEY_D:
                var_value(VAR_SUB);
                break;

            case KEY_L:
                var_select(VAR_PREV);
                break;

            case KEY_R:
                var_select(VAR_NEXT);
                break;

            case KEY_B:
                var_ok();
                break;

            case KEY_A:
                val_cancel();
                break;

            case KEY_START:
                save_var(CAR_CTRL,CAR_START);
                var_syn(CAR_CTRL);
                var_display(CAR_CTRL);
                break;
            case KEY_STOP:
                save_var(CAR_CTRL,CAR_STOP);
                var_syn(CAR_CTRL);
                var_display(CAR_CTRL);
                break;

            default:
                break;
            }
        }
        else if(keymsg.status == KEY_HOLD)
        {
            switch(keymsg.key)
            {
            case KEY_U:
                var_value(VAR_ADD_HOLD);
                break;

            case KEY_D:
                var_value(VAR_SUB_HOLD);
                break;

            case KEY_L:
                var_select(VAR_PREV_HOLD);
                break;

            case KEY_R:
                var_select(VAR_NEXT_HOLD);
                break;

            case KEY_B:                //长按 OK 键 同步全部数据并显示
                var_syn(VAR_MAX);       //同步全部 ,必须先同步再显示全部，因为有可能同步失败。
                var_display(VAR_MAX);   //显示全部
                break;

            case KEY_START:
                save_var(CAR_CTRL,CAR_START);
                while(var_syn(CAR_CTRL)==0);
                var_display(CAR_CTRL);
                break;

            case KEY_STOP:
                save_var(CAR_CTRL,CAR_STOP);
                while(var_syn(CAR_CTRL)==0);
                var_display(CAR_CTRL);

            default:            //不需要处理 cancel
                break;
            }
        }
        else
        {
            //KEY_UP ,不进行处理
        }
    }
}

/*******************************************************************************
* Function Name: void deal_key_event();
* Input Param  : 无
* Output Param : 无
* Description  : 按键处理
* Author Data  : 2018/2/1  by DLSZ
******************************************************************************/
void deal_key_event()
{
    KEY_MSG_t keymsg;

    while(get_key_msg(& keymsg))     //获得按键就进行处理
    {
  //      gpio_set (PTE11,0);
        color_init();
        renew_flag=0; //按下按键就允许特殊页面刷屏一次
        if(keymsg.status == KEY_DOWN)
        {
            switch(keymsg.key)
            {
            case KEY_U:     //上
                 deal_key_up();
                 break;

            case KEY_D:     //下
                 deal_key_down();
                 break;

            case KEY_L:      //左
                 key_clear_flag=1;
                 deal_key_left();
                 break;

            case KEY_R:      //右
                 key_clear_flag=1;
                 deal_key_right();
                 break;

            case KEY_B:      //选择
                 key_clear_flag=1;
                 deal_key_select();
                 break;
/*
            case KEY_A:      //独立按键
                {
                  switch(flag_key_select)
                  {
                    case 0:
                          {
                          }
                          break;
                 }

               } break;

            case KEY_START:
              //  save_var(CAR_CTRL,CAR_START);
              //  var_syn(CAR_CTRL);
              //  var_display(CAR_CTRL);
                break;
            case KEY_STOP:
             //   save_var(CAR_CTRL,CAR_STOP);
             //   var_syn(CAR_CTRL);
             //   var_display(CAR_CTRL);
                break;
*/
                default:
                break;
            }
        }
       
        else if(keymsg.status == KEY_HOLD)
        {
            switch(keymsg.key)
            {
              case KEY_U:                //长按上按键
                  break;
              case KEY_D:                //长按下按键
                  break;
              case KEY_L:
                  break;
              case KEY_R:
                  break;

              case KEY_B:                //长按 OK 键 同步全部数据并显示
                  gpio_set (PTE11,0);
                  write_flash();
                  gpio_set (PTE11,1);
                  break;
              case KEY_START:
             //  save_var(CAR_CTRL,CAR_START);
             //  while(var_syn(CAR_CTRL)==0);
             //  var_display(CAR_CTRL);
                  break;
              case KEY_STOP:
             //  save_var(CAR_CTRL,CAR_STOP);
             //  while(var_syn(CAR_CTRL)==0);
             //  var_display(CAR_CTRL);
              default:            //不需要处理 
                  break;
              }
          }

        else
        {
            //不进行处理
        }
    }
//    DELAY_MS(50);
//    gpio_set (PTE11,1);
}

 /*******************************************************************************
* Function Name: void deal_key_select()
* Input Param  : 无
* Output Param : 无
* Description  : 中间按键处理
* Author Data  : 2018/4/5  by Lcy
******************************************************************************/
void deal_key_select()
{
 switch(flag_key_select)
  {
   case 0:       //表示现在停留在首页
    {
         switch(flag_key_l_u_0)
            {
             case 1:       //显示首页
              {
                   flag_key_select=1;
                   flag_key_l_u_0=0;
              }
              break;

            case 2:        //显示图像页面
              {
                   flag_key_select=2;
                   flag_key_l_u_0=0;
              }
              break;

            case 3:        //显示舵机参数页面
              {
                   flag_key_select=3;
                   flag_key_l_u_0=0;
              }
              break;

            case 4:        //显示电机参数页面
              {
                   flag_key_select=4;
                   flag_key_l_u_0=0;
              }
              break;
            case 5:       //开车页面（不刷屏）
              {
                flag_key_select=5;
                flag_key_l_u_0=0;
                if(bumper_car_flag==1)
                {
                  for(int i = 0; i < 1; ++i)
                  {
                    uart_putchar(UART4,'A'); 
                  }
                }
                gpio_set (PTE11,0);
                DELAY_MS(1000) ;
                gpio_set (PTE11,1);
                car_start_key();   //按键发车函数
              }
              break;
            case 6:        //显示设置页面
              {
                   flag_key_select=6;
                   flag_key_l_u_0=0;
              }
              break;
            }

    }
    break;
  case 1:        //表示现在停留在赛道显示页面
    {
       switch(flag_key_l_u_1)
        {
         case 0:       //表示现在停留在赛道显示页的“上一页”
          {
               flag_key_select=0;
               flag_key_l_u_1=0;
          }
          break;
         case 3:       //表示现在停留在赛道显示页的“下一页”
          {
               flag_key_select=2;
               flag_key_l_u_1=0;
          }
          break;
          case 1:       //表示现在停留在赛道显示页的T
          {
               flag_key_select=1;
               flag_key_l_u_1=1;
          }
          break;
          case 2:       //表示现在停留在赛道显示页的Y
          {
               flag_key_select=1;
               flag_key_l_u_1=2;
          }
          break;
          case 4:       //表示现在停留在赛道显示页
          {
               flag_key_select=1;
               flag_key_l_u_1=4;
          }
          break;
        }
    }
    break;
  case 2:        //表示现在停留在舵机信息显示页面
    {
         switch(flag_key_l_u_2)
          {
           case 0:       //表示现在停留在舵机信息显示页的“上一页”
            {
                 flag_key_select=1;
                 flag_key_l_u_2=0;
            }
            break;
           case 7:       //表示现在停留在舵机信息显示页的“下一页”
            {
                 flag_key_select=3;
                 flag_key_l_u_2=0;
            }
            break;
           case 8:       //表示现在停留在舵机信息显示页的“返回首页”
            {
                 flag_key_select=0;
                 flag_key_l_u_2=0;
            }
            break;
          }
    }
    break;
  case 3:        //表示现在停留在电机信息显示页面
    {
         switch(flag_key_l_u_3)
          {
           case 0:       //表示现在停留在电机信息显示页的“上一页”
            {
                 flag_key_select=2;
                 flag_key_l_u_3=0;
            }
            break;
           case 7:       //表示现在停留在电机信息显示页的“下一页”
            {
                 flag_key_select=4;
                 flag_key_l_u_3=0;
            }
            break;
           case 8:       //表示现在停留在电机信息显示页的“返回首页”
            {
                 flag_key_select=0;
                 flag_key_l_u_3=0;
            }
            break;
          }
    }
    break;
  case 4:        //表示现在停留在其他信息显示页面
    {
         switch(flag_key_l_u_4)
          {
           case 0:       //表示现在停留在电机信息显示页的“上一页”
            {
                 flag_key_select=3;
                 flag_key_l_u_4=0;
            }
            break;
           case 7:       //表示现在停留在电机信息显示页的“下一页”
            {
                 flag_key_select=6;
                 flag_key_l_u_4=0;
            }
            break;
           case 8:       //表示现在停留在电机信息显示页的“返回首页”
            {
                 flag_key_select=0;
                 flag_key_l_u_4=0;
            }
            break;
          }
    }
    break;
  case 5:        //表示现在停留在开车显示页面
    {
      switch(flag_key_l_u_5)
      {
        case 1:       //表示现在停留在开车显示页的“停车”
            {
                 flag_key_select=0;
                 flag_key_l_u_5=0;

                 car_stop_key();
            }
            break;
        case 2:       //表示现在停留在开车显示页的“返回首页”
            {
                 flag_key_select=0;
                 flag_key_l_u_5=0;
            }
            break;
      }
    }
    break;
  case 6:        //表示现在停留在其他信息显示页面
    {
         switch(flag_key_l_u_6)
          {
           case 0:       //表示现在停留在电机信息显示页的“上一页”
            {
                 flag_key_select=4;
                 flag_key_l_u_6=0;
            }
            break;
           case 7:       //表示现在停留在电机信息显示页的“下一页”
            {
                 flag_key_select=0;
                 flag_key_l_u_6=0;
            }
            break;
           case 8:       //表示现在停留在电机信息显示页的“返回首页”
            {
                 flag_key_select=0;
                 flag_key_l_u_6=0;
            }
            break;
          }
    }
    break;
  default:
          {
              flag_key_select=0;
              flag_key_l_u_0=0;
              flag_key_l_u_1=0;
              flag_key_l_u_2=0;
              flag_key_l_u_3=0;
              flag_key_l_u_4=0;
              flag_key_l_u_5=0;
              flag_key_l_u_6=0;
          }
          break;
  }

}

 /*******************************************************************************
* Function Name: void deal_key_left()
* Input Param  : 无
* Output Param : 无
* Description  : 左按键处理
* Author Data  : 2018/4/5  by Lcy
******************************************************************************/
void deal_key_left()
{
    switch (flag_key_select)
    {
    case 0:
      {
         bumper_car_flag=0;
         flag_key_l_u_0=6;
      }
      break;
    case 1:
      {
          switch (flag_key_l_u_1)      //调整赛道信息的参数
            {
            case 0:    //上一页
              {
              }
              break;
            case 1:    //图像
              {
                if(camera_boundary==0)
                {
                  camera_boundary=0;
                }
                else
                camera_boundary-=1;
              }
              break;
             case 2:    //阈值
              {
                if(OV7725_yuzhi==40)
                {
                  OV7725_yuzhi=40;
                }
                else
                {            
                  OV7725_yuzhi-=1;
                }
                SCCB_WriteByte( OV7725_CNST ,OV7725_yuzhi );
              }
              break;
             case 3:    //下一页
              {
              }
              break;
             case 6:    //无
              {
                if(width_y==1)
                {
                  width_y=1;
                }
                else
                width_y-=1;
              }
              break;
            }
      }
    case 2:
      {
          switch (flag_key_l_u_2)      //调整舵机的参数
            {
            case 0:     //上一页
              {
              }
              break;
            case 1:
              {
                   s_kp-=0.001;
              }
              break;
            case 2:
              {
                    s_td-=0.005;
              }
              break;
            case 3:
              {
                   
              }
              break;
            case 4:
              {

              }
              break;
            case 5:
              {
                 cssz_flag-=1;
                 cssz_flag=constrain_int16(cssz_flag,0,1);
              }
              break;
            case 6:
              {
                 servo_flag-=1;
                 servo_flag=constrain_int16(servo_flag,0,1);
              }
              break;
            case 7:      //下一页
              {
              }
              break;
            case 8:      //用于返回菜单
              {
              }
              break;
            }
      }
    case 3:
      {
          switch (flag_key_l_u_3)      //调整电机的参数
            {
            case 0:       //上一页
              {
              }
              break;
            case 1:
              {
                 m_kp-=1;
              }
              break;
            case 2:
              {
                 m_td-=1;
              }
              break;
            case 3:
              {
                 
              }
              break;
            case 4:
              {
     
              }
              break;
            case 5:
              {

              }
              break;
            case 6:
              {
                 speedmax-=5;
                 speedmax=constrain_int16(speedmax,20,100);
                 speedmax2=speedmax;
              }
              break;
            case 7:     //下一页
              {
              }
              break;
            case 8:    //返回菜单
              {
              }
              break;
            }
      }
    case 4:
      {
          switch (flag_key_l_u_4)      //调整其他的参数
            {
            case 0:       //上一页
              {
              }
              break;
            case 1:
              {
                 start_spot-=1;
                 start_spot=constrain_int16(start_spot,0,50);
              }
              break;
            case 2:
              {
                 end_spot-=1;
                 end_spot=constrain_int16(end_spot,51,70);
              }
              break;
            case 3:
              {
                
              }
              break;
            case 4:
              {

              }
              break;
            case 5:
              {
                 special_roundo-=1;
                 special_roundo=constrain_int16(special_roundo,0,1);
              }
              break;
            case 6:
              {
                if(c_mode==0)
                {
                  c_mode=0;
                }
                else
                {
                  c_mode-=1;
                }
              }
              break;
            case 7:     //下一页
              {
              }
              break;
            case 8:    //返回菜单
              {
              }
              break;
            }
      }
    case 6:
      {
          switch (flag_key_l_u_6)      //调整设置的参数
            {
            case 0:       //上一页
              {
              }
              break;
            case 1:
              {
                 bumper_car_flag-=1;
              }
              break;
            case 2:
              {
                 gongshi1-=1;
              }
              break;
            case 3:
              {
                 gongshi2-=1;
              }
              break;
            case 4:
              {
                 dis_hcjj1-=100;
                 dis_hcjj1=constrain_int16(dis_hcjj1,100,5000);
              }
              break;
            case 5:
              {
                 dis_hcjj2-=100;
                 dis_hcjj2=constrain_int16(dis_hcjj2,100,5000);
              }
              break;
            case 6:
              {
                 speedmax-=1;
                 speedmax=constrain_int16(speedmax,20,100);
                 speedmax2=speedmax;
              }
              break;
            case 7:     //下一页
              {
              }
              break;
            case 8:    //返回菜单
              {
              }
              break;
            }
      }
    }
}


/*******************************************************************************
* Function Name: void deal_key_right()
* Input Param  : 无
* Output Param : 无
* Description  : 右按键处理
* Author Data  : 2018/4/5  by Lcy
******************************************************************************/
void deal_key_right()
{
    switch (flag_key_select)
    {
    case 0:
      {
         bumper_car_flag=1;
         if(bumper_car_flag==1)
         {
           for(;test_time<50;test_time++)
           {
             uart_putchar (UART4,'T'); 
           }
           test_time=0;
         }
         flag_key_l_u_0=5;
      }
      break;
    case 1:
      {
          switch (flag_key_l_u_1)      //调整赛道信息的参数
            {
            case 0:     //上一页
              {
              }
              break;           
            case 1:     //图像
              {
                camera_boundary+=1;
                if(camera_boundary>32)
                  camera_boundary=32;
              }
              break;
            case 2:     //阈值
              {
                if(OV7725_yuzhi==255)
                {
                  OV7725_yuzhi=255;
                }
                else
                {            
                  OV7725_yuzhi+=1;
                }
                SCCB_WriteByte( OV7725_CNST ,OV7725_yuzhi );    
              }
              break;
            case 3:     //下一页
              {
              }
              break;
            case 6:     //无
              {
                if(width_y==68)
                {
                  width_y=68;
                }
                else
                width_y+=1;
              }
              break;
            }
      }
    case 2:
      {
          switch (flag_key_l_u_2)      //调整舵机的参数
            {
            case 0:      //上一页
              {
              }
              break;
            case 1:
              {
                  s_kp+=0.001;
              }
              break;
            case 2:
              {
                  s_td+=0.005;
              }
              break;
            case 3:
              {
                  
              }
              break;
            case 4:
              {
       
              }
              break;
            case 5:
              {
                 cssz_flag+=1;
                 cssz_flag=constrain_int16(cssz_flag,0,1);
              }
              break;
            case 6:
              {
                 servo_flag+=1;
                 servo_flag=constrain_int16(servo_flag,0,1);
              }
              break;
            case 7:     //下一页
              {
              }
              break;
            case 8:      //返回菜单
              {
              }
              break;
            }
      }
    case 3:
      {
          switch (flag_key_l_u_3)      //调整电机的参数
            {
            case 0:       //上一页
              {
              }
              break;
            case 1:
              {
                 m_kp+=1;
              }
              break;
            case 2:
              {
                 m_td+=1;
              }
              break;
            case 3:
              {
                 
              }
              break;
            case 4:
              {

              }
              break;
            case 5:
              {

              }
              break;
            case 6:
              {
                 speedmax+=5;
                 speedmax=constrain_int16(speedmax,20,100);
                 speedmax2=speedmax;
              }
              break;
            case 7:     //下一页
              {
              }
              break;
            case 8:    //返回菜单
              {
              }
              break;
            }
      }
    case 4:
      {
          switch (flag_key_l_u_4)      //调整其他的参数
            {
            case 0:       //上一页
              {
              }
              break;
            case 1:
              {
                  start_spot+=1;
                  start_spot=constrain_int16(start_spot,0,50);
              }
              break;
            case 2:
              {
                  end_spot+=1;
                  end_spot=constrain_int16(end_spot,51,70);
              }
              break;
            case 3:
              {

              }
              break;
            case 4:
              {

              }
              break;
            case 5:
              {
                  special_roundo+=1;
                  special_roundo=constrain_int16(special_roundo,0,1);
              }
              break;
            case 6:
              {
                if(c_mode==3)
                {
                  c_mode=3;
                }
                else
                {
                  c_mode+=1;
                }
              }
              break;
            case 7:     //下一页
              {
              }
              break;
            case 8:    //返回菜单
              {
              }
              break;
            }
      }
    case 6:
      {
          switch (flag_key_l_u_6)      //调整设置的参数
            {
            case 0:       //上一页
              {
              }
              break;
            case 1:
              {
                 bumper_car_flag+=1;
                 if(bumper_car_flag==1)
                 {
                   for(;test_time<50;test_time++)
                   {
                     uart_putchar (UART4,'T'); 
                   }
                   test_time=0;
                 }
                 flag_key_select=0;
                 flag_key_l_u_0=5;
              }
              break;
            case 2:
              {
                 gongshi1+=10;
              }
              break;
            case 3:
              {   
                 gongshi2+=20;
              }
              break;
            case 4:
              {
                 dis_hcjj1+=100;
                 dis_hcjj1=constrain_int16(dis_hcjj1,100,4000);
              }
              break;
            case 5:
              {
                 dis_hcjj2+=100;
                 dis_hcjj2=constrain_int16(dis_hcjj2,100,4000);
              }
              break;
            case 6:
              {
                 speedmax+=1;
                 speedmax=constrain_int16(speedmax,20,100);
                 speedmax2=speedmax;
              }
              break;
            case 7:     //下一页
              {
              }
              break;
            case 8:    //返回菜单
              {
              }
              break;
            }
      }
    }
}


/*******************************************************************************
* Function Name: void deal_key_up()
* Input Param  : 无
* Output Param : 无
* Description  : 上按键处理
* Author Data  : 2018/4/5  by Lcy
******************************************************************************/
void deal_key_up()
{
  switch (flag_key_select)
  {
    case 0:
      {
        if(flag_key_l_u_0==0)
          flag_key_l_u_0=6;
        else
          flag_key_l_u_0 --;
      }
      break;
    case 1:
      {
        if(flag_key_l_u_1==0)
          flag_key_l_u_1=8;
        else
          flag_key_l_u_1 --;
        if(flag_key_l_u_1==4)
        {
          LCD_clear_xy(BLACK,0 ,75  );     //清屏
          number_display_flag=1;  
        }
        else if(flag_key_l_u_1==5)
        {
          LCD_clear_xy(BLACK,0 ,75  );     //清屏
          number_display_flag=2;  
        }
        else if(flag_key_l_u_1==6)
        {
          LCD_clear_xy(BLACK,0 ,75  );     //清屏
          number_display_flag=3;  
        }
        else if(flag_key_l_u_1==7)
        {
          LCD_clear_xy(BLACK,0 ,75  );     //清屏
          number_display_flag=4;  
        }
        else if(flag_key_l_u_1==8)
        {
          LCD_clear_xy(BLACK,0 ,75  );     //清屏
          number_display_flag=5;  
        }
        else
        {
          LCD_clear_xy(BLACK,0 ,75  );     //清屏
          number_display_flag=0;  
        }
      }
      break;
    case 2:
      {
        if(flag_key_l_u_2==0)
          flag_key_l_u_2=8;
        else
          flag_key_l_u_2 --;
      }
      break;
    case 3:
      {
        if(flag_key_l_u_3==0)
          flag_key_l_u_3=8;
        else
          flag_key_l_u_3 --;
      }
      break;
    case 4:
      {
        if(flag_key_l_u_4==0)
          flag_key_l_u_4=8;
        else
          flag_key_l_u_4 --;
      }
      break;
    case 5:
      {
        if(flag_key_l_u_5==0)
          flag_key_l_u_5=2;
        else
          flag_key_l_u_5 --;
      }
      break;
    case 6:
      {
        if(flag_key_l_u_6==0)
          flag_key_l_u_6=8;
        else
          flag_key_l_u_6 --;
      }
      break;
  }
}

/*******************************************************************************
* Function Name: void deal_key_down()
* Input Param  : 无
* Output Param : 无
* Description  : 下按键处理
* Author Data  : 2018/4/5  by Lcy
******************************************************************************/
void deal_key_down()
{
    switch (flag_key_select)
    {
    case 0:
      {
        flag_key_l_u_0 ++;
        if(flag_key_l_u_0>6)
          flag_key_l_u_0=0;
      }
      break;
    case 1:
      {
        flag_key_l_u_1 ++;
        if(flag_key_l_u_1>8)
          flag_key_l_u_1=0;
        if(flag_key_l_u_1==4)
        {
          LCD_clear_xy(BLACK,0 ,75  );     //清屏
          number_display_flag=1;  
        }
        else if(flag_key_l_u_1==5)
        {
          LCD_clear_xy(BLACK,0 ,75  );     //清屏
          number_display_flag=2;  
        }
        else if(flag_key_l_u_1==6)
        {
          LCD_clear_xy(BLACK,0 ,75  );     //清屏
          number_display_flag=3;  
        }
        else if(flag_key_l_u_1==7)
        {
          LCD_clear_xy(BLACK,0 ,75  );     //清屏
          number_display_flag=4;  
        }
        else if(flag_key_l_u_1==8)
        {
          LCD_clear_xy(BLACK,0 ,75  );     //清屏
          number_display_flag=5;  
        }
        else
        {
          LCD_clear_xy(BLACK,0 ,75  );     //清屏
          number_display_flag=0;  
        }
      }
      break;
    case 2:
      {
        flag_key_l_u_2 ++;
        if(flag_key_l_u_2>8)
          flag_key_l_u_2=0;
      }
      break;
    case 3:
      {
        flag_key_l_u_3 ++;
        if(flag_key_l_u_3>8)
          flag_key_l_u_3=0;
      }
      break;
    case 4:
      {
        flag_key_l_u_4 ++;
        if(flag_key_l_u_4>8)
          flag_key_l_u_4=0;
      }
      break;
    case 5:
      {
        flag_key_l_u_5 ++;
        if(flag_key_l_u_5>2)
          flag_key_l_u_5=0;
      }
      break;

    case 6:
      {
        flag_key_l_u_6 ++;
        if(flag_key_l_u_6>8)
          flag_key_l_u_6=0;
      }
      break;
    }
}