/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル データキュー                                            */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_dtq.h"



/* データキューの生成(ID番号自動割付け) */
ER_ID acre_dtq(
		const T_CDTQ *pk_cdtq)	/* データキュー生成情報を入れたパケットへのポインタ */
{
	ID dtqid;
	ER ercd;

	mknl_loc_sys();	/* システムのロック */

	/* 利用可能なIDの検索 */
	for ( dtqid = TMAX_DTQID; dtqid >= TMIN_DTQID; dtqid-- )
	{
		if ( kernel_dtqcb_ram_tbl[dtqid - TMIN_DTQID] == NULL )
		{
			break;
		}
	}
	
	/* ID番号不足チェック */
#ifdef HOS_ERCHK_E_NOID
	if ( dtqid < TMIN_DTQID )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOID;	/* ID番号不足 */
	}
#endif

	/* データキューの生成 */
	ercd = kernel_cre_dtq(dtqid, pk_cdtq);
	if ( ercd != E_OK )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return (ER_ID)ercd;
	}
	
	mknl_unl_sys();	/* システムのロック解除 */

	return (ER_ID)dtqid;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
