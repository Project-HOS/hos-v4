/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル システム状態管理                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sys.h"



/* 実行状態タスクIDの参照 */
ER get_tid(ID *p_tskid)
{
	T_KERNEL_TCB_RAM *tcb_ram;

	mknl_loc_sys();	/* システムのロック */

	tcb_ram = kernel_get_run_tsk();	/* 実行中のタスクを取得 */
	if ( tcb_ram == NULL )
	{
		*p_tskid = TSK_NONE;	/* 実行中のタスクが存在しない */
	}
	else
	{
		*p_tskid = kernel_get_tid(tcb_ram);	/* 実行中のタスクを取得 */
	}

	mknl_unl_sys();	/* システムのロック解除 */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
