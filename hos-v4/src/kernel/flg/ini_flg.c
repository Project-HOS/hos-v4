/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル イベントフラグ                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"



/* イベントフラグの初期化 */
void kernel_ini_flg(void)
{
	INT i;

	/* イベントフラグの初期化 */
	for ( i = 0; i < kernel_flgcb_cnt; i++ )
	{
		kernel_flgcb_ram_tbl[i]->flgptn = kernel_flgcb_ram_tbl[i]->flgcb_rom->iflgptn;
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
