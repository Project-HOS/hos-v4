/* ------------------------------------------------------------------------ */
/*  HOS-V4 サンプル                                                         */
/*   プロセッサ抽象化コンポーネント (ARM用)                                 */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* グローバル変数定義 */
UW hospac_arm_imask = ARM_IMASK_USR_MODE;	/* 割り込みマスク */



/* 割り込みマスク指定 */
ER chg_imask(IMASK imask)
{
	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_PAR
	if ( (imask & ~(ARM_IMASK_FIQ | ARM_IMASK_IRQ)) != 0 )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();		/* システムのロック */

	hospac_arm_imask = (hospac_arm_imask | ARM_IMASK_USR_MODE);

	mknl_unl_sys();		/* システムのアンロック */

	return E_OK;
}


/* 割り込みマスクの参照 */
ER get_imask(IMASK *p_imask)
{
	*p_imask = (hospac_arm_imask & (ARM_IMASK_FIQ | ARM_IMASK_IRQ));
	
	return E_OK;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
