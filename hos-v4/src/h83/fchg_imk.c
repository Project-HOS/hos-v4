/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*   プロセッサ抽象化コンポーネント (日立 H8/300H 用)                       */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* 現在の割込みマスク値の強制変更 */
ER fchg_imsk(
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
	
	/* 強制的に現在値を変更 */
	kernel_h83_imsk = imsk;		/* 割り込みマスクの設定 */
	
	mknl_unl_sys();		/* システムのアンロック */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
