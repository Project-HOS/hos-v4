/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル システム状態管理                                        */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* 実行状態タスクIDの参照 */
ER get_tid(ID *p_tskid)
{
	T_KERNEL_TCB_RAM *tcb_ram;
	T_MKNL_TCB *mtcb;
	ID tskid;

	/* 実行中に自タスクIDが変化することは無い為ロックは行わない */

	mtcb = mknl_get_run_tsk();	/* 実行中のタスクを取得 */
	*p_tskid = TSK_NONE;
	if ( mtcb != NULL )
	{
		/* 実行中のタスクを取得 */
		tcb_ram = KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb);
		
		/* タスクIDを検索 */
		for ( tskid = TMIN_TSKID; tskid <= kernel_tcb_cnt; tskid++ )
		{
			if ( tcb_ram == KERNEL_TSKID_TO_TCB_RAM(tskid) )
			{
				*p_tskid = tskid;
				break;
			}
		}
	}

	return E_OK;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
