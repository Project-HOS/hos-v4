/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� �����ƥ���ִ���                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sys.h"



/* ������ID�μ��� */
ID kernel_get_tid(T_KERNEL_TCB_RAM *tcb_ram)
{
	ID tskid;
	
	/* ������ID�򸡺� */
	for ( tskid = KERNEL_TMAX_TSKID; tskid >= TMIN_TSKID; tskid-- )
	{
		if ( tcb_ram == KERNEL_TSKID_TO_TCB_RAM(tskid) )
		{
			break;
		}
	}
	
	return tskid;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
