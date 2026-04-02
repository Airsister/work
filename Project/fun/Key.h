#ifndef __KEY_H__
#define __KEY_H__
#include <REGX52.H>
#include <INTRINS.H>

unsigned char Key_Get(void);
void Nixie(unsigned char Location,unsigned char Numer);
void Timer0_Init(void);
void Delay_ms(unsigned int m);
void Buzzer_Time(unsigned int ms);
#endif
