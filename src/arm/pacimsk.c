/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*   プロセッサ抽象化コンポーネント (ARM用)                                 */
/*   割り込みマスク管理                                                     */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* グローバル変数定義 */
UW hospac_arm_imsk  = ARM_IMSK_USR_MODE;		/* 割り込みマスク */
UW hospac_arm_bimsk = ARM_IMSK_USR_MODE;		/* ベース割り込みマスク */


/* 割り込みマスク指定 */
ER chg_imsk(IMSK imsk)
{
	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_PAR
	if ( (imsk & ~(ARM_IMSK_FIQ | ARM_IMSK_IRQ)) != 0 )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();		/* システムのロック */

	hospac_arm_bimsk = (imsk | ARM_IMSK_USR_MODE);
	
	if ( !mknl_sns_ctx() )
	{
		hospac_arm_imsk = hospac_arm_bimsk;
	}
	else
	{
		hospac_arm_imsk |= hospac_arm_bimsk;
	}

	mknl_unl_sys();		/* システムのアンロック */

	return E_OK;
}


/* 割り込みマスクの参照 */
ER get_imsk(IMSK *p_imsk)
{
	*p_imsk = (hospac_arm_bimsk & (ARM_IMSK_FIQ | ARM_IMSK_IRQ));
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
