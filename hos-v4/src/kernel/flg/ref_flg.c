/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル イベントフラグ                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"
#include "knl_sys.h"



/* イベントフラグの状態参照 */
ER ref_flg(					
		ID     flgid,		/* 状態参照対象のイベントフラグのID番号 */
		T_RFLG *pk_rflg)	/* イベントフラグ状態を返すパケットへのポインタ */
{
	T_KERNEL_FLGCB_RAM       *flgcb_ram;
	T_MKNL_TCB *mtcb;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( flgid < TMIN_FLGID || flgid > KERNEL_TMAX_FLGID )
	{
		return E_ID;	/* 不正ID番号 */
	}
#endif

	/* パラメータのチェック */
#ifdef HOS_ERCHK_E_PAR
	if ( pk_rflg == NULL )
	{
		return E_PAR;	/* パラメータエラー */
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	flgcb_ram = KERNEL_FLGID_TO_FLGCB_RAM(flgid);

	/* オブジェクトの存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( flgcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif

	/* イベントフラグの待ち行列の先頭のタスクのID番号取得 */
	mtcb = mknl_ref_qhd(&flgcb_ram->que);	/* 待ち行列先頭からタスク取り出し */
	if ( mtcb == NULL )
	{
		pk_rflg->wtskid = TSK_NONE;		/* 待ちタスクなし */
	}
	else
	{
		/* タスクIDを検索 */
		pk_rflg->wtskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}

	/* フラグビットパターンの取得 */
	pk_rflg->flgptn = flgcb_ram->flgptn;

	mknl_unl_sys();	/* システムのロック解除 */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
