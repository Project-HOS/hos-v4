/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル タスク管理機能                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"


/* タスクの生成 */
ER cre_tsk(
		ID           tskid,		/* 生成対象のタスクID番号 */
		const T_CTSK *pk_ctsk)	/* タスク生成情報を入れたパケットへのポインタ */
{
	ER ercd;

	/* ID 範囲チェック */
#ifdef HOS_ERCHK_E_ID
	if ( tskid < TMIN_TSKID || tskid > TMAX_TSKID )
	{
		return E_ID;	/* 不正ID番号 */
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	if ( KERNEL_TSKID_TO_TCB_RAM(tskid) != NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_ID;	/* IDが使用できない */
	}
	
	/* タスクの生成 */
	ercd = kernel_cre_tsk(tskid, pk_ctsk);

	mknl_unl_sys();	/* システムのロック解除 */

	return ercd;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
