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
	
	/* TA_STA °���Τ�Τ򳫻Ϥ��� */
	for ( i = 0; i < kernel_cyccb_cnt; i++ )
	{
		cyccb_ram = kernel_cyccb_ram_tbl[i];
		
		if ( cyccb_ram != NULL )
		{
			/* �����ޥϥ�ɥ���Ͽ */
			cyccb_ram->timobj.timhdr = kernel_cyc_hdr;
			
			/* ��������������� */
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
