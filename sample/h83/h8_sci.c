/* ------------------------------------------------------------------------ */
/*  H8/3048用 SCI制御ライブラリ                                             */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include "kernel.h"
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

#define RECV_BUFSIZE	32		/* 受信バッファのサイズ */



static unsigned char recv_buf[32];
static int head;
static int tail;



/* SCI初期化 */
void Sci_Initialize(unsigned char rate)
{
	volatile int v;
	int i;
	
	/* SCI初期化 */
	SCR  = 0x00;
	SMR  = 0x00;
	BRR  = rate;
	for ( i = 0; i < 280; i++ )
		v++;
	SCR  = 0x70;
	SSR &= 0x80;
	
	/* 受信バッファ初期化 */
	head = 0;
	tail = 0;
}


/* １文字出力 */
void Sci_PutChar(char c)
{
	while ( !(SSR & 0x80) )
		;
	
	TDR  = c;
	SSR &= 0x7f;
}


/* １文字入力 */
int Sci_GetChar(void)
{
	if ( head == tail )
	{
		return -1;
	}
	
	return recv_buf[head++];
}


/* SCI受信割り込み */
void Sci_RxiHandler(VP_INT exinf)
{
	unsigned char c;
	int next;
	
	/* 1文字受信 */
	c = RDR;
	SSR &= 0xbf;
	
	/* 次の末尾位置を計算 */
	next = tail + 1;
	if ( next >= RECV_BUFSIZE )
	{
		next = 0;
	}
	
	/* オーバーフローチェック */
	if ( next == head )
	{
		return;
	}
	
	/* 受信バッファに格納 */
	recv_buf[tail] = c;
	tail = next;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
