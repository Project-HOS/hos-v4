/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル タスク管理機能                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"


static void kernel_ext_tsk(VP_INT exinf);	/* タスクの終了処理(システムタスクで実行) */



/* 自タスクの終了 */
void ext_tsk(void)
{
	T_KERNEL_TCB_RAM *tcb_ram;
	T_MKNL_TCB       *mtcb_run;

	/* 実行中タスクの取得 */
	mtcb_run = mknl_get_run_tsk();
	tcb_ram  = KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb_run);

	mknl_loc_sys();		/* システムのロック */

	/* システムタスクから処理を行う */
	mknl_exe_sys((FP)kernel_ext_tsk, (VP_INT)tcb_ram);
}



/* タスクの終了処理(システムタスクで実行) */
void kernel_ext_tsk(VP_INT exinf)
{
	const T_KERNEL_TCB_ROM *tcb_rom;
	T_KERNEL_TCB_RAM       *tcb_ram;
	
	tcb_ram = (T_KERNEL_TCB_RAM *)exinf;
	tcb_rom = tcb_ram->tcb_rom;
	
	/* タスクを終了させる */
	mknl_ter_tsk(&tcb_ram->mtcb);

	/* 起動がキューイングされていたなら */
	if ( tcb_ram->actcnt > 0 )
	{
		tcb_ram->actcnt--;		/* キューイング減算 */
		tcb_ram->suscnt = 0;	/* 強制待ちネストクリア */
		tcb_ram->wupcnt = 0;	/* 待ち解除要求キューイングクリア */

		/* 再度タスクを生成 */
		mknl_sta_tsk(
				&tcb_ram->mtcb,			/* 登録するタスク */
				tcb_rom->exinf,			/* タスクの拡張情報 */
				(FP)kernel_task_entry,	/* タスクの起動番地 */
				tcb_rom->itskpri,		/* タスクの起動時優先度 */
				tcb_rom->stksz,			/* タスクのスタック領域サイズ */
				tcb_rom->stk			/* タスクのスタック領域の先頭番地 */
			);	
	}
	
	/* タスクディスパッチの実行 */
	mknl_exe_dsp();
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
