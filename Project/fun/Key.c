#include "Key.h"

void Delay_ms(unsigned int m)		//@11.0592MHz
{
	unsigned char i, j;
	while(m)
	{
	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
	m--;
	}		
}

void Delay500us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 6;
	j = 93;
	do
	{
		while (--j);
	} while (--i);
}



unsigned char Key_Get(void)
{
	unsigned char Keynum=0;
	if(P3_0==0){Delay_ms(20);while(P3_0==0){Delay_ms(20);Keynum=1;}}
	if(P3_1==0){Delay_ms(20);while(P3_1==0){Delay_ms(20);Keynum=2;}}
	if(P3_2==0){Delay_ms(20);while(P3_2==0){Delay_ms(20);Keynum=3;}}
	if(P3_3==0){Delay_ms(20);while(P3_3==0){Delay_ms(20);Keynum=4;}}
	return Keynum;
}


void Timer0_Init(void)
{
	
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
  ET0=1;//允许中断
  EA=1;//全局中断
	PT0=0;//优先级，0表示低优先级
//  TMOD=0x01;//选择模式，不可以同时设置两个定时器
//	TMOD=TMOD&0xF0;//清低四位为0，保存高四位
//	TMOD=TMOD|0x01;
//	TF0=0;//中断进入开关（0表示未进入）
//	TR0=1;//启动定时器
//	TH0=(65535-921)/256;
//	TL0=(65535-921)%256;//TH0和TL0是用来设置计时周期的（重装载值）
//	ET0=1;//允许中断
//	EA=1;//全局中断
//	PT0=0;//优先级，0表示低优先级
}

unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
void Delay_ms(unsigned int m);
void Nixie(unsigned char Location,unsigned char Numer)
{
	
	switch(Location)
	{
		case 1:P2_4=1;P2_3=1;P2_2=1;break;	
		case 2:P2_4=1;P2_3=1;P2_2=0;break;	
		case 3:P2_4=1;P2_3=0;P2_2=1;break;
		case 4:P2_4=1;P2_3=0;P2_2=0;break;
		case 5:P2_4=0;P2_3=1;P2_2=0;break;
		case 6:P2_4=0;P2_3=0;P2_2=1;break;
		case 7:P2_4=0;P2_3=0;P2_2=0;break;		
	}
	P0=NixieTable[Numer];
	Delay_ms(1);
	P0=0x00;
}

//void Buzzer_Time(unsigned int ms)
//{
//	 unsigned int i;
//	  for(i=0;i<ms*2;i++)
//	 {
//		 Buzzer=!Buzzer;
//		 Delay500us();
//	  }
//}










