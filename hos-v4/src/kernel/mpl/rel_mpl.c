/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル 可変長メモリプール                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpl.h"



/* 可変長メモリブロックの返却 */
ER rel_mpl(
		ID mplid,		/* メモリブロック獲得対象の可変長メモリプールのID番号 */
		VP blk)			/* 返却するメモリブロックの先頭番地 */
{
	T_KERNEL_MPLCB_RAM *mplcb_ram;
	T_MKNL_TCB         *mtcb;
	T_KERNEL_MPLINF    *mplinf;
	VP                 mem;
	BOOL               wup = FALSE;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( mplid < KERNEL_TMIN_MPLID || mplid > KERNEL_TMAX_MPLID )
	{
		return E_ID;	/* ID不正 */
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	mplcb_ram = KERNEL_MPLID_TO_MPLCB_RAM(mplid);

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mplcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif

	/* メモリプールに返却 */
	kernel_fre_hep(&mplcb_ram->hep, blk);

	/* 待ちタスクの起床 */
	for ( ; ; )
	{
		/* 待ち行列先頭からタスク取り出し */
		mtcb = mknl_ref_qhd(&mplcb_ram->que);
		if ( mtcb == NULL )
		{
			break;
		}
		
		/* メモリ確保にトライ */
		mplinf = (T_KERNEL_MPLINF *)mtcb->data;
		mem = kernel_alc_hep(&mplcb_ram->hep, mplinf->blksz);
		if ( mem == NULL )
		{
			break;
		}

		/* 待ちタスクがあれば待ち解除 */
		*mplinf->p_blk = mem;
		mknl_rmv_que(mtcb);					/* メモリプールの待ち行列から削除 */
		mknl_rmv_tmout(mtcb);				/* タイムアウト待ち行列から削除 */
		mknl_wup_tsk(mtcb, E_OK);			/* タスクの待ち解除 */
		
		wup = TRUE;
	}
	
	if ( wup )
	{
		mknl_exe_dsp();		/* タスクディスパッチの実行 */
		mknl_exe_tex();		/* 例外処理の実行 */
	}

	mknl_unl_sys();		/* システムのロック解除 */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
