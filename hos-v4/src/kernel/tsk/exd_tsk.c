/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル タスク管理機能                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"
#include "knl_sys.h"
#include "knl_mem.h"



/* 自タスクの終了と削除 */
void exd_tsk(void)
{
	T_KERNEL_TCB_RAM *tcb_ram;
	T_MKNL_TCB *mtcb_run;
	ID tskid;

	/* 実行中タスクの取得 */
	mtcb_run = mknl_get_run_tsk();

	mknl_loc_sys();	/* システムのロック */

	/* 実行タスクの終了 */
	mknl_ext_tsk(mtcb_run);

	tcb_ram = KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb_run);
	tskid = kernel_get_tid(tcb_ram);
	
	/* メモリの解放(システムロック解除までは解放した領域も安全であることを保障する) */
	kernel_fre_mem(tcb_ram);

	/* タスクコントロールブロックテーブルから登録解除 */
	kernel_tcb_ram_tbl[tskid - TMIN_TSKID] = NULL;

	/* タスクディスパッチの実行 */
	mknl_exe_dsp();
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
