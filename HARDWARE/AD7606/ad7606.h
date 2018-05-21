#ifndef __AD7606_H			//Ϊ�˱����ظ����壬��ֻ�ᱻ����һ��

#define __AD7606_H
#include "sys.h"

/****************���ƿ�****************/
#define AD_CS   			PCout(6)
#define AD_RD  				PCout(7)
#define AD_RST   			PCout(8)
#define AD_CONVST  		PCout(9)
#define AD_STBY   		PAout(8)
#define AD_MODE   		PAout(9)
#define AD_OS2  			PAout(10)
#define AD_OS1 			  PAout(11)
#define AD_OS0 			  PAout(12)

#define AD_FASTDATA  	PBin(14)
#define AD_BUSY   		PBin(15)

/****************���ݿ�****************/
#define AD_DB0   			PBin(13)
#define AD_DB1   			PBin(12)
#define AD_DB2   			PBin(11)
#define AD_DB3   			PBin(10)
#define AD_DB4   			PBin(1)
#define AD_DB5   			PBin(0)
#define AD_DB6   			PCin(5)
#define AD_DB7   			PCin(4)
#define AD_DB8   			PAin(7)
#define AD_DB9   			PAin(6)
#define AD_DB10  			PAin(5)
#define AD_DB11   		PAin(4)
#define AD_DB12   		PAin(3)
#define AD_DB13  			PAin(2)
#define AD_DB14  			PAin(1)
#define AD_DB15   		PAin(0)


void ad7606io_init(void);//��ʼ��ad7606io
void ad7606_init(void);//��ʼ��ad7606
void ad7606_reset(void);//Ӳ����λ
void ad7606_start(void);//��ʼת��

void ad7606_read(void);//��ad7606����

#endif

