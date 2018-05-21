#include "ad7606.h"
#include "delay.h"


//u16 channel_a=0,channel_b=0,channel_c=0,channel_d=0,channel_e=0,channel_f=0,channel_g=0,channel_h=0;
u16 channel[8];
int q[16];
extern char a,b;	

void ad7606io_init(void) //初始化ad7606io
{
 GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOF时钟

  /*****************************输出引脚初始化*****************************/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;//
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA输出
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC输出
	
	/*****************************输入引脚初始化*****************************/
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB输入：FASTDATA、BUSY

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA输入：DB15-8
			
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB输入：DB5-0
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC输入：DB7-6

}
void ad7606_init(void)	//AD7606初始化
{
 
	
	/*****************************初始化*****************************/

	AD_STBY=1;	//待机模式关闭
	delay_ms(50);
	AD_MODE=0;	//并行接口模式
	AD_OS0=0;
	AD_OS1=0;
	AD_OS2=0; //过采样关闭
	ad7606_reset();//硬件复位
	
	AD_CONVST=1;
}

void ad7606_reset(void)	//复位函数
{
	AD_RST=0;
	delay_us(1);
	AD_RST=1;
	delay_us(1);
	AD_RST=0;
	delay_us(1);
}

void ad7606_start(void)//开始转换
{
	AD_CS=1;
	AD_RD=1;
	delay_us(1);
	AD_CONVST=1;
	delay_us(1);
	AD_CONVST=0;
	delay_us(1);
	AD_CONVST=1;
}

void ad7606_read(void)//读ad7606数据
{
	u16 pa,pb,pc;
	int i=0;
	AD_CS=0;

	for(i=0;i<8;i++)
	{
		AD_RD=0;
		AD_RD=0;
		channel[i]=0;
		delay_us(1);
		pa = GPIO_ReadInputData(GPIOA);
		pb = GPIO_ReadInputData(GPIOB);
		pc = GPIO_ReadInputData(GPIOC);
		channel[i]=((pa&0x01)<<15)+((pa&0x02)<<13)+((pa&0x04)<<11)+((pa&0x08)<< 9)+
							((pa&0x10)<< 7)+((pa&0x20)<< 5)+((pa&0x40)<< 3)+((pa&0x80)<< 1)+
							((pc&0x10)<< 3)+((pc&0x20)<< 1)+((pb&0x01)<< 5)+((pb&0x02)<< 3)+
							((pb&0x400)>> 7)+((pb&0x800)>> 9)+((pb&0x1000)>>11)+((pb&0x2000)>> 13);
		//读通道i值
		AD_RD=1;
		AD_RD=1;
	}

	AD_CONVST=1;
	ad7606_reset();
	
	AD_CONVST=1;
	AD_CS=1;
}


