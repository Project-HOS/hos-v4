/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル 可変長メモリプール                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpl.h"



/* 可変長メモリプールの生成(ID番号自動割付け) */
ER_ID acre_mpl(
		const T_CMPL *pk_cmpl)	/* 可変長メモリプール生成情報を入れたパケットへのポインタ */
{
	ID mplid;
	ER ercd;

	mknl_loc_sys();	/* システムのロック */

	/* 利用可能なIDの検索 */
	for ( mplid = KERNEL_TMAX_MPLID; mplid >= KERNEL_TMIN_MPLID; mplid-- )
	{
		if ( KERNEL_MPLID_TO_MPLCB_RAM(mplid) == NULL )
		{
			break;
		}
	}
	
	/* ID番号不足チェック */
#ifdef HOS_ERCHK_E_NOID
	if ( mplid < KERNEL_TMIN_MPLID )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOID;	/* ID番号不足 */
	}
#endif

	/* 可変長メモリプールの生成 */
	ercd = kernel_cre_mpl(mplid, pk_cmpl);
	if ( ercd != E_OK )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return (ER_ID)ercd;
	}
	
	mknl_unl_sys();	/* システムのロック解除 */

	return (ER_ID)mplid;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
