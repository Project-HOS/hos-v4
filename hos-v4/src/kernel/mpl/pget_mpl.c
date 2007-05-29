/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル 可変長メモリプール                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpl.h"



/* 可変長メモリブロックの獲得(ポーリング) */
ER pget_mpl(
		ID mplid,		/* メモリブロック獲得対象の可変長メモリプールのID番号 */
		UINT blksz,		/* 獲得するメモリブロックのサイズ(バイト数) */
		VP *p_blk)		/* 獲得したメモリブロックの先頭番地 */
{
	T_KERNEL_MPLCB_RAM *mplcb_ram;
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
		/* 空きブロックが無ければタイムアウト */
		ercd = E_TMOUT;
	}

	mknl_unl_sys();		/* システムのロック解除 */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
