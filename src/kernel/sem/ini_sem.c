/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル セマフォ                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"



/* セマフォの初期化 */
void kernel_ini_sem(void)
{
	INT i;

	/* セマフォコントロールブロックの初期化 */
	for ( i = KERNEL_TMIN_SEMID; i <= KERNEL_TMAX_SEMID; i++ )
	{
		if ( KERNEL_SEMID_TO_SEMCB_RAM(i) != NULL )
		{
			KERNEL_SEMID_TO_SEMCB_RAM(i)->semcnt = KERNEL_SEMID_TO_SEMCB_RAM(i)->semcb_rom->isemcnt;
		}
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
