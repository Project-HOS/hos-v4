/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� �����ϥ�ɥ�                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_cyc.h"



/* �����ϥ�ɥ�ν���� */
void kernel_ini_cyc(void)
{
	T_KERNEL_CYCCB_RAM *cyccb_ram;
	int i;
	
	/* ��Ū�������줿�����ϥ�ɥ������ */
	for ( i = KERNEL_TMIN_CYCID; i <= KERNEL_TMAX_CYCID; i++ )
	{
		cyccb_ram = KERNEL_CYCID_TO_CYCCB_RAM(i);
		
		if ( cyccb_ram != NULL )
		{
			/* �����ޥϥ�ɥ���Ͽ */
			cyccb_ram->timobj.timhdr = kernel_cyc_hdr;
			
			/* TA_STA °���Τ�Τ򳫻Ϥ��� */
			if ( cyccb_ram->cyccb_rom->cycatr & TA_STA )
			{
				/* �����ޥꥹ�Ȥ��ɲ� */
				cyccb_ram->lefttim = cyccb_ram->cyccb_rom->cyctim;
				kernel_add_tml((T_KERNEL_TIM *)cyccb_ram);
			}
		}
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
