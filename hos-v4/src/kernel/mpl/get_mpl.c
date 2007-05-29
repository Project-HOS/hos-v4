/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル 可変長メモリプール                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpl.h"



/* 可変長メモリブロックの獲得 */
ER get_mpl(
		ID   mplid,		/* メモリブロック獲得対象の可変長メモリプールのID番号 */
		UINT blksz,		/* 獲得するメモリブロックのサイズ(バイト数) */
		VP   *p_blk)	/* 獲得したメモリブロックの先頭番地 */
{
	const T_KERNEL_MPLCB_ROM *mplcb_rom;
	T_KERNEL_MPLCB_RAM       *mplcb_ram;
	T_MKNL_TCB               *mtcb;
	T_KERNEL_MPLINF          mplinf;
	VP mem;
	ER ercd;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( mplid < KERNEL_TMIN_MPLID || mplid > KERNEL_TMAX_MPLID )
	{
		return E_ID;	/* ID不正 */
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	/* コンテキストチェック */
#ifdef HOS_ERCHK_E_CTX
	if ( mknl_sns_wai() )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_CTX;	/* コンテキスト不正 */
	}
#endif

	mplcb_ram = KERNEL_MPLID_TO_MPLCB_RAM(mplid);

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mplcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif

	/* メモリ確保にトライ */
	mem = kernel_alc_hep(&mplcb_ram->hep, blksz);

	if ( mem != NULL )
	{
		/* 割り当て成功 */
		*p_blk          = mem;
		ercd = E_OK;
	}
	else
	{
		/* 空きが無ければ待ちに入る */
		mplcb_rom = mplcb_ram->mplcb_rom;
		mtcb = mknl_get_run_tsk();
		mplinf.blksz = blksz;
		mplinf.p_blk = p_blk;
		mtcb->data = (VP_INT)&mplinf;
		mknl_wai_tsk(mtcb, TTW_MPL);
		mknl_add_que(&mplcb_ram->que, mtcb, mplcb_rom->mplatr);	/* 待ち行列に追加 */
		
		ercd = (ER)mknl_exe_dsp();		/* タスクディスパッチの実行 */
				
		mknl_exe_tex();		/* 例外処理の実行 */
	}
	
	mknl_unl_sys();		/* システムのロック解除 */
	
	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
