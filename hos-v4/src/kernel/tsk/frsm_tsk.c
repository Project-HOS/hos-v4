/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ��������°Ʊ����ǽ                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* �����Ԥ����֤���ζ����Ƴ� */
ER frsm_tsk(
		ID tskid)	/* �Ƴ��оݤΥ�������ID�ֹ� */
{
		T_KERNEL_TCB_RAM *tcb_ram;

	/* ID �ϰϥ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( tskid < TMIN_TSKID || tskid > TMAX_TSKID )
	{
		return E_ID;	/* ����ID�ֹ� */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	tcb_ram = KERNEL_TSKID_TO_TCB_RAM(tskid);

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( tcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif

	/* ���֥������Ⱦ��֥����å� */
#ifdef HOS_ERCHK_E_OBJ
	if ( !(mknl_get_tskstat(&tcb_ram->mtcb) & TTS_SUS) )
	{
		/* �����Ԥ����֤Ǥʤ���� */
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_OBJ;	/* ���֥������Ȥξ������� */
	}
#endif

	/* �������ζ����Ԥ�������� */
	tcb_ram->suscnt = 0;
	mknl_rsm_tsk(&tcb_ram->mtcb);
	
	mknl_exe_dsp();		/* �������ǥ����ѥå��μ¹� */
	mknl_exe_tex();		/* �㳰�����μ¹� */
	
	mknl_unl_sys();		/* �����ƥ�Υ�å���� */

	return E_OK;
}			


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
