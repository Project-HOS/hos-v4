/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� �����ƥ���ִ���                                        */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* ������ID�μ��� */
ID kernel_get_tid(T_KERNEL_TCB_RAM *tcb_ram)
{
	ID tskid;
	
	/* ������ID�򸡺� */
	for ( tskid = TMAX_TSKID; tskid >= TMIN_TSKID; tskid-- )
	{
		if ( tcb_ram == KERNEL_TSKID_TO_TCB_RAM(tskid) )
		{
			break;
		}
	}
	
	return tskid;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
