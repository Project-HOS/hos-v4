/* ------------------------------------------------------------------------ */
/*  H8/3048用 SCI制御ライブラリ                                             */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


/* 現時点では、テスト用にポーリングで文字を出すのみ */


#include "h8_3048.h"
#include "h8_sci.h"



/* 使用ポートの定義 */
#ifdef __USE_SCI0
#define SMR     SMR0
#define BRR     BRR0
#define SCR     SCR0
#define TDR     TDR0
#define SSR     SSR0
#define RDR     RDR0
#else
#define SMR     SMR1
#define BRR     BRR1
#define SCR     SCR1
#define TDR     TDR1
#define SSR     SSR1
#define RDR     RDR1
#endif



/* SCI初期化 */
void SCI_Init(unsigned char rate)
{
	volatile int v;
	int i;
	
	/* SCI初期化 */
	SCR  = 0x00;
	SMR  = 0x00;
	BRR  = rate;
	for ( i = 0; i < 280; i++ )
		v++;
	SCR  = 0x30;
	SSR &= 0x80;
}


/* １文字出力 */
void SCI_Putc(char c)
{
	while ( !(SSR & 0x80) )
		;
	TDR  = c;
	SSR &= 0x7f;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
