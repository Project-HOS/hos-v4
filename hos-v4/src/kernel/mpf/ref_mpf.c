/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル 固定長メモリプール                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"
#include "knl_sys.h"



/* 固定長メモリブロックの状態参照 */
ER ref_mpf(
		ID     mpfid,		/* 状態取得対象の固定長メモリプールのID番号 */
		T_RMPF *pk_rmpf)	/* 固定長メモリプール状態を返すパケットへのポインタ */
{
	T_KERNEL_MPFCB_RAM *mpfcb_ram;
	T_MKNL_TCB *mtcb;
	VP   blk;
	UINT blkcnt;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( mpfid < TMIN_MPFID || mpfid > KERNEL_TMAX_MPFID )
	{
		return E_ID;	/* ID不正 */
	}
#endif

	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_PAR 
	if ( pk_rmpf == NULL )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	mpfcb_ram = KERNEL_MPFID_TO_MPFCB_RAM(mpfid);

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mpfcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif
	
	/* 固定長メモリブロックの待ち行列の先頭のタスクのID番号取得 */
	mtcb = mknl_ref_qhd(&mpfcb_ram->que);	/* 待ち行列先頭からタスク取り出し */
	if ( mtcb == NULL )
	{
		pk_rmpf->wtskid = TSK_NONE;		/* 待ちタスクなし */
	}
	else
	{
		/* タスクIDを検索 */
		pk_rmpf->wtskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}

	/* 空きブロックのカウント */
	blkcnt = 0;
	blk    = mpfcb_ram->free;
	while ( blk != NULL )
	{
		blk = *(VP *)blk;
		blkcnt++;
	}

	pk_rmpf->fblkcnt = blkcnt;
	
	mknl_unl_sys();		/* システムのロック解除 */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
