/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� �������㳰������ǽ                                      */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"
#include "knl_sys.h"



/* �������㳰�����ε��� */
ER ena_tex(void)
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
	mknl_ena_tex(&tcb_ram->mtcb);

	/* ��α���줿�㳰����������Фμ¹� */
	mknl_exe_tex();

	mknl_unl_sys();		/* �����ƥ�Υ�å���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
