/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル イベントフラグ                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"



/* イベントフラグの生成 */
ER cre_flg(
		ID           flgid,		/* 生成対象のイベントフラグのID番号 */
		const T_CFLG *pk_cflg)	/* イベントフラグ生成情報を入れたパケットへのポインタ */
{
	ER ercd;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( flgid < KERNEL_TMIN_FLGID || flgid > KERNEL_TMAX_FLGID )
	{
		return E_ID;	/* 不正ID */
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	/* イベントフラグが登録可能かどうかチェック */
#ifdef HOS_ERCHK_E_OBJ
	if ( KERNEL_FLGID_TO_FLGCB_RAM(flgid) != NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_OBJ;	/* 既に登録済み */
	}
#endif

	/* イベントフラグの生成 */
	ercd = kernel_cre_flg(flgid, pk_cflg);
	
	mknl_unl_sys();	/* システムのロック解除 */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
