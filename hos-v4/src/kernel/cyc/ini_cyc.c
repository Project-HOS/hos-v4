/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル 周期ハンドラ                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_cyc.h"



/* 周期ハンドラの初期化 */
void kernel_ini_cyc(void)
{
	T_KERNEL_CYCCB_RAM *cyccb_ram;
	int i;
	
	/* TA_STA 属性のものを開始する */
	for ( i = 0; i < kernel_cyccb_cnt; i++ )
	{
		cyccb_ram = kernel_cyccb_ram_tbl[i];
		
		if ( cyccb_ram != NULL )
		{
			/* タイマハンドラ登録 */
			cyccb_ram->timobj.timhdr = kernel_cyc_hdr;
			
			/* 初期スタート設定 */
			if ( cyccb_ram->cyccb_rom->cycatr & TA_STA )
			{
				/* タイマリストに追加 */
				cyccb_ram->lefttim = cyccb_ram->cyccb_rom->cyctim;
				kernel_add_tml((T_KERNEL_TIM *)cyccb_ram);
			}
		}
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
