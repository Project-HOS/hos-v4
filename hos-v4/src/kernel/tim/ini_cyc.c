/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �����ϥ�ɥ�                                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
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
		if ( cyccb_ram != NULL && (cyccb_ram->cyccbrom->cycatr & TA_STA) )
		{
			sta_cyc(TMIN_CYCID + i);
		}
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
