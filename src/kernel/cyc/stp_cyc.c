/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル アラームハンドラ                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_cyc.h"



/* アラームハンドラの動作停止 */
ER stp_cyc(
		ID cycid)	/* 動作停止対象のアラームハンドラのID番号 */
{
	T_KERNEL_CYCCB_RAM *cyccb_ram;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( cycid < KERNEL_TMIN_CYCID || cycid > KERNEL_TMAX_CYCID )
	{
		return E_ID;
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	cyccb_ram = KERNEL_CYCID_TO_CYCCB_RAM(cycid);

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( cyccb_ram == NULL )
	{
		mknl_unl_sys();		/* システムのロック解除 */
		return E_NOEXS;
	}
#endif
	
	/* タイマリストから外す */
	kernel_rmv_tml((T_KERNEL_TIM *)cyccb_ram);
	
	mknl_unl_sys();		/* システムのロック解除 */

	return E_OK;	
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
