/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*   H8/3048用 SCI制御ライブラリ                                            */
/*                                                                          */
/* 1. 著作者は本ソースファイルの利用によって発生する如何なる損害にもその    */
/*    責任を負いません。                                                    */
/* 2. 再配布において著作権情報及び免責事項の情報改竄を固く禁じます。        */
/* 3. 上記を守る限り、改版したものの再配布を含め、商用／非商用を問わず      */
/*    あらゆる用途に自由に利用できます。                                    */
/* 4. 改版物の再配布時は、改版者の著作情報と連絡先を必ず追記してください。  */
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
	SCR  = 0x50;
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
