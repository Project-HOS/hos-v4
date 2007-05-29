/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル タスク管理機能                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"
#include "knl_sys.h"
#include "knl_mem.h"


static void kernel_exd_tsk(VP_INT exinf);	/* 自タスクの終了と削除(システムタスクで実行) */


/* 自タスクの終了と削除 */
void exd_tsk(void)
{
	T_KERNEL_TCB_RAM *tcb_ram;
	T_MKNL_TCB       *mtcb_run;

	/* 実行中タスクの取得 */
	mtcb_run = mknl_get_run_tsk();
	tcb_ram  = KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb_run);

	mknl_loc_sys();		/* システムのロック */

	/* システムタスクから処理を行う */
	mknl_exe_sys((FP)kernel_exd_tsk, (VP_INT)tcb_ram);
}


/* 自タスクの終了と削除(システムタスクで実行) */
void kernel_exd_tsk(VP_INT exinf)
{
	T_KERNEL_TCB_RAM *tcb_ram;
	ID               tskid;
	
	tcb_ram = (T_KERNEL_TCB_RAM *)exinf;
	tskid   = kernel_get_tid(tcb_ram);

	/* タスクを終了させる */
	mknl_ter_tsk(&tcb_ram->mtcb);
	
	/* メモリの解放 */
	kernel_fre_mem(tcb_ram);
	
	/* タスクコントロールブロックテーブルから登録解除 */
	KERNEL_TSKID_TO_TCB_RAM(tskid) = NULL;

	/* タスクディスパッチの実行 */
	mknl_exe_dsp();
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
