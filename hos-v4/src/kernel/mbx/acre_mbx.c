/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル メールボックス                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbx.h"



/* メールボックスの生成(ID番号自動割付け) */
ER_ID acre_mbx(
		const T_CMBX *pk_cmbx)	/* メールボックス生成情報を入れたパケットへのポインタ */
{
	ID mbxid;
	ER ercd;

	mknl_loc_sys();	/* システムのロック */

	/* 利用可能なIDの検索 */
	for ( mbxid = KERNEL_TMAX_MBXID; mbxid >= TMIN_MBXID; mbxid-- )
	{
		if ( kernel_mbxcb_ram_tbl[mbxid - TMIN_MBXID] == NULL )
		{
			break;
		}
	}
	
	/* ID番号不足チェック */
#ifdef HOS_ERCHK_E_NOID
	if ( mbxid < TMIN_MBXID )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOID;	/* ID番号不足 */
	}
#endif

	/* メールボックスの生成 */
	ercd = kernel_cre_mbx(mbxid, pk_cmbx);
	if ( ercd != E_OK )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return (ER_ID)ercd;
	}
	
	mknl_unl_sys();	/* システムのロック解除 */

	return (ER_ID)mbxid;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
