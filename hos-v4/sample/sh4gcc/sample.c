/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include "kernel.h"
#include "kernel_id.h"
#include "sh7750.h"
#include "scif.h"


/* メイン関数 */
int main()
{
	/* 開始メッセージ */
	scif_puts("HOS-V4/SH4 test program start.\n");
	sta_hos();
	
	return 0;
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
		scif_putc('0' + (st.ltime / 10000) % 10);
		scif_putc('0' + (st.ltime / 1000) % 10);
		scif_putc('0' + (st.ltime / 100) % 10);
		scif_putc('0' + (st.ltime / 10) % 10);
		scif_putc('0' + (st.ltime / 1) % 10);
		scif_putc(':');
		
		/* タスクメッセージ */
		scif_puts("Task1\r\n");
		
		/* 1秒待つ */
		dly_tsk(1000);
	}
}


/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
