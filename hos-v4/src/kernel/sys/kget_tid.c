/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル システム状態管理                                        */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* タスクIDの取得 */
ID kernel_get_tid(T_KERNEL_TCB_RAM *tcb_ram)
{
	ID tskid;
	
	/* タスクIDを検索 */
	for ( tskid = TMAX_TSKID; tskid >= TMIN_TSKID; tskid-- )
	{
		if ( tcb_ram == KERNEL_TSKID_TO_TCB_RAM(tskid) )
		{
			break;
		}
	}
	
	return tskid;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
