#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
#include "stdlib.h"	    


#define OLED_MODE 	0
		    						  
//-----------------OLED端口定义----------------  					   

#define OLED_RST  	PCout(3)
#define OLED_RS 	PBout(9)

#define OLED_SCLK 	PCout(1)
#define OLED_SDIN 	PCout(14)
		     
#define OLED_CMD  	0		//写命令
#define OLED_DATA 	1		//写数据
 
#define  OLED_SCL_PIN					GPIO_Pin_1
#define	 OLED_SDA_PIN					GPIO_Pin_14
/*另一种方式*/
#define  OLED_DC      PBout(9)
#define     XLevelL		    0x00
#define     XLevelH		    0x10
#define     XLevel		    ((XLevelH&0x0F)*16+XLevelL)
#define     Max_Column	    128
#define     Max_Row		    64
#define	    Brightness	    0xCF
#define     X_WIDTH         128
#define     Y_WIDTH         64
#define		Page			8

void OLED_WB(uint8_t data);
/*********************LCD写数据************************************/ 
void OLED_WrDat(uint8_t data);
/*********************LCD写命令************************************/
void OLED_WrCmd(uint8_t cmd);
/*********************设定坐标************************************/
void OLED_Set_Pos(uint8_t x, uint8_t y);
/*********************LCD全屏操作************************************/
void OLED_Fill(unsigned char bmp_dat);
/*********************LCD复位************************************/
void OLED_CLS(void);
/*********************LCD初始化************************************/
void OLED_Init(void);
/*********************延时函数***********************/
void LCD_DLY_ms(unsigned int ms);
/***************功能描述：显示6*8一组标准ASCII字符串	显示的坐标（x,y），y为页范围0～7****************/
void LCD_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[]);
/*******************功能描述：显示8*16一组标准ASCII字符串	 显示的坐标（x,y），y为页范围0～7****************/
void LCD_P8x16Str(unsigned char x,unsigned char y,unsigned char ch[]);
/*****************功能描述：显示16*16点阵  显示的坐标（x,y），y为页范围0～7****************************/
void LCD_P16x16Ch(unsigned char x,unsigned char y,unsigned char N);
/*****************功能描述：显示32*32点阵  显示的坐标（x,y），y为页范围0～7****************************/
void LCD_P32x32Ch(unsigned char x,unsigned char y,unsigned char N);

void LCD_DrawPoint(unsigned char x,unsigned char y,unsigned char t);
//更新显存到LCD		 
void OLED_Refresh_Gram(void);
void LCD_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void LCD_Show8x16Char(unsigned char x,unsigned char y,unsigned char ch);
void LCD_Show6x8Char(unsigned char x,unsigned char y,unsigned char ch);
void OLED_write_char(unsigned char c);
void OLED_write_3_num(unsigned char X,unsigned char Y,signed int s);
void OLED_write_5_num(unsigned char X,unsigned char Y,int s);
void OLED_write_8_num(unsigned char X,unsigned char Y,int s);
void OLED_write_4_num(unsigned char X,unsigned char Y,int s);
void OLED_write_2_num(unsigned char X,unsigned char Y,signed int s);
void OLED_write_1_num(unsigned char X,unsigned char Y,signed int s);
void Draw_LibLogo(void);
void OLED_P13x16Str(u8 x,u8 y,u8 ch[]);
void OLED_P16x16Str(u8 x,u8 y,u8 ch[]);
void OLED_P12x12Str(u8 x,u8 y,u8 ch[]);
#define OLED_SDA   PCout(14)
#define OLED_SCL   PCout(1)

#endif  
	 
