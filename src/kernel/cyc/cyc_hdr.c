/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル 周期ハンドラ                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_cyc.h"



/* 周期ハンドラのタイマハンドラ */
void kernel_cyc_hdr(
		T_KERNEL_TIM *timobj,	/* タイマオブジェクト */
		RELTIM       tic)		/* タイムティック */
{
	const T_KERNEL_CYCCB_ROM *cyccb_rom;
	T_KERNEL_CYCCB_RAM *cyccb_ram;
	
	/* upper cast */
	cyccb_ram = (T_KERNEL_CYCCB_RAM *)timobj;
	
	/* 周期タスクの実行 */
	if ( cyccb_ram->lefttim <= tic )
	{
		cyccb_rom = cyccb_ram->cyccb_rom;
				
		/* 次の値を設定 */
		cyccb_ram->lefttim += cyccb_rom->cyctim - tic;

		/* 周期ハンドラ呼び出し */
		mknl_unl_sys();							/* システムのロック解除 */		
		cyccb_rom->cychdr(cyccb_rom->exinf);	/* ハンドラ呼び出し */
		mknl_loc_sys();							/* システムのロック */
	}
	else
	{
		cyccb_ram->lefttim -= tic;
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
