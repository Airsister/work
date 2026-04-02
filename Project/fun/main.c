#include <REGX52.H>
#include "Key.h"
#define SPEED 500
unsigned char keynum;
sbit Buzzer=P2^5;
unsigned int code FreqTable[]={
	63777,63872,63967,64053,64139,64214,64290,64359,64424,64488,64546,64602,
	64654,64703,64750,64794,64836,64875,64912,64947,64980,65012,65041,65069,
  65094,65119,65142,65165,65186,65205,65223,65241,65258,65273,65288,65302
};

unsigned char code Music_2[]={
  21,4+4,
  19,4,
  16,4+2,
	16,2,
	12,4,
	14,6, 
	12,2, 
	14,4, 
	16,3, 
	14,1,
	12,6,
	9,2, 
	9,4, 
	7,4, 
	12,4,
	12,4+4,
	7,4,
	12,6,
	12,2,
	12,4,
	16,2,
	14,6,
	12,2,
	14,4,
	16,2,
	14,2,
	12,4,
	12,4,
	16,4,
	19,4,
	21,4+4+4,
	21,2,
	19,6,
	16,2,
	16,4,
	12,4,
	14,4,
	16,	2,
  14,	2,
  12,	6,
  9,	2,
  9,	4,
  7,	4,
  12,	4,
  12,12,
  21,	4,
19,	8,
16,	6,
16,	2,
12,	4,
14,	6,
12,	2,
14,	4,
21,	2,
19,	6,
16,	2,
16,	4,
19,	4,
21,	4,
21,	12,
21,	4,
19,	8,
16,	4,
16,6,
12,	2,
14,	6,
12,	2,
14,	4,
16,	6,
14,	1,
12,	6,
9	,2,
9,	4,
7,	4,
12,	4,
12,	12,
21,	8,
19,	4,
16,	6,
16,	2,
12,	4,
14,	6,
12,	2,
14,	4,
16,	6,
14,	1,
12,	6,
9,	2,
9,	4,
7,	4,
12,	12,
12,	8,
7,	4,
21,	2,
19,	2,
16,	2,
19,	2,
21,	4,
21,	12,
24,	4,
19,	4,
16,	4,
16,	6,
14,	2,
16,	4,
16,	12

};
//unsigned char FreqSelect,MusicSelect;
//void main()
//{
//	
//   Timer0_Init();
//	  
//     while(1)
//		 {
//			 FreqSelect=Music_2[MusicSelect];
//			 MusicSelect++;
//       Delay_ms(SPEED/4*Music_2[MusicSelect]);
//			 MusicSelect++;
////			 if(MusicSelect>=sizeof(Music_2)/sizeof(unsigned char))
////			 {MusicSelect=0;}
//			 TR0=0;//发个音符后停止，避免连续同音无法区分
//			 Delay_ms(5);
//			 TR0=1;

//		 }
//}

unsigned char FreqSelect;
unsigned int MusicSelect = 0;       // 全局播放索引
bit MusicFinish = 0;                // 乐曲结束标志

void DelayMusic(unsigned int t)
{
	unsigned int i;
	for(i=0;i<t;i++)
	{
		Nixie(1, MusicSelect/10);
		Nixie(2, MusicSelect%10);
		Delay_ms(1);
		
	}
}


void main()
{
    Timer0_Init();
    while(1)
    {
        // ====================== 核心逻辑 ======================
        if(MusicFinish == 0)  // 没播完：正常播放
        {
            FreqSelect = Music_2[MusicSelect];
            MusicSelect++;
            
            // 显示当前 MusicSelect
            Nixie(1, MusicSelect / 10);    // 十位
            Nixie(2, MusicSelect % 10);    // 个位
            Delay_ms(SPEED/4 * Music_2[MusicSelect]);
            MusicSelect++;
            
            TR0 = 0;
            DelayMusic(5);
            TR0 = 1;
            
            // 判断是否播放完毕
            if(MusicSelect >= sizeof(Music_2)/sizeof(unsigned char))
            {
                MusicFinish = 1;   // 标记结束
                TR0 = 0;           // 关闭蜂鸣器
            }
        }
        else  // 播完：固定显示最后数值，不再增加
        {
            Nixie(1, MusicSelect / 10);
            Nixie(2, MusicSelect % 10);
        }
    }
}





unsigned int T0Count;
void Timer0_Routine() interrupt 1
{
	  //static unsigned int T0Count;
		TL0 = FreqTable[FreqSelect]%256;
	  TH0 = FreqTable[FreqSelect]/256;	  	  
	  Buzzer=!Buzzer;	
}
