/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル データキュー                                            */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_dtq.h"



/* データキューの生成 */
ER cre_dtq(
		ID           dtqid,		/* 生成対象のデータキューのID番号 */
		const T_CDTQ *pk_cdtq)	/* データキュー生成情報を入れたパケットへのポインタ */
{
	ER ercd;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( dtqid < TMIN_DTQID || dtqid > TMAX_DTQID )
	{
		return E_ID;	/* 不正ID */
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	/* IDが使用可能かどうかチェック */
#ifdef HOS_ERCHK_E_ID
	if ( kernel_dtqcb_ram_tbl[dtqid - TMIN_DTQID] == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_ID;	/* 不正ID */
	}
#endif

	/* データキューの生成 */
	ercd = kernel_cre_dtq(dtqid, pk_cdtq);
	
	mknl_unl_sys();	/* システムのロック解除 */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
