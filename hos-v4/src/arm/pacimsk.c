/* ------------------------------------------------------------------------ */
/*  HOS-V4 サンプル                                                         */
/*   プロセッサ抽象化コンポーネント (ARM用)                                 */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* グローバル変数定義 */
UW hospac_arm_imsk = ARM_IMASK_USR_MODE;	/* 割り込みマスク */



/* 割り込みマスク指定 */
ER chg_imsk(IMASK imsk)
{
	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_PAR
	if ( (imsk & ~(ARM_IMASK_FIQ | ARM_IMASK_IRQ)) != 0 )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();		/* システムのロック */

	hospac_arm_imsk = (hospac_arm_imsk | ARM_IMASK_USR_MODE);

	mknl_unl_sys();		/* システムのアンロック */

	return E_OK;
}


/* 割り込みマスクの参照 */
ER get_imsk(IMASK *p_imsk)
{
	*p_imsk = (hospac_arm_imsk & (ARM_IMASK_FIQ | ARM_IMASK_IRQ));
	
	return E_OK;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
