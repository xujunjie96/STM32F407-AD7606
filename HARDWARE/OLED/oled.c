#include "oled.h"
#include "oledfont.h"
#include "delay.h"

//[7]0 1 2 3 ... 127 			   
u8 OLED_GRAM[128][8];	 

//�����Դ浽LCD		 
void OLED_Refresh_Gram(void)
{
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WrCmd (0xb0+i);    //����ҳ��ַ��0~7��
		OLED_WrCmd (0x00);      //������ʾλ�á��е͵�ַ
		OLED_WrCmd (0x10);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_WrDat(OLED_GRAM[n][i]); 
	}   
}
void OLED_WB(uint8_t data)
{
    /* Loop while DR register in not emplty */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    /* Send byte through the SPI1 peripheral */
    SPI_I2S_SendData(SPI1, data);
		delay_us(2);
}
/*******************һ���ֽ�����д��***********************/
/*��һ�ַ�ʽ*/
/*******************һ���ֽ�����д��***********************/
void OLED_WrDat(uint8_t data)
{
    unsigned char i;
  OLED_DC=1;  
  for(i=0;i<8;i++) //???????? 
  {
    if((data << i) & 0x80)
       {
          OLED_SDA=1;
       }
    else  
          OLED_SDA=0;
    
    OLED_SCL=0;
    OLED_SCL=1;
  }
}

/********************һ��ָ��д��**********************/
void OLED_WrCmd(uint8_t cmd)
{
   unsigned char i;
  OLED_DC=0;
  for(i=0;i<8;i++) //???????? 
  {
    if((cmd << i) & 0x80)
       {
          OLED_SDA=1;
       }
    else  
          OLED_SDA=0;
    
    OLED_SCL=0;
    OLED_SCL=1;
  }
}

/**********************������ʾλ��**********************/
void OLED_Set_Pos(uint8_t x, uint8_t y)
{
OLED_WrCmd(0xb0+y);
  OLED_WrCmd(((x&0xf0)>>4)|0x10);
  OLED_WrCmd((x&0x0f)|0x01); 
}

/**********************д��������**********************/
void OLED_Fill(unsigned char bmp_dat)
{
	  unsigned char y,x;
    OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WrCmd(0x00);//
    OLED_WrCmd(0x21);//-Set Column Address
	  OLED_WrCmd(0x00);
	  OLED_WrCmd(0x7f);
	  OLED_WrCmd(0x22);//-Set Page Address
	  OLED_WrCmd(0x00);
	  OLED_WrCmd(0x07);
	  LCD_DLY_ms(1);/* �ȴ��ڲ��ȶ�   */
    for(y=0;y<Page;y++)
    {
    	for(x=0;x<X_WIDTH;x++)
    	{
    		OLED_WrDat(bmp_dat);
    	}
    }
//    LCD_WrCmd(0xaf);//--turn off oled panel
}

/*********************��������***********************/
void OLED_CLS(void)
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(0);
		LCD_DLY_ms(200);
	}
}

/*********************��ʱ����***********************/
void LCD_DLY_ms(unsigned int ms)
{
    unsigned int a;
    while(ms)
    {
        a=1335;
        while(a--);
        ms--;
    }
    return;
}

/*********************12864��ʼ��***********************/
void OLED_Init(void)
{

  GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��PORTABCʱ��
 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_14|GPIO_Pin_1;	
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��		

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��		
	
	OLED_SDIN=1;
	OLED_SCLK=1;
//#endif
	
	OLED_RS=1;
	
	  OLED_RST=0;
	  LCD_DLY_ms(50);
	  OLED_RST=1;
	//���ϵ絽���濪ʼ��ʼ��Ҫ���㹻��ʱ�䣬���ȴ�RC��λ���

        OLED_WrCmd( 0xAE);//--turn off oled panel
    OLED_WrCmd(0xD5);//---set low column address
    OLED_WrCmd(80);//---set high column address
    OLED_WrCmd(0xA8 );//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WrCmd(0X3F);//--set contrast control register
    OLED_WrCmd(0xD3 ); // Set SEG Output Current Brightness
    OLED_WrCmd(0X00);//--Set SEG/Column Mapping     0xa0???? 0xa1??
    OLED_WrCmd(0x40);//Set COM/Row Scan Direction   0xc0???? 0xc8??
    OLED_WrCmd(0x8D);//--set normal display
    OLED_WrCmd(0x14);//--set multiplex ratio(1 to 64)
    OLED_WrCmd(0x20);//--1/64 duty
    OLED_WrCmd(0x02 );//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WrCmd(0xA1);//-not offset
    OLED_WrCmd(0xC8);//--set display clock divide ratio/oscillator frequency
    OLED_WrCmd(0xDA);//--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WrCmd(0x12);//--set pre-charge period
    OLED_WrCmd(0x81);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WrCmd(0xEF);//--set com pins hardware configuration
    OLED_WrCmd(0xD9);
    OLED_WrCmd(0xf1);//--set vcomh
    OLED_WrCmd(0xDB);//Set VCOM Deselect Level
    OLED_WrCmd(0x30);//-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WrCmd(0xA4);//
    OLED_WrCmd(0xA6);//--set Charge Pump enable/disable
    OLED_WrCmd(0xAF);//--set(0x10) disable
    OLED_Fill(0x00);  //????
}
////////////////////////////////////////////////////////////////////////////////////

//����Ϊ�ײ�����
//����Ϊ������ʾ����
////////////////////////////////////////////////////////////////////////////////////
/***************������������ʾ6*8һ���׼ASCII�ַ���	��ʾ�����꣨x,y����yΪҳ��Χ0��7****************/
void LCD_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[])
{
	  unsigned char c=0,i=0,j=0;      
  while (ch[j]!='\0')
  {    
    c =ch[j]-32;
    if(x>126){x=0;y++;}
        OLED_Set_Pos(x,y);    
    for(i=0;i<6;i++) 
    {
      OLED_WrDat(F6x8[c][i]);
      //Delay_ms(60);
    }
    x+=6;
    j++;
  }
}

/*******************������������ʾ8*16һ���׼ASCII�ַ���	 ��ʾ�����꣨x,y����yΪҳ��Χ0��7****************/
void LCD_P8x16Str(unsigned char x,unsigned char y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{    
		c =ch[j]-32;
		if(x>120){x=0;y++;}
		OLED_Set_Pos(x,y);    
		for(i=0;i<8;i++)     
		OLED_WrDat(F8X16[c*16+i]);
		OLED_Set_Pos(x,y+1);    
		for(i=0;i<8;i++)     
		OLED_WrDat(F8X16[c*16+i+8]);  
		x+=8;
		j++;
	}
}
/*****************������������ʾ16*16����  ��ʾ�����꣨x,y����yΪҳ��Χ0��7****************************/
void LCD_P16x16Ch(unsigned char x,unsigned char y,unsigned char N)
{
	unsigned char wm=0;
	unsigned int adder=32*N;  //ÿ����ģ����ʼ��ַ  	
	OLED_Set_Pos(x , y);
	for(wm = 0;wm < 16;wm++)  //             
	{
		OLED_WrDat(F16x16[adder]);	
		adder += 1;
	}      									 //�ϰ���
	OLED_Set_Pos(x,y + 1); 
	for(wm = 0;wm < 16;wm++) //         
	{
		OLED_WrDat(F16x16[adder]);
		adder += 1;
	} 	  									 //�°���
}
/*****************������������ʾ32*32����  ��ʾ�����꣨x,y����yΪҳ��Χ0��7****************************/
void LCD_P32x32Ch(unsigned char x,unsigned char y,unsigned char N)
{
	unsigned char wm=0;
	unsigned int adder=128*N;  //  	
	OLED_Set_Pos(x , y);
	for(wm = 0;wm < 32;wm++)  //             
	{
		OLED_WrDat(F32x32[adder]);	
		adder += 1;
	}      
	OLED_Set_Pos(x,y + 1); 
	for(wm = 0;wm < 32;wm++) //         
	{
		OLED_WrDat(F32x32[adder]);
		adder += 1;
	} 
		OLED_Set_Pos(x,y + 2); 
	for(wm = 0;wm < 32;wm++) //         
	{
		OLED_WrDat(F32x32[adder]);
		adder += 1;
	} 
		OLED_Set_Pos(x,y + 3); 
	for(wm = 0;wm < 32;wm++) //         
	{
		OLED_WrDat(F32x32[adder]);
		adder += 1;
	} 			  	
}
//���� 
//x:0~127
//y:0~63
//t:1 ��� 0,���	
//���ƴ˺�����ʵ�ֺ��ַ�ת
void LCD_DrawPoint(unsigned char x,unsigned char y,unsigned char t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;//������Χ��.
//	pos=7-y/8;
	pos=y/8;
	bx=y%8;
//	temp=1<<(7-bx);
	temp=1<<bx;
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;	    

}
//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ				 
//size:ѡ������ 16/12 
void LCD_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode)
{      			    
	u8 temp,t,t1;
	u8 y0=y;
	chr=chr-' ';//�õ�ƫ�ƺ��ֵ				   
    for(t=0;t<size;t++)
    {   
		if(size==12)temp=oled_asc2_1206[chr][t]; //����1206����
		else if(size==16) temp=oled_asc2_1608[chr][t];		 //����1608���� 	                          
        else if(size==24)temp=oled_asc2_2412[chr][t];        //����2412����
		for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_DrawPoint(x,y,mode);
			else LCD_DrawPoint(x,y,!mode);
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}


void OLED_write_char(unsigned char c)
{
    unsigned char line;
    c -= 32;
    for (line = 0; line < 6 ; line ++)
      OLED_WrDat(F6x8[c][line]);
}

void OLED_write_3_num(unsigned char X,unsigned char Y,signed int s)
{   
    OLED_Set_Pos(X,Y);
    OLED_write_char((s/100)+0x30);
    OLED_write_char(((s%100)/10)+0x30);
    OLED_write_char((s%10)+0x30);	 
}

void OLED_write_4_num(unsigned char X,unsigned char Y,int s)
{
    OLED_Set_Pos(X,Y);
    OLED_write_char((s/100)+0x30);
    OLED_write_char(((s%100)/10)+0x30);
    OLED_write_char((s%10)+0x30);	 
}

void OLED_write_5_num(unsigned char X,unsigned char Y,int s)
{
    OLED_Set_Pos(X,Y);
    OLED_write_char((s/1000)+0x30);
    OLED_write_char(((s%1000)/100)+0x30);
    OLED_write_char((s%100/10)+0x30);
    OLED_write_char((s%10)+0x30);	 
}

void OLED_write_8_num(unsigned char X,unsigned char Y,int s)
{
    OLED_Set_Pos(X,Y);
    OLED_write_char((s/1000000)+0x30);
    OLED_write_char(((s%1000000)/100000)+0x30);
    OLED_write_char((s%100000/10000)+0x30);
	OLED_write_char((s%10000/1000)+0x30);
	OLED_write_char((s%1000/100)+0x30);
	OLED_write_char((s%100/10)+0x30);
    OLED_write_char((s%10)+0x30);	 
}
void OLED_write_2_num(unsigned char X,unsigned char Y,signed int s)
{
    OLED_Set_Pos(X,Y);
    OLED_write_char((s/10)+0x30);
    OLED_write_char((s%10)+0x30);	 
}

void OLED_write_1_num(unsigned char X,unsigned char Y,signed int s)
{
    OLED_Set_Pos(X,Y);
    OLED_write_char(s+0x30);	 
}

void Draw_LibLogo(void)
{
  u16 ii=0;
  u8 x,y;
	for(y=0;y<8;y++)
	{
	    OLED_Set_Pos(x,y);
            for(x=0;x<128;x++)
	    {
	    	OLED_WrDat(BMP[ii++]);
	    }
	}
}


//��ʾ�����ַ�
void OLED_P13x16Str(u8 x,u8 y,u8 ch[])
{
	u8 wm=0,ii = 0;
	u16 adder=1;

	while(ch[ii] != '\0')
	{
  	wm = 0;
  	adder = 1;
  	while(zhongwenzi_Idx[wm] > 127)
  	{
  		if(zhongwenzi_Idx[wm] == ch[ii])
  		{
  			if(zhongwenzi_Idx[wm + 1] == ch[ii + 1])
  			{
  				adder = wm * 13;
  				break;
  			}
  		}
  		wm += 2;
  	}
  	if(x>118){x=0;y++;}
  	OLED_Set_Pos(x , y);
  	if(adder != 1)// 
  	{
  		OLED_Set_Pos(x , y);
  		for(wm = 0;wm < 13;wm++)
  		{
  		  OLED_WrDat(zhongwenzi[adder]);
  		  adder += 1;
  		}
  		OLED_Set_Pos(x,y + 1);
  		for(wm = 0;wm < 13;wm++)
  		{
  		  OLED_WrDat(zhongwenzi[adder]);
  		  adder += 1;
  		}
  	}
  	else			  //
  	{
  		ii += 1;
                OLED_Set_Pos(x,y);
  		for(wm = 0;wm < 16;wm++)
  		{
  		  OLED_WrDat(0);
  		}
  		OLED_Set_Pos(x,y + 1);
  		for(wm = 0;wm < 16;wm++)
  		{
  		  OLED_WrDat(0);
  		}
  	}
  	x += 14;
  	ii += 2;
	}
}


//��ʾ�����ַ�
void OLED_P16x16Str(u8 x,u8 y,u8 ch[])
{
	u8 wm=0,ii = 0;
	u16 adder=1;

	while(ch[ii] != '\0')
	{
  	wm = 0;
  	adder = 1;
  	while(xu_j[wm] > 127)
  	{
  		if(xu_j[wm] == ch[ii])
  		{
  			if(xu_j[wm + 1] == ch[ii + 1])
  			{
  				adder = wm * 16;
  				break;
  			}
  		}
  		wm += 2;
  	}
  	if(x>118){x=0;y++;}
  	OLED_Set_Pos(x , y);
  	if(adder != 1)// 
  	{
  		OLED_Set_Pos(x , y);
  		for(wm = 0;wm < 16;wm++)
  		{
  		  OLED_WrDat(xu[adder]);
  		  adder += 1;
  		}
  		OLED_Set_Pos(x,y + 1);
  		for(wm = 0;wm < 16;wm++)
  		{
  		  OLED_WrDat(xu[adder]);
  		  adder += 1;
  		}
  	}
  	else			  //
  	{
  		ii += 1;
                OLED_Set_Pos(x,y);
  		for(wm = 0;wm < 16;wm++)
  		{
  		  OLED_WrDat(0);
  		}
  		OLED_Set_Pos(x,y + 1);
  		for(wm = 0;wm < 16;wm++)
  		{
  		  OLED_WrDat(0);
  		}
  	}
  	x += 14;
  	ii += 2;
	}
}

//��ʾ�����ַ�
void OLED_P12x12Str(u8 x,u8 y,u8 ch[])
{
	u8 wm=0,ii = 0;
	u16 adder=1;

	while(ch[ii] != '\0')
	{
  	wm = 0;
  	adder = 1;
  	while(xu12_j[wm] > 127)
  	{
  		if(xu12_j[wm] == ch[ii])
  		{
  			if(xu12_j[wm + 1] == ch[ii + 1])
  			{
  				adder = wm * 12;
  				break;
  			}
  		}
  		wm += 2;
  	}
  	if(x>118){x=0;y++;}
  	OLED_Set_Pos(x , y);
  	if(adder != 1)// 
  	{
  		OLED_Set_Pos(x , y);
  		for(wm = 0;wm < 12;wm++)
  		{
  		  OLED_WrDat(xu12[adder]);
  		  adder += 1;
  		}
  		OLED_Set_Pos(x,y + 1);
  		for(wm = 0;wm < 12;wm++)
  		{
  		  OLED_WrDat(xu12[adder]);
  		  adder += 1;
  		}
  	}
  	else			  //
  	{
  		ii += 1;
                OLED_Set_Pos(x,y);
  		for(wm = 0;wm < 16;wm++)
  		{
  		  OLED_WrDat(0);
  		}
  		OLED_Set_Pos(x,y + 1);
  		for(wm = 0;wm < 16;wm++)
  		{
  		  OLED_WrDat(0);
  		}
  	}
  	x += 14;
  	ii += 2;
	}
}


















