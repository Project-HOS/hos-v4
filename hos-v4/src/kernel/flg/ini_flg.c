/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ���٥�ȥե饰                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2004 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"



/* ���٥�ȥե饰�ν���� */
void kernel_ini_flg(void)
{
	INT i;

	/* ���٥�ȥե饰�ν���� */
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
