/*
 * @file       z_test.c   
 * @author     DLSZ
 * @date       2018-05-15
 */

#include "include.h"
#include "common.h"

/////////////////////////////////  ������   ////////////////////////////////////
#define SECTOR_NUM  (FLASH_SECTOR_NUM-1)         //FLASH������������������ȷ����ȫ

/////////////////////////////////  ������   ////////////////////////////////////




void write_flash()    //д������
{
   flash_erase_sector(SECTOR_NUM);  //��������
   flash_write(SECTOR_NUM, 0, (uint32)OV7725_yuzhi );
   flash_erase_sector(SECTOR_NUM-1);  //��������
   flash_write(SECTOR_NUM-1, 0, (uint32)dis_hcjj1 );
   flash_erase_sector(SECTOR_NUM-2);  //��������
   flash_write(SECTOR_NUM-2, 0, (uint32)dis_hcjj2 );
   flash_erase_sector(SECTOR_NUM-3);  //��������
   flash_write(SECTOR_NUM-3, 0, (uint32)gongshi1 );
   flash_erase_sector(SECTOR_NUM-4);  //��������
   flash_write(SECTOR_NUM-4, 0, (uint32)gongshi2 );
   /*
   flash_erase_sector(SECTOR_NUM-5);  //��������
   flash_write(SECTOR_NUM-5, 0, (uint32)sj3 );
   flash_erase_sector(SECTOR_NUM-6);  //��������
   flash_write(SECTOR_NUM-6, 0, (uint32)sj4);
   flash_erase_sector(SECTOR_NUM-7);  //��������
   flash_write(SECTOR_NUM-7, 0, (uint32)sj5 );
   flash_erase_sector(SECTOR_NUM-8);  //��������
   flash_write(SECTOR_NUM-8, 0, (uint32)sj6 );
   flash_erase_sector(SECTOR_NUM-9);  //��������
   flash_write(SECTOR_NUM-9, 0, (uint32)sj7 );
   */
}

void read_flash()  //��ȡ����
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


