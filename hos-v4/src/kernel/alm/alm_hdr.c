/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル アラームハンドラ                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_alm.h"



/* アラームハンドラのタイマハンドラ */
void kernel_alm_hdr(
		T_KERNEL_TIM *timobj,	/* タイマオブジェクト */
		RELTIM       tic)		/* タイムティック */
{
	const T_KERNEL_ALMCB_ROM *almcb_rom;
	T_KERNEL_ALMCB_RAM *almcb_ram;
	
	/* upper cast */
	almcb_ram = (T_KERNEL_ALMCB_RAM *)timobj;
	
	/* アラームタスクの実行 */
	if ( almcb_ram->lefttim <= tic )
	{
		almcb_rom = almcb_ram->almcb_rom;
				
		/* アラームハンドラをタイマリストから外す */
		kernel_rmv_tml((T_KERNEL_TIM *)almcb_ram);

		/* アラームハンドラ呼び出し */
		mknl_unl_sys();							/* システムのロック解除 */		
		almcb_rom->almhdr(almcb_rom->exinf);	/* ハンドラ呼び出し */
		mknl_loc_sys();							/* システムのロック */
	}
	else
	{
		almcb_ram->lefttim -= tic;		/* 残り時間を減算 */
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
