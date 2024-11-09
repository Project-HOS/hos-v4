/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル タスク管理機能                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* タスクの初期化 */
void kernel_ini_tsk(void)
{
	T_KERNEL_TCB_RAM *tcb_ram;
	int i;

	/* TCBのRAM部はゼロ領域にしておいてコードで初期化したほうが効率がよい */
	for ( i = KERNEL_TMIN_TSKID; i <= KERNEL_TMAX_TSKID; i++ )
	{
		tcb_ram = KERNEL_TSKID_TO_TCB_RAM(i);
		if ( tcb_ram != NULL )
		{
			/* μカーネル部分の初期化 */
			mknl_ini_tsk(&tcb_ram->mtcb);
			
			/* TA_ACT属性のものを起動する */
			if ( tcb_ram->tcb_rom->tskatr & TA_ACT )
			{
				act_tsk(i);
			}
		}
	}
}


/* タスクのエントリーポイント */
void kernel_task_entry(
		VP_INT exinf)		/* タスクの拡張情報 */
{
	register const T_KERNEL_TCB_ROM *tcb_rom;
	register T_KERNEL_TCB_RAM *tcb_ram;

	/* スタートアドレスの算出 */
	tcb_ram = KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mknl_get_run_tsk());
	tcb_rom = tcb_ram->tcb_rom;

	mknl_unl_sys();			/* システムのロック解除 */

	tcb_rom->task(exinf);	/* タスク実行 */

	ext_tsk();	/* リターン時は終了 */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
