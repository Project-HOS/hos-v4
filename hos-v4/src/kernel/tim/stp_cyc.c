/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    周期ハンドラ                                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tim.h"



/* 周期ハンドラの動作停止 */
ER stp_cyc(
		ID cycid)	/* 動作停止対象の周期ハンドラのID番号 */
{
	const T_KERNEL_CYCCB_ROM *cyccb_rom;
	T_KERNEL_CYCCB_RAM *cyccb_ram;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( cycid < TMIN_CYCID || cycid > TMAX_CYCID )
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

	/* コンテキストチェック */
#ifdef HOS_ERCHK_E_CTX
	if ( mknl_sns_wai() )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_CTX;	/* コンテキスト不正 */
	}
#endif
	
	cyccb_rom = cyccb_ram->cyccb_rom;
	
	/* 動作設定 */
	cyccb_ram->cycstat = TCYC_STP;
	
	mknl_unl_sys();		/* システムのロック解除 */

	return E_OK;	
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
