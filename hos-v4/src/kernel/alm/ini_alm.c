/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ���顼��ϥ�ɥ�                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_alm.h"



/* ���顼��ϥ�ɥ�ν���� */
void kernel_ini_alm(void)
{
	T_KERNEL_ALMCB_RAM *almcb_ram;
	int i;
	
	/* ��Ū�������줿���顼��ϥ�ɥ������ */
	for ( i = KERNEL_TMIN_ALMID; i <= KERNEL_TMAX_ALMID; i++ )
	{
		almcb_ram = KERNEL_ALMID_TO_ALMCB_RAM(i);
		
		if ( almcb_ram != NULL )
		{
			/* �����ޥϥ�ɥ���Ͽ */
			almcb_ram->timobj.timhdr = kernel_alm_hdr;
		}
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
