/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*   プロセッサ抽象化コンポーネント (日立 H8/300H 用)                       */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* 割り込みマスクのベース値の変更 */
ER chg_imsk(
		IMSK imsk)		/* 設定するマスク値 */
{
	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_PAR
	if ( (imsk & ~(H83_IMSK_I_BIT | H83_IMSK_UI_BIT)) != 0 )
	{
		return E_PAR;
	}
#endif
	
	mknl_loc_sys();		/* システムのロック */
	
	/* ベースマスク値の変更 */
	kernel_h83_ibmsk = imsk;
	
	if ( mknl_sns_ctx() )
	{
		/* 割り込みコンテキストならマスクレベルUPのみ反映 */
		kernel_h83_imsk |= imsk;
	}
	else
	{
		/* タスクコンテキストなら現在のマスク値も即時変更 */
		kernel_h83_imsk = imsk;
	}
	
	mknl_unl_sys();		/* システムのアンロック */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
