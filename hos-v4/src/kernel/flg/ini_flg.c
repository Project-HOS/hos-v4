/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル イベントフラグ                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2004 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"



/* イベントフラグの初期化 */
void kernel_ini_flg(void)
{
	INT i;

	/* イベントフラグの初期化 */
	for ( i = KERNEL_TMIN_FLGID; i <= KERNEL_TMAX_FLGID; i++ )
	{
		if ( KERNEL_FLGID_TO_FLGCB_RAM(i) != NULL )
		{
			KERNEL_FLGID_TO_FLGCB_RAM(i)->flgptn = KERNEL_FLGID_TO_FLGCB_RAM(i)->flgcb_rom->iflgptn;
		}
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2004 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
