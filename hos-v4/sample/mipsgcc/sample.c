/*******************************************************************************
 * Hyper Operating System V4  サンプルプログラム
 *
 *  各タスクの起動時刻とタスク名をシリアルコンソールへ表示するプログラム
 *      タスク名    優先度  起動条件
 *      Task1       1       Task2からのsig_sem()により起動
 *      Task2       2       1[s]おきの周期タイマにより起動
 *
 *                                      Copyright (C) 1998-2007 by Project HOS
 *                                      http://sourceforge.jp/projects/hos/
 *******************************************************************************/

#include <semb1200a/semb1200a.h>
#include "kernel.h"
#include "kernel_id.h"
#include "sample.h"
#include "irq_sample.h"
#include <math.h>

/**
 *  main関数
 */
int
main(void)
{
	/* HOS-V4 の開始 */
	sta_hos();
	return 0;
}

/**
 *  初期化関数
 *  タスクの起動を行う
 */
void
sample_init (VP_INT exinf)
{
	act_tsk (TSKID_SAMPLE_1);
	act_tsk (TSKID_SAMPLE_2);
	act_tsk (TSKID_SAMPLE_3);

	/* 周期タイマの起動 */
	sta_cyc (CYCID_SAMPLE_1);
}

/**
 *  サンプルタスク1
 *  - タスク2がセマフォを解除するまで待つ
 *  - 現在時刻とタスク名を表示
 */
void
sample_task_1 (VP_INT exinf)
{
	for (;;) {
		wai_sem (SEMID_SAMPLE_1);
		sample_print (1);
	}
}

/**
 *  サンプルタスク2
 *  - 1[s]の間sleepする
 *  - セマフォを解除
 *  - 現在時刻とタスク名を表示
 */

double	b;

void
sample_task_2 (VP_INT exinf)
{
	static double	a = 0.0;

	for (;;){
		slp_tsk ();
		sig_sem (SEMID_SAMPLE_1);
		a += 0.1f;
		b = sin( a / M_PI );
		sample_print (2);
	}
}

void
sample_task_3 (VP_INT exinf)
{
	volatile double	a = 0.0, c;

	for (;;){
		a += 0.1f;
		c = cos( a / M_PI );
		uart1_putc( '.' );
		dly_tsk(100);
	}
}

/**
 *  現在時刻とタスクnoを表示する
 */
void
sample_print (int no)
{
	SYSTIM st;

	get_tim (&st);

	uart1_putc ('0'+ (st.ltime / 10000) % 10);
	uart1_putc ('0'+ (st.ltime / 1000) % 10);
	uart1_putc ('0'+ (st.ltime / 100) % 10);
	uart1_putc ('0'+ (st.ltime / 10) % 10);
	uart1_putc ('0'+ (st.ltime / 1) % 10);
	uart1_puts (":Task ");
	uart1_putc ('0'+no);

	if( no == 2 ) {
		uart1_putc( ' ' );
		uart1_outval( flag_tc0 );
		uart1_putc( ' ' );
		uart1_outval( (int)(b * 10000.0) );
		uart1_putc( ' ' );
	}
	uart1_puts ("\n\r");
}

void
sample_cycle_handler (VP_INT exinf)
{
	iwup_tsk (TSKID_SAMPLE_2);
}
