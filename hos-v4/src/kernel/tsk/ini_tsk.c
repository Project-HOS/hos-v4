/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル タスク制御                                              */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"


/* タスクの初期化 */
void kernel_ini_tsk(void)
{
	int i;

	/* TCBのRAM部はゼロ領域にしておいてコードで初期化したほうが効率がよい */
	for ( i = 0; i < kernel_tcb_cnt; i++ )
	{
		/* task アドレスのあるものだけ存在すると見なす */
		if ( kernel_tcb_ram_tbl[i] != NULL )
		{
			mknl_ini_tsk(&kernel_tcb_ram_tbl[i]->mtcb);
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
	tcb_rom = tcb_ram->tcbrom;

	mknl_unl_sys();			/* システムのロック解除 */

	tcb_rom->task(exinf);	/* タスク実行 */

	ext_tsk();	/* リターン時は終了 */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
