/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル メッセージバッファ                                      */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"



/* メッセージバッファの生成 */
ER cre_mbf(
		ID           mbfid,		/* 生成対象のメッセージバッファのID番号 */
		const T_CMBF *pk_cmbf)	/* メッセージバッファ生成情報を入れたパケットへのポインタ */
{
	ER ercd;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( mbfid < TMIN_MBFID || mbfid > TMAX_MBFID )
	{
		return E_ID;	/* 不正ID */
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	/* IDが使用可能かどうかチェック */
#ifdef HOS_ERCHK_E_ID
	if ( kernel_mbfcb_ram_tbl[mbfid - TMIN_MBFID] == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_ID;	/* 不正ID */
	}
#endif

	/* メッセージバッファの生成 */
	ercd = kernel_cre_mbf(mbfid, pk_cmbf);
	
	mknl_unl_sys();	/* システムのロック解除 */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
