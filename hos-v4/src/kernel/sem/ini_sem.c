/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル セマフォ                                                */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"



/* セマフォの初期化 */
void kernel_ini_sem(void)
{
	INT i;

	/* セマフォコントロールブロックの初期化 */
	for ( i = 0; i < kernel_semcb_cnt; i++ )
	{
		if ( kernel_semcb_ram_tbl[i] != NULL )
		{
			kernel_semcb_ram_tbl[i]->semcnt = kernel_semcb_ram_tbl[i]->semcb_rom->isemcnt;
		}
	}
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
