/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� �������㳰������ǽ                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"
#include "knl_sys.h"



/* �������㳰�����ζػ� */
ER dis_tex(void)
{
	T_KERNEL_TCB_RAM *tcb_ram;

	/* ����ƥ����ȥ����å� */
#ifdef HOS_ERCHK_E_CTX
	if ( sns_ctx() )
	{
		return E_CTX;	/* ����ƥ��������� */
	}
#endif

	tcb_ram = kernel_get_run_tsk();

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ���֥������Ⱦ��֥����å� */
#ifdef HOS_ERCHK_E_OBJ
	if ( tcb_ram->texcb == NULL )
	{
		mknl_unl_sys();		/* �����ƥ�Υ�å���� */
		return E_OBJ;		/* ���֥������Ⱦ������� */
	}
#endif

	/* �㳰�����ζػ� */
	mknl_dis_tex(&tcb_ram->mtcb);

	mknl_unl_sys();		/* �����ƥ�Υ�å���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
