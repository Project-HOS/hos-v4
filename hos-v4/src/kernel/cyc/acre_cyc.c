/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル 周期ハンドラ                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_cyc.h"


/* 周期ハンドラの生成(ID番号自動割付け) */
ER_ID acre_cyc(
		const T_CCYC *pk_ccyc)	/* 周期ハンドラ生成情報を入れたパケットへのポインタ */
{
	ID cycid;
	ER ercd;

	mknl_loc_sys();	/* システムのロック */

	/* 空きIDの検索 */
	for ( cycid = KERNEL_TMAX_CYCID; cycid >= KERNEL_TMIN_CYCID; cycid-- )
	{
		if ( KERNEL_CYCID_TO_CYCCB_RAM(cycid) == NULL )
		{
			break;
		}
	}
	if ( cycid < KERNEL_TMIN_CYCID )
	{
		mknl_unl_sys();		/* システムのロック解除 */
		return E_NOID;		/* ID番号不足 */
	}
	
	/* 周期ハンドラの生成 */
	ercd = kernel_cre_cyc(cycid, pk_ccyc);

	mknl_unl_sys();	/* システムのロック解除 */

	if ( ercd != E_OK )
	{
		return (ER_ID)ercd;	/* エラー発生 */
	}

	return (ER_ID)cycid;		/* 成功 */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
