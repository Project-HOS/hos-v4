/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    周期ハンドラ                                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_tim.h"



/* 周期ハンドラの動作開始 */
ER sta_cyc(
		ID cycid)	/* 動作開始対象の周期ハンドラのID番号 */
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

	cyccb_rom = cyccb_ram->cyccb_rom;
	
	/* 動作設定 */
	cyccb_ram->lefttim = cyccb_rom->cyctim;
	cyccb_ram->cycstat = TCYC_STA;
	
	mknl_unl_sys();		/* システムのロック解除 */

	return E_OK;	
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
