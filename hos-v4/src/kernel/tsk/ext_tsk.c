/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル タスク制御                                              */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* 自タスクの終了 */
void ext_tsk()
{
	const T_KERNEL_TCB_ROM *tcb_rom;
	T_KERNEL_TCB_RAM *tcb_ram;
	T_MKNL_TCB *mtcb;

	mtcb = mknl_get_run_tsk();

	mknl_loc_sys();	/* システムのロック */

	/* 実行タスクの終了 */
	mknl_ext_tsk(mtcb);

	tcb_ram = KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mknl_get_run_tsk());
	tcb_rom = tcb_ram->tcbrom;

	/* 起動がキューイングされていたなら */
	if ( tcb_ram->actcnt > 0 )
	{
		tcb_ram->actcnt--;	/* キューイング減算 */

		/* 実行コンテキスト登録 */
		mknl_sta_tsk(
				&tcb_ram->mtcb,			/* 登録するタスク */
				tcb_rom->exinf,			/* タスクの拡張情報 */
				(FP)kernel_task_entry,	/* タスクの起動番地 */
				tcb_rom->itskpri,		/* タスクの起動時優先度 */
				tcb_rom->stksz,			/* タスクのスタック領域サイズ */
				tcb_rom->stk			/* タスクのスタック領域の先頭番地 */
			);	
		tcb_ram->suscnt = 0;	/* 強制待ちネストクリア */
		tcb_ram->wupcnt = 0;	/* 待ち解除要求キューイングクリア */
	}

	/* タスクディスパッチの実行 */
	mknl_exe_dsp();
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
