/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� �����ƥ���ִ���                                        */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* �¹Ծ��֥�����ID�λ��� */
ER get_tid(ID *p_tskid)
{
	T_KERNEL_TCB_RAM *tcb_ram;
	T_MKNL_TCB *mtcb;
	ID tskid;

	/* �¹���˼�������ID���Ѳ����뤳�Ȥ�̵���٥�å��ϹԤ�ʤ� */

	mtcb = mknl_get_run_tsk();	/* �¹���Υ���������� */
	*p_tskid = TSK_NONE;
	if ( mtcb != NULL )
	{
		/* �¹���Υ���������� */
		tcb_ram = KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb);
		
		/* ������ID�򸡺� */
		for ( tskid = TMIN_TSKID; tskid <= kernel_tcb_cnt; tskid++ )
		{
			if ( tcb_ram == KERNEL_TSKID_TO_TCB_RAM(tskid) )
			{
				*p_tskid = tskid;
				break;
			}
		}
	}

	return E_OK;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
