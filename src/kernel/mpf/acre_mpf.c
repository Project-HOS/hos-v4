/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル 固定長メモリプール                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"



/* 固定長メモリプールの生成(ID番号自動割付け) */
ER_ID acre_mpf(
		const T_CMPF *pk_cmpf)	/* 固定長メモリプール生成情報を入れたパケットへのポインタ */
{
	ID mpfid;
	ER ercd;

	mknl_loc_sys();	/* システムのロック */

	/* 利用可能なIDの検索 */
	for ( mpfid = KERNEL_TMAX_MPFID; mpfid >= KERNEL_TMIN_MPFID; mpfid-- )
	{
		if ( KERNEL_MPFID_TO_MPFCB_RAM(mpfid) == NULL )
		{
			break;
		}
	}
	
	/* ID番号不足チェック */
#ifdef HOS_ERCHK_E_NOID
	if ( mpfid < KERNEL_TMIN_MPFID )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOID;	/* ID番号不足 */
	}
#endif

	/* 固定長メモリプールの生成 */
	ercd = kernel_cre_mpf(mpfid, pk_cmpf);
	if ( ercd != E_OK )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return (ER_ID)ercd;
	}
	
	mknl_unl_sys();	/* システムのロック解除 */

	return (ER_ID)mpfid;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
