/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ���٥�ȥե饰                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"



/* ���٥�ȥե饰�ν���� */
void kernel_ini_flg(void)
{
	INT i;

	/* ���٥�ȥե饰�ν���� */
	for ( i = 0; i < kernel_flgcb_cnt; i++ )
	{
		kernel_flgcb_ram_tbl[i]->flgptn = kernel_flgcb_ram_tbl[i]->flgcb_rom->iflgptn;
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
