/* ------------------------------------------------------------------------ */
/*  H8/3664用 SCI3制御ライブラリ                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#include "kernel.h"
#include "h83664f.h"
#include "h8t_sci.h"

#define RECV_BUFSIZE	32		/* 受信バッファのサイズ */

static unsigned char recv_buf[RECV_BUFSIZE];
static int head;
static int tail;

/* SCI3初期化 */
void SCI3_Initialize(unsigned char rate)
{
	volatile int i;
	
	/* SCI3初期化 */
	SCI3.SCR3.BYTE = 0x00;
	SCI3.SMR.BYTE = 0x00;
	SCI3.BRR = rate;
	for ( i = 0; i < 280; i++ )
		;
	SCI3.SCR3.BYTE = 0x30; /* 送信可|受信可 */
	IO.PMR1.BIT.TXD = 1;
}

/* １文字出力 */
void SCI3_PutChar(char c)
{
	while ( !(SCI3.SSR.BYTE & 0x80) )
		;

	SCI3.TDR  = c;
/*      SCI3.SSR.BYTE &= 0x7f;  */
}

/* １文字入力 */
int SCI3_GetChar(void)
{
	int c;

	if ( head == tail )
	{
		return -1;
	}

	c = recv_buf[head++];
	if ( head == RECV_BUFSIZE )
	{
		head = 0;
	}
	
	return c;
}

/* SCI受信割り込み */
void SCI3_RxiHandler(VP_INT exinf)
{
	unsigned char c;
	int next;
	
	/* 1文字受信 */
	c = SCI3.RDR;
	SCI3.SSR.BYTE &= 0xbf;
	
	/* 次の末尾位置を計算 */
	next = tail + 1;
	if ( next == RECV_BUFSIZE )
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
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
