/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル 固定長メモリプール                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"



/* 固定長メモリプールの生成 */
ER cre_mpf(
		ID           mpfid,		/* 生成対象の固定長メモリプールのID番号 */
		const T_CMPF *pk_cmpf)	/* 固定長メモリプール生成情報を入れたパケットへのポインタ */
{
	ER ercd;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( mpfid < TMIN_MPFID || mpfid > KERNEL_TMAX_MPFID )
	{
		return E_ID;	/* 不正ID */
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	/* メモリプールが登録可能かどうかチェック */
#ifdef HOS_ERCHK_E_OBJ
	if ( kernel_mpfcb_ram_tbl[mpfid - TMIN_MPFID] != NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_OBJ;	/* 既に登録済み */
	}
#endif

	/* 固定長メモリプールの生成 */
	ercd = kernel_cre_mpf(mpfid, pk_cmpf);
	
	mknl_unl_sys();	/* システムのロック解除 */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
