#include <reg52.h>
#include "usart.h"
#include "iic.h"  
/*
硬件接法：
GY-33----C51
SCL---P3^6
SDA---P3^7
C51---FT232
TX ---RX
RX ---TX
软件说明：
该程序采用IIC对GY-33进行读取数据
采用上位机发送对应指令：
A5 51 F6 ----上传数据
A5 BB 60 ----白平衡
注：
	IIC时钟频率需低于100Khz；
	中断函数位于stc_it.c
联系方式：
http://shop62474960.taobao.com/?spm=a230r.7195193.1997079397.2.9qa3Ky&v=1
*/
typedef struct
{
    uint16_t Red;
    uint16_t Green;
    uint16_t Blue;
    uint16_t Clear;
} RGBC;
typedef struct
{
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
} RGB;
void delay(unsigned int x)
{
	while(x--);
}
int main(void)
{
	unsigned char  raw_data[9]={0};
	unsigned int datas[4]={0};
	RGBC rgbc={0,0,0,0};
	RGB rgb={0,0,0};
	uint16_t CT=0,Lux=0;
	u8 color=0;

	Usart_Int(9600);
 	while(1)
	{
		if(Calibration==0)//读取数据并上传给上位机
		{
			if(Single_ReadI2C(0xb4,0x00,raw_data,8))//读取原始RGBC值
			{
				datas[0]=rgbc.Red=(raw_data[0]<<8)|raw_data[1];
				datas[1]=rgbc.Green=(raw_data[2]<<8)|raw_data[3];
				datas[2]=rgbc.Blue=(raw_data[4]<<8)|raw_data[5];
				datas[3]=rgbc.Clear=(raw_data[6]<<8)|raw_data[7];
			}
			send_out(datas,4,0x15);//串口发送
			
			if(Single_ReadI2C(0xb4,0x08,raw_data,4))//读取色温，亮度
			{
			    datas[0]=Lux=(raw_data[0]<<8)|raw_data[1];
				datas[1]=CT=(raw_data[2]<<8)|raw_data[3];
			
			}
			if(Single_ReadI2C(0xb4,0x0f,raw_data,1))//读取颜色
				datas[2]=color=raw_data[0];
			 send_out(datas,3,0x25);//串口发送
			
			if(Single_ReadI2C(0xb4,0x0c,raw_data,3))//读取处理后的rgb
			{
				rgb.Red=raw_data[0];
				rgb.Green=raw_data[1];
				rgb.Blue=raw_data[2];
			}
			send_3out(raw_data,3,0x45);//串口发送
			
		}
		delay(5000);
		if(Calibration==1)//发送一次白平衡指令
		{
			Single_WriteI2C_byte(0xb4,0x10,0x31);
			Calibration=3;
		}
	}
}
