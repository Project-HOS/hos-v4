/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル 固定長メモリプール                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"



/* 固定長メモリブロックの獲得(タイムアウトあり) */
ER tget_mpf(
		ID  mpfid,		/* メモリブロック獲得対象の固定長メモリプールのID番号 */
		VP  *p_blk,		/* 獲得したメモリブロックの先頭番地 */
		TMO tmout)		/* タイムアウト指定 */
{
	const T_KERNEL_MPFCB_ROM *mpfcb_rom;
	T_KERNEL_MPFCB_RAM       *mpfcb_ram;
	T_MKNL_TCB *mtcb;
	ER ercd;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( mpfid < KERNEL_TMIN_MPFID || mpfid > KERNEL_TMAX_MPFID )
	{
		return E_ID;	/* ID不正 */
	}
#endif

	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_PAR 
	if ( tmout != TMO_FEVR && tmout < 0 )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	/* コンテキストチェック */
#ifdef HOS_ERCHK_E_CTX
	if ( tmout != TMO_POL &&  mknl_sns_wai() )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_CTX;	/* コンテキスト不正 */
	}
#endif

	mpfcb_ram = KERNEL_MPFID_TO_MPFCB_RAM(mpfid);

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mpfcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif

	if ( mpfcb_ram->free != NULL )
	{
		/* 空きブロックがあれば割り当てる */
		*p_blk          = mpfcb_ram->free;
		mpfcb_ram->free = *(VP *)mpfcb_ram->free;	/* 次の空きエリアを設定 */
		ercd = E_OK;
	}
	else
	{
		if ( tmout == TMO_POL )
		{
			/* ポーリングなら即時タイムアウト */
			ercd = E_TMOUT;
		}
		else
		{
			/* 空きブロックが無ければ待ちに入る */
			mpfcb_rom = mpfcb_ram->mpfcb_rom;
			mtcb = mknl_get_run_tsk();
			mknl_wai_tsk(mtcb, TTW_MPF);
			mknl_add_que(&mpfcb_ram->que, mtcb, mpfcb_rom->mpfatr);	/* 待ち行列に追加 */
			
			/* 無限待ちでなければタイムアウト設定 */
			if ( tmout != TMO_FEVR )
			{
				mknl_add_tmout(mtcb, (RELTIM)tmout);	/* タイムアウトキューに追加 */
			}
			
			ercd = (ER)mknl_exe_dsp();	/* タスクディスパッチの実行 */
			
			if ( ercd == E_OK )
			{
				*p_blk = (VP)mtcb->data;	/* 獲得ブロック先頭番地格納 */
			}
			
			mknl_exe_tex();		/* 例外処理の実行 */
		}
	}
	
	mknl_unl_sys();		/* システムのロック解除 */
	
	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
