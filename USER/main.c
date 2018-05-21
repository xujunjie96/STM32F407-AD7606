#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "oled.h"
#include "timer.h"
#include "ad7606.h"

int aa=0;
int c[8];
int j;
char a=0;
char b=0;
extern u16 channel[8];
int main(void)
{
	delay_init(168);
	LED_Init();
	ad7606io_init();
	ad7606_init();
	OLED_Init();
	//TIM3_Int_Init(500);//定时500ms
	ad7606_start();//开始转换
	 while(1)
	 {
		 for(aa=0;aa<100;aa++)
		 {
		 
			//a=AD_BUSY;
		 
		 while(AD_BUSY)
		 {
			delay_us(1);
		 }
		  delay_us(1);
		 ad7606_read();//读ad7606数据	
			for(j=0;j<8;j++)		 
		 {
			c[j]+=channel[j];
		 }
		
		// ad7606_reset();
		 ad7606_start();//开始转换
	 }
		 	for(j=0;j<8;j++)		 
		 {
			c[j]/=100;
		 }

		 OLED_write_8_num(0,0,c[0]);
		 OLED_write_8_num(0,1,c[1]);
		 OLED_write_8_num(0,2,c[2]);
		 OLED_write_8_num(0,3,c[3]);
		 OLED_write_8_num(63,0,c[4]);
		 OLED_write_8_num(63,1,c[5]);
		 OLED_write_8_num(63,2,c[6]);
		 OLED_write_8_num(63,3,c[7]);
//	 	 OLED_write_8_num(0,4,(float) c[0]/32767*5000);
//		 OLED_write_8_num(0,5,(float) c[1]/32767*5000);
//		 OLED_write_8_num(0,6,(float) c[2]/32767*5000);
//		 OLED_write_8_num(0,7,(float) c[3]/32767*5000);
//		 OLED_write_8_num(63,4,(float) c[4]/32767*5000);
//		 OLED_write_8_num(63,5,(float) c[5]/32767*5000);
//		 OLED_write_8_num(63,6,(float) c[6]/32767*5000);
//		 OLED_write_8_num(63,7,(float) c[7]/32767*5000);
		// delay_ms(50);
	 	for(j=0;j<8;j++)		 
		 {
			c[j]=0;
		 }

	 }
 }


void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update)!=RESET)
	{
		LED=!LED;
	}
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}







