/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル メールボックス                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbx.h"



/* メールボックスの生成 */
ER cre_mbx(
		ID           mbxid,		/* 生成対象のメールボックスのID番号 */
		const T_CMBX *pk_cmbx)	/* メールボックス生成情報を入れたパケットへのポインタ */
{
	ER ercd;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( mbxid < TMIN_MBXID || mbxid > TMAX_MBXID )
	{
		return E_ID;	/* 不正ID */
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	/* メールボックスが登録可能かどうかチェック */
#ifdef HOS_ERCHK_E_OBJ
	if ( kernel_mbxcb_ram_tbl[mbxid - TMIN_MBXID] != NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_OBJ;	/* 既に登録済み */
	}
#endif

	/* メールボックスの生成 */
	ercd = kernel_cre_mbx(mbxid, pk_cmbx);
	
	mknl_unl_sys();	/* システムのロック解除 */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
