/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ϥ�ɥ�                                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tim.h"



/* �����ϥ�ɥ�ν���� */
void kernel_ini_cyc(void)
{
	T_KERNEL_CYCCB_RAM *cyccb_ram;
	int i;
	
	/* TA_STA °���Τ�Τ򳫻Ϥ��� */
	for ( i = 0; i < kernel_cyccb_cnt; i++ )
	{
		cyccb_ram = kernel_cyccb_ram_tbl[i];
		if ( cyccb_ram != NULL && (cyccb_ram->cyccb_rom->cycatr & TA_STA) )
		{
			cyccb_ram->lefttim = cyccb_ram->cyccb_rom->cyctim;
			cyccb_ram->cycstat = TCYC_STA;
		}
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
