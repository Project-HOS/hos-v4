/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ���ޥե�                                                */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* ���ޥե��ν���� */
void kernel_ini_sem(void)
{
	INT i;

	/* ���ޥե�����ȥ���֥�å��ν���� */
	for ( i = 0; i < kernel_semcb_cnt; i++ )
	{
		if ( kernel_semcb_ram_tbl[i] != NULL )
		{
			kernel_semcb_ram_tbl[i]->semcnt = kernel_semcb_ram_tbl[i]->semcbrom->isemcnt;
		}
	}
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
