/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル イベントフラグ                                                */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"



/* イベントフラグの生成(ID番号自動割付け) */
ER_ID acre_flg(
		const T_CFLG *pk_cflg)	/* イベントフラグ生成情報を入れたパケットへのポインタ */
{
	ID flgid;
	ER ercd;

	mknl_loc_sys();	/* システムのロック */

	/* 利用可能なIDの検索 */
	for ( flgid = TMAX_FLGID; flgid >= TMIN_FLGID; flgid-- )
	{
		if ( kernel_flgcb_ram_tbl[flgid - TMIN_FLGID] == NULL )
		{
			break;
		}
	}
	
	/* ID番号不足チェック */
#ifdef HOS_ERCHK_E_NOID
	if ( flgid < TMIN_FLGID )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOID;	/* ID番号不足 */
	}
#endif

	/* イベントフラグの生成 */
	ercd = kernel_cre_flg(flgid, pk_cflg);
	if ( ercd != E_OK )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return (ER_ID)ercd;
	}
	
	mknl_unl_sys();	/* システムのロック解除 */

	return (ER_ID)flgid;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
