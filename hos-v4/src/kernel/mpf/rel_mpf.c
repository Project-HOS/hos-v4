/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル 固定長メモリプール                                      */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"



/* 固定長メモリブロックの返却 */
ER rel_mpf(
		ID mpfid,		/* メモリブロック獲得対象の固定長メモリプールのID番号 */
		VP blk)			/* 返却するメモリブロックの先頭番地 */
{
	T_KERNEL_MPFCB_RAM *mpfcb_ram;
	T_MKNL_TCB *mtcb;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( mpfid < TMIN_MPFID || mpfid > TMAX_MPFID )
	{
		return E_ID;	/* ID不正 */
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

	mtcb = mknl_ref_qhd(&mpfcb_ram->que);	/* 待ち行列先頭からタスク取り出し */
	if ( mtcb != NULL )
	{
		/* 待ちタスクがあれば待ち解除 */
		mknl_rmv_que(mtcb);						/* メモリプールの待ち行列から削除 */
		mknl_rmv_tmout(mtcb);					/* タイムアウト待ち行列から削除 */
		mtcb->data = (VP_INT)blk;				/* ブロックの先頭番地を設定 */
		mknl_wup_tsk(mtcb, E_OK);				/* タスクの待ち解除 */
		
		mknl_exe_dsp();		/* タスクディスパッチの実行 */
		mknl_exe_tex();		/* 例外処理の実行 */
	}
	else
	{
		/* 待ちタスクが無ければメモリプールに返却 */
		*(VP *)blk      = mpfcb_ram->free;
		mpfcb_ram->free = blk;
	}

	mknl_unl_sys();		/* システムのロック解除 */

	return E_OK;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
