/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル 周期ハンドラ                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_cyc.h"


/* タスクの生成 */
ER cre_cyc(
		ID           cycid,		/* 生成対象の周期ハンドラのID番号 */
		const T_CCYC *pk_ccyc)	/* 周期ハンドラ生成情報を入れたパケットへのポインタ */
{
	ER ercd;

	/* ID 範囲チェック */
#ifdef HOS_ERCHK_E_ID
	if ( cycid < KERNEL_TMIN_CYCID || cycid > KERNEL_TMAX_CYCID )
	{
		return E_ID;	/* 不正ID番号 */
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	/* タスクが登録可能かチェック */
#ifdef HOS_ERCHK_E_OBJ
	if ( KERNEL_CYCID_TO_CYCCB_RAM(cycid) != NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_OBJ;	/* 既に登録済み */
	}
#endif
	
	/* タスクの生成 */
	ercd = kernel_cre_cyc(cycid, pk_ccyc);

	mknl_unl_sys();	/* システムのロック解除 */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
