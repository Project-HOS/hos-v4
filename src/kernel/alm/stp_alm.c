/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル アラームハンドラ                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_alm.h"



/* アラームハンドラの動作停止 */
ER stp_alm(
		ID almid)	/* 動作停止対象のアラームハンドラのID番号 */
{
	T_KERNEL_ALMCB_RAM *almcb_ram;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( almid < KERNEL_TMIN_ALMID || almid > KERNEL_TMAX_ALMID )
	{
		return E_ID;
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	almcb_ram = KERNEL_ALMID_TO_ALMCB_RAM(almid);

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( almcb_ram == NULL )
	{
		mknl_unl_sys();		/* システムのロック解除 */
		return E_NOEXS;
	}
#endif
	
	/* タイマリストから外す */
	kernel_rmv_tml((T_KERNEL_TIM *)almcb_ram);
	
	mknl_unl_sys();		/* システムのロック解除 */

	return E_OK;	
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
