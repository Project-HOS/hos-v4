/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル タスク例外処理機能                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* タスク例外処理エントリーポイント(μカーネルより呼び出し) */
void kernel_tex_entry(void)
{
	T_KERNEL_TCB_RAM   *tcb_ram;
	T_KERNEL_TEXCB_RAM *texcb;
	TEXPTN rasptn;
	
	tcb_ram = kernel_get_run_tsk();
	texcb   = tcb_ram->texcb;
	
	/* タスク例外要因クリア */
	rasptn = texcb->rasptn;
	texcb->rasptn = 0;
	
	mknl_dis_tex(&tcb_ram->mtcb);	/* タスク例外処理の禁止 */
	mknl_unl_sys();					/* システムのロック解除 */

	texcb->texrtn(rasptn);			/* タスク例外処理ルーチンの呼び出し */

	mknl_loc_sys();					/* システムのロック */
	mknl_ena_tex(&tcb_ram->mtcb);	/* タスク例外処理の許可 */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
