/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ���ޥե�                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"



/* ���ޥե��ν���� */
void kernel_ini_sem(void)
{
	INT i;

	/* ���ޥե�����ȥ���֥�å��ν���� */
	for ( i = 0; i < kernel_semcb_cnt; i++ )
	{
		if ( kernel_semcb_ram_tbl[i] != NULL )
		{
			kernel_semcb_ram_tbl[i]->semcnt = kernel_semcb_ram_tbl[i]->semcb_rom->isemcnt;
		}
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
