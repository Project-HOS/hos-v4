/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル システム状態管理                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sys.h"



/* タスクIDの取得 */
ID kernel_get_tid(T_KERNEL_TCB_RAM *tcb_ram)
{
	ID tskid;
	
	/* タスクIDを検索 */
	for ( tskid = KERNEL_TMAX_TSKID; tskid >= KERNEL_TMIN_TSKID; tskid-- )
	{
		if ( tcb_ram == KERNEL_TSKID_TO_TCB_RAM(tskid) )
		{
			break;
		}
	}
	
	return tskid;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
