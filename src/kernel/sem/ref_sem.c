/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル セマフォ                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"
#include "knl_sys.h"



/* セマフォの状態参照 */
ER ref_sem(
		ID     semid,		/* 状態参照対象のセマフォのID番号 */
		T_RSEM *pk_rsem)	/* セマフォ状態を返すパケットへのポインタ */
{
	T_KERNEL_SEMCB_RAM *semcb_ram;
	T_MKNL_TCB *mtcb;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( semid < KERNEL_TMIN_SEMID || semid > KERNEL_TMAX_SEMID )
	{
		return E_ID;
	}
#endif

	/* パラメータのチェック */
#ifdef HOS_ERCHK_E_PAR
	if ( pk_rsem == NULL )
	{
		return E_PAR;	/* パラメータエラー */
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	semcb_ram = KERNEL_SEMID_TO_SEMCB_RAM(semid);

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( semcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif

	/* セマフォの待ち行列の先頭のタスクのID番号取得 */
	mtcb = mknl_ref_qhd(&semcb_ram->que);	/* 待ち行列先頭からタスク取り出し */
	if ( mtcb == NULL )
	{
		pk_rsem->wtskid = TSK_NONE;		/* 待ちタスクなし */
	}
	else
	{
		/* タスクIDを検索 */
		pk_rsem->wtskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}
	
	/* セマフォの現在の資源数取得 */
	pk_rsem->semcnt = semcb_ram->semcnt;

	mknl_unl_sys();	/* システムのロック解除 */

	return E_OK;	/* 成功 */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
