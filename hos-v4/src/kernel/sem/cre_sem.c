/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル セマフォ                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"



/* セマフォの生成 */
ER cre_sem(
		ID           semid,		/* 生成対象のセマフォのID番号 */
		const T_CSEM *pk_csem)	/* セマフォ生成情報を入れたパケットへのポインタ */
{
	ER ercd;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( semid < TMIN_SEMID || semid > TMAX_SEMID )
	{
		return E_ID;	/* 不正ID */
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	/* セマフォが登録可能かどうかチェック */
#ifdef HOS_ERCHK_E_OBJ
	if ( kernel_semcb_ram_tbl[semid - TMIN_SEMID] != NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_OBJ;	/* 既に登録済み */
	}
#endif

	/* セマフォの生成 */
	ercd = kernel_cre_sem(semid, pk_csem);
	
	mknl_unl_sys();	/* システムのロック解除 */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
