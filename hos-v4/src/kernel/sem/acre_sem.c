/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル セマフォ                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"



/* セマフォの生成(ID番号自動割付け) */
ER_ID acre_sem(
		const T_CSEM *pk_csem)	/* セマフォ生成情報を入れたパケットへのポインタ */
{
	ID semid;
	ER ercd;

	mknl_loc_sys();	/* システムのロック */

	/* 利用可能なIDの検索 */
	for ( semid = KERNEL_TMAX_SEMID; semid >= TMIN_SEMID; semid-- )
	{
		if ( kernel_semcb_ram_tbl[semid - TMIN_SEMID] == NULL )
		{
			break;
		}
	}
	
	/* ID番号不足チェック */
#ifdef HOS_ERCHK_E_NOID
	if ( semid < TMIN_SEMID )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOID;	/* ID番号不足 */
	}
#endif

	/* セマフォの生成 */
	ercd = kernel_cre_sem(semid, pk_csem);
	if ( ercd != E_OK )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return (ER_ID)ercd;
	}
	
	mknl_unl_sys();	/* システムのロック解除 */

	return (ER_ID)semid;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
