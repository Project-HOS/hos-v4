/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*   Hitachi H8 用 サンプルプログラム                                       */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"
#include "kernel_id.h"
#include "h8_3048.h"
#include "h8_sci.h"



/* メイン関数 */
int main()
{
/*	SCI_Init(0x19); */	/* moniter ROM が初期化しているのでいじらない (^^;; */
	
	/* ITU0 (システムタイマ）初期化 */
	TCR0   = 0x23;		/* φ/8でカウント */
	TSR0  &= 0xfe;		/* ステータスレジスタクリア */
	TIER0  = 0x01;		/* 割り込み許可 */
	GRA0   = 2000 - 1;	/* 1 msec のインターバル（16MHz時） */
	TSTR  |= 0x01;		/* TCNT0動作開始 */
	
	/* 開始メッセージ */
	SCI_Putc('H');
	SCI_Putc('O');
	SCI_Putc('S');
	SCI_Putc('\r');
	SCI_Putc('\n');
	
	sta_hos();
}


/* 初期化ハンドラ */
void Initialize(VP_INT exinf)
{
	act_tsk(TSKID_SAMPLE1);
}


/* サンプルタスク */
void Task1(VP_INT exinf)
{
	SYSTIM st;
	
	for ( ; ; )
	{
		/* タイマ値取得 */
		get_tim(&st);
		
		/* タイマ値出力 */
		SCI_Putc('0' + (st.ltime / 10000) % 10);
		SCI_Putc('0' + (st.ltime / 1000) % 10);
		SCI_Putc('0' + (st.ltime / 100) % 10);
		SCI_Putc('0' + (st.ltime / 10) % 10);
		SCI_Putc('0' + (st.ltime / 1) % 10);
		SCI_Putc(':');
		
		/* タスクメッセージ */
		SCI_Putc('T');
		SCI_Putc('a');
		SCI_Putc('s');
		SCI_Putc('k');
		SCI_Putc('1');
		SCI_Putc('\r');
		SCI_Putc('\n');
		
		/* 1秒待つ */
		dly_tsk(1000);
	}
}


/* タイマ用割り込みハンドラ */
void timer_handler(VP_INT exinf)
{
	TSR0 &= 0xfe;
	
	/* タイムティック供給 */
	isig_tim();
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
