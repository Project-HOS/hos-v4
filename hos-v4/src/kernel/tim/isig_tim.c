/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ƥ���ִ���                                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tim.h"



/* ������ƥ��å��ζ��� */
ER isig_tim(void)
{
	RELTIM tic;
	UW     prev_tim;
    INT    i;

	/* �û����륿����ƥ��å��򻻽� */
	/* �㤨�� 10/3 ms �����ʤ� 3, 3, 4, 3, 3, 4, ... �ȥ�����Ȥ��Ƥ��� */
	kernel_tic_cnt--;
	if ( kernel_tic_cnt < kernel_tic_mod )
	{
		tic = kernel_tic_div + 1;	/* ����ڤ�ʤ�ʬ������ */
	}
	else
	{
		tic = kernel_tic_div;
	}
	if ( kernel_tic_cnt == 0 )
	{
		kernel_tic_cnt = kernel_tic_deno;
	}

	mknl_loc_sys();		/* �����ƥ�Υ�å� */

	/* �����ƥॿ����˲û� */
	prev_tim = kernel_systim.ltime;
	kernel_systim.ltime += tic;
	if ( kernel_systim.ltime < prev_tim )	/* ��夬�꤬����ʤ� */
	{
		kernel_systim.utime++;
	}


	/* �����ॢ�����Ԥ�����Υ��������� */
	mknl_tic_tmout(tic);	/* �����ॢ���ȥ��塼�˥�����ƥ��å��򶡵� */


	/* �����������μ¹� */
	for ( i = 0; i < kernel_cyccb_cnt; i++ )
	{
		const T_KERNEL_CYCCB_ROM *cyccb_rom;
		T_KERNEL_CYCCB_RAM       *cyccb_ram;

		cyccb_ram = kernel_cyccb_ram_tbl[i];

		if ( cyccb_ram->cycstat != TCYC_STP )	/* ��ߤǤϤʤ��ʤ� */
		{
			if ( cyccb_ram->lefttim <= tic )
			{
				cyccb_rom = cyccb_ram->cyccb_rom;
				
				/* �����ͤ����� */
				cyccb_ram->lefttim += cyccb_rom->cyctim - tic;

				/* �����ϥ�ɥ�ƤӽФ� */
				cyccb_rom = cyccb_ram->cyccb_rom;
				cyccb_rom->cychdr(cyccb_rom->exinf);				
			}
			else
			{
				cyccb_ram->lefttim -= tic;
			}
			
		}
	}

	mknl_unl_sys();		/* �����ƥ�Υ�å���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
