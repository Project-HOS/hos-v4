/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル タスク制御                                              */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* タスクの生成(ID番号自動割付け) */
ER_ID acre_tsk(
		const T_CTSK *pk_ctsk)	/* タスク生成情報を入れたパケットへのポインタ */
{
	ID tskid;
	ER ercd;

	mknl_loc_sys();	/* システムのロック */

	/* 空きIDの検索 */
	for ( tskid = kernel_tcb_cnt; tskid >= TMIN_TSKID; tskid++ )
	{
		if ( KERNEL_TSKID_TO_TCB_RAM(tskid) == NULL )
		{
			break;
		}
	}
	if ( tskid < TMIN_TSKID )
	{
		mknl_unl_sys();		/* システムのロック解除 */
		return E_NOID;		/* ID番号不足 */
	}
	
	/* タスクの生成 */
	ercd = kernel_cre_tsk(tskid, pk_ctsk);

	mknl_unl_sys();	/* システムのロック解除 */

	if ( ercd != E_OK )
	{
		return (ER_ID)ercd;	/* エラー発生 */
	}

	return (ER_ID)tskid;		/* 成功 */
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
