/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ��������°Ʊ����ǽ                                      */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* �������ε����Ԥ� */
ER slp_tsk(void)
{
	T_KERNEL_TCB_RAM *tcb_ram;
	ER ercd;

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ����ƥ����ȥ����å� */
#ifdef HOS_ERCHK_E_CTX
	if ( mknl_sns_wai() )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_CTX;	/* ����ƥ��������� */
	}
#endif

	tcb_ram = kernel_get_run_tsk();

	/* �����׵ᥭ�塼���󥰤Υ����å� */
	if ( tcb_ram->wupcnt > 0 )
	{
		tcb_ram->wupcnt--;
		mknl_unl_sys();		/* �����ƥ�Υ�å���� */
		return E_OK;
	}
	
	/* �Ԥ����֤����� */
	mknl_wai_tsk(&tcb_ram->mtcb, TTW_SLP);
	
	ercd = (ER)mknl_exe_dsp();	/* �������ǥ����ѥå��μ¹� */
	mknl_exe_tex();				/* �㳰�����μ¹� */
	
	mknl_unl_sys();		/* �����ƥ�Υ�å���� */
	
	return ercd;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
