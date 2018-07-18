#include "common.h"
#include "include.h"
int8 camera_boundary=26;
//压缩二值化图像解压（空间 换 时间 解压）
//srclen 是二值化图像的占用空间大小
//【鹰眼解压】鹰眼图像解压，转为 二维数组 - 智能车资料区 - 山外论坛 http://vcan123.com/forum.php?mod=viewthread&tid=17&ctid=6
//解压的时候，里面有个数组，配置黑、白对应的值是多少。

void img_unzip_1(uint8 *dst, uint8 *src)
{

    uint8 line_distance[120]=
    {  
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,        
        
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    uint8 color[2] = {255, 0}; //0 和 1 分别对应的颜色
    //注：野火的摄像头 0 表示 白色，1表示 黑色
    uint8 line=0;
    uint8 tmpsrc;
    uint8 all_img[160];
    uint8 *p_all;
    int i,j;

    for(i=0;i<120;i++)
    {
        if(line_distance[i]==1)             //前80个是1后二十个是0
        {
            p_all=all_img;
            for(j=0;j<20;j++)          //解压一行
            {
                tmpsrc = *src++;                         //代表解压前一个字节里面包含的东西
                *p_all++ = color[ (tmpsrc >> 7 ) & 0x01 ];
                *p_all++ = color[ (tmpsrc >> 6 ) & 0x01 ];
                *p_all++ = color[ (tmpsrc >> 5 ) & 0x01 ];
                *p_all++ = color[ (tmpsrc >> 4 ) & 0x01 ];
                *p_all++ = color[ (tmpsrc >> 3 ) & 0x01 ];
                *p_all++ = color[ (tmpsrc >> 2 ) & 0x01 ];
                *p_all++ = color[ (tmpsrc >> 1 ) & 0x01 ];
                *p_all++ = color[ (tmpsrc >> 0 ) & 0x01 ];
            }
            if(camera_boundary>=0&&camera_boundary<=32)
            {
              for(j=camera_boundary;j<camera_boundary+128;j++)
              {
                  *dst++ = all_img[j];
              }
            }
            else if(camera_boundary<0)
            {
              line=abs(camera_boundary);
              for(j=0;j<line;j++)
              {
                  *dst++ = all_img[0];
              }
              for(j=0;j<128-line;j++)
              {
                  *dst++ = all_img[j];
              }             
            }
            else
            {
              line=camera_boundary-32;
              for(j=camera_boundary;j<160;j++)
              {
                  *dst++ = all_img[j];
              }
              for(j=0;j<line;j++)
              {
                  *dst++ = all_img[127];
              } 
            
            } 
            
        }
        else
        {
            src+=20;
        }
    }
}

void img_unzip_2(uint8 *dst, uint8 *src)
{
  
    int8 camera_b=camera_boundary-26;
  
    uint8 line_distance[120]=
    {  
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,        
        
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    uint8 color[2] = {255, 0}; //0 和 1 分别对应的颜色
    //注：野火的摄像头 0 表示 白色，1表示 黑色
    uint8 line=0;
    uint8 tmpsrc;
    uint8 all_img[160];
    uint8 *p_all;
    int i,j;

    for(i=0;i<120;i++)
    {
        if(line_distance[i]==1)             //前80个是1后二十个是0
        {
            p_all=all_img;
            for(j=0;j<20;j++)          //解压一行
            {
                tmpsrc = *src++;                         //代表解压前一个字节里面包含的东西
                *p_all++ = color[ (tmpsrc >> 7 ) & 0x01 ];
                *p_all++ = color[ (tmpsrc >> 6 ) & 0x01 ];
                *p_all++ = color[ (tmpsrc >> 5 ) & 0x01 ];
                *p_all++ = color[ (tmpsrc >> 4 ) & 0x01 ];
                *p_all++ = color[ (tmpsrc >> 3 ) & 0x01 ];
                *p_all++ = color[ (tmpsrc >> 2 ) & 0x01 ];
                *p_all++ = color[ (tmpsrc >> 1 ) & 0x01 ];
                *p_all++ = color[ (tmpsrc >> 0 ) & 0x01 ];
            }
            if(camera_b>=0&&camera_b<=32)
            {
              for(j=camera_b;j<camera_b+128;j++)
              {
                  *dst++ = all_img[j];
              }
            }
            else if(camera_b<0)
            {
              line=abs(camera_b);
              for(j=0;j<line;j++)
              {
                  *dst++ = 0;
              }
              for(j=0;j<128-line;j++)
              {
                  *dst++ = all_img[j];
              }             
            }
            else
            {
              line=camera_b-32;
              for(j=camera_b;j<160;j++)
              {
                  *dst++ = all_img[j];
              }
              for(j=0;j<line;j++)
              {
                  *dst++ = all_img[127];
              } 
            
            } 
            
        }
        else
        {
            src+=20;
        }
    }
}


void img_unzip_3(uint8 *dst, uint8 *src)
{
  
    int8 camera_b=0;
    if(servo_angle>30)
      camera_b=camera_boundary-15;
    else if(servo_angle<-30)
      camera_b=camera_boundary+15;
    else
      camera_b=camera_boundary;
  
    uint8 line_distance[120]=
    {  
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,        
        
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    uint8 color[2] = {255, 0}; //0 和 1 分别对应的颜色
    //注：野火的摄像头 0 表示 白色，1表示 黑色
    uint8 line=0;
    uint8 tmpsrc;
    uint8 all_img[160];
    uint8 *p_all;
    int i,j;

    for(i=0;i<120;i++)
    {
        if(line_distance[i]==1)             //前80个是1后二十个是0
        {
            p_all=all_img;
            for(j=0;j<20;j++)          //解压一行
            {
                tmpsrc = *src++;                         //代表解压前一个字节里面包含的东西
                *p_all++ = color[ (tmpsrc >> 7 ) & 0x01 ];
                *p_all++ = color[ (tmpsrc >> 6 ) & 0x01 ];
                *p_all++ = color[ (tmpsrc >> 5 ) & 0x01 ];
                *p_all++ = color[ (tmpsrc >> 4 ) & 0x01 ];
                *p_all++ = color[ (tmpsrc >> 3 ) & 0x01 ];
                *p_all++ = color[ (tmpsrc >> 2 ) & 0x01 ];
                *p_all++ = color[ (tmpsrc >> 1 ) & 0x01 ];
                *p_all++ = color[ (tmpsrc >> 0 ) & 0x01 ];
            }
            if(camera_b>=0&&camera_b<=32)
            {
              for(j=camera_b;j<camera_b+128;j++)
              {
                  *dst++ = all_img[j];
              }
            }
            else if(camera_b<0)
            {
              line=abs(camera_b);
              for(j=0;j<line;j++)
              {
                  *dst++ = 0;
              }
              for(j=0;j<128-line;j++)
              {
                  *dst++ = all_img[j];
              }             
            }
            else
            {
              line=camera_b-32;
              for(j=camera_b;j<160;j++)
              {
                  *dst++ = all_img[j];
              }
              for(j=0;j<line;j++)
              {
                  *dst++ = all_img[127];
              } 
            
            } 
            
        }
        else
        {
            src+=20;
        }
    }
}