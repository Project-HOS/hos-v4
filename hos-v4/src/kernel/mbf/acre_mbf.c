/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル メッセージバッファ                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"



/* メッセージバッファの生成(ID番号自動割付け) */
ER_ID acre_mbf(
		const T_CMBF *pk_cmbf)	/* メッセージバッファ生成情報を入れたパケットへのポインタ */
{
	ID mbfid;
	ER ercd;

	mknl_loc_sys();	/* システムのロック */

	/* 利用可能なIDの検索 */
	for ( mbfid = KERNEL_TMAX_MBFID; mbfid >= KERNEL_TMIN_MBFID; mbfid-- )
	{
		if ( kernel_mbfcb_ram_tbl[mbfid - KERNEL_TMIN_MBFID] == NULL )
		{
			break;
		}
	}
	
	/* ID番号不足チェック */
#ifdef HOS_ERCHK_E_NOID
	if ( mbfid < KERNEL_TMIN_MBFID )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOID;	/* ID番号不足 */
	}
#endif

	/* メッセージバッファの生成 */
	ercd = kernel_cre_mbf(mbfid, pk_cmbf);
	if ( ercd != E_OK )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return (ER_ID)ercd;
	}
	
	mknl_unl_sys();	/* システムのロック解除 */

	return (ER_ID)mbfid;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
