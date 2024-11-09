/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*   プロセッサ抽象化コンポーネント (SH用)  割り込みマスク管理              */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* グローバル変数定義 */
UW hospac_sh_imsk      = 0;		/* 割り込みマスク */
UW hospac_sh_imsk_base = 0;		/* 割り込みマスクベース値 */



/* 割り込みマスク指定 */
ER chg_imsk(IMSK imsk)
{
	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_PAR
	if ( imsk < 0 || imsk > 15 )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();		/* システムのロック */
	
	hospac_sh_imsk_base = (imsk << 4);
	if ( mknl_sns_ctx() || hospac_sh_imsk < hospac_sh_imsk_base )
	{
		hospac_sh_imsk = hospac_sh_imsk_base;
	}
	
	mknl_unl_sys();		/* システムのアンロック */

	return E_OK;
}


/* 割り込みマスクの参照 */
ER get_imsk(IMSK *p_imsk)
{
	*p_imsk = hospac_sh_imsk_base >> 4;
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
