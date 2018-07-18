/*
 * @file       z_test.c   
 * @author     DLSZ
 * @date       2018-05-15
 */

#include "include.h"
#include "common.h"

/////////////////////////////////  变量表   ////////////////////////////////////
#define SECTOR_NUM  (FLASH_SECTOR_NUM-1)         //FLASH尽量用最后面的扇区，确保安全

/////////////////////////////////  函数表   ////////////////////////////////////




void write_flash()    //写入数据
{
   flash_erase_sector(SECTOR_NUM);  //擦除扇区
   flash_write(SECTOR_NUM, 0, (uint32)OV7725_yuzhi );
   flash_erase_sector(SECTOR_NUM-1);  //擦除扇区
   flash_write(SECTOR_NUM-1, 0, (uint32)dis_hcjj1 );
   flash_erase_sector(SECTOR_NUM-2);  //擦除扇区
   flash_write(SECTOR_NUM-2, 0, (uint32)dis_hcjj2 );
   flash_erase_sector(SECTOR_NUM-3);  //擦除扇区
   flash_write(SECTOR_NUM-3, 0, (uint32)gongshi1 );
   flash_erase_sector(SECTOR_NUM-4);  //擦除扇区
   flash_write(SECTOR_NUM-4, 0, (uint32)gongshi2 );
   /*
   flash_erase_sector(SECTOR_NUM-5);  //擦除扇区
   flash_write(SECTOR_NUM-5, 0, (uint32)sj3 );
   flash_erase_sector(SECTOR_NUM-6);  //擦除扇区
   flash_write(SECTOR_NUM-6, 0, (uint32)sj4);
   flash_erase_sector(SECTOR_NUM-7);  //擦除扇区
   flash_write(SECTOR_NUM-7, 0, (uint32)sj5 );
   flash_erase_sector(SECTOR_NUM-8);  //擦除扇区
   flash_write(SECTOR_NUM-8, 0, (uint32)sj6 );
   flash_erase_sector(SECTOR_NUM-9);  //擦除扇区
   flash_write(SECTOR_NUM-9, 0, (uint32)sj7 );
   */
}

void read_flash()  //读取数据
{
  OV7725_yuzhi=(int) (flash_read(SECTOR_NUM, 0, uint32 ));
  SCCB_WriteByte( OV7725_CNST ,OV7725_yuzhi );
  dis_hcjj1=(int) (flash_read(SECTOR_NUM-1, 0, uint32 ));
  dis_hcjj2=(int) (flash_read(SECTOR_NUM-2, 0, uint32 ));
  gongshi1=(int) (flash_read(SECTOR_NUM-3, 0, uint32 ));
  gongshi2=(int) (flash_read(SECTOR_NUM-4, 0, uint32 ));
  /*
  sj3=(int) (flash_read(SECTOR_NUM-5, 0, uint32 ));
  sj4=(int) (flash_read(SECTOR_NUM-6, 0, uint32 ));
  sj5=(int) (flash_read(SECTOR_NUM-7, 0, uint32 ));
  sj6=(int) (flash_read(SECTOR_NUM-8, 0, uint32 ));
  sj7=(int) (flash_read(SECTOR_NUM-9, 0, uint32 ));
  */

}


