/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル 固定長メモリプール                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"



/* 固定長メモリブロックの獲得(ポーリング) */
ER pget_mpf(
		ID mpfid,		/* メモリブロック獲得対象の固定長メモリプールのID番号 */
		VP *p_blk)		/* 獲得したメモリブロックの先頭番地 */
{
	T_KERNEL_MPFCB_RAM *mpfcb_ram;
	ER ercd;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( mpfid < KERNEL_TMIN_MPFID || mpfid > KERNEL_TMAX_MPFID )
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

	if ( mpfcb_ram->free != NULL )
	{
		/* 空きブロックがあれば割り当てる */
		*p_blk          = mpfcb_ram->free;
		mpfcb_ram->free = *(VP *)mpfcb_ram->free;	/* 次の空きエリアを設定 */
		ercd = E_OK;
	}
	else
	{
		/* 空きブロックが無ければタイムアウト */
		ercd = E_TMOUT;
	}

	mknl_unl_sys();		/* システムのロック解除 */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
