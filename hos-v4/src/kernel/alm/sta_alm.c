/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル アラームハンドラ                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_alm.h"



/* アラームハンドラの動作開始 */
ER sta_alm(
		ID     almid,	/* 動作開始対象のアラームハンドラのID番号 */
		RELTIM almtim)	/* アラームハンドラの起動時刻(相対時間) */
{
	const T_KERNEL_ALMCB_ROM *almcb_rom;
	T_KERNEL_ALMCB_RAM *almcb_ram;
	
	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( almid < TMIN_ALMID || almid > TMAX_ALMID )
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
	
	almcb_rom = almcb_ram->almcb_rom;
	
	/* タイマカウンタ設定 */
	almcb_ram->lefttim = almtim;
	
	/* タイマリストに登録 */
	kernel_add_tml((T_KERNEL_TIM *)almcb_ram);
	
	mknl_unl_sys();		/* システムのロック解除 */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
