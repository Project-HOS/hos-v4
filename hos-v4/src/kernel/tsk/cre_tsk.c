/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル タスク管理機能                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
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
	if ( tskid < TMIN_TSKID || tskid > KERNEL_TMAX_TSKID )
	{
		return E_ID;	/* 不正ID番号 */
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	/* タスクが登録可能かチェック */
#ifdef HOS_ERCHK_E_OBJ
	if ( KERNEL_TSKID_TO_TCB_RAM(tskid) != NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_OBJ;	/* 既に登録済み */
	}
#endif
	
	/* タスクの生成 */
	ercd = kernel_cre_tsk(tskid, pk_ctsk);

	mknl_unl_sys();	/* システムのロック解除 */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
