/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ������������ǽ                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* ������ͥ���٤��ѹ� */
ER chg_pri(
		ID tskid,		/* �ѹ��оݤΥ�����ID�ֹ� */
		PRI tskpri)		/* �ѹ���Υ١���ͥ���� */
{
	T_KERNEL_TCB_RAM *tcb_ram;

	/* ID �ϰϥ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( tskid != TSK_SELF && (tskid < TMIN_TSKID || tskid > TMAX_TSKID) )
	{
		return E_ID;	/* ����ID�ֹ� */
	}
#endif

	/* �ѥ�᡼�����ϰϥ����å� */
#ifdef HOS_ERCHK_E_PAR
	if ( tskpri < TMIN_TPRI || tskpri > TMAX_TPRI )
	{
		return E_PAR;	/* �ѥ�᡼�������� */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ����������ȥ���֥�å����� */
	if ( tskid == TSK_SELF )
	{
		/* ����������������Ѵ� */
#ifdef HOS_ERCHK_E_ID
		if ( mknl_sns_ctx() )
		{
			/* �󥿥�������ƥ����Ȥ� TSK_SELF��������� */
			mknl_unl_sys();		/* �����ƥ�Υ�å���� */
			return E_ID;		/* ����ID�ֹ� */
		}
#endif
		tcb_ram = kernel_get_run_tsk();
	}
	else
	{
		/* ID�ֹ��������Ѵ� */
		tcb_ram = KERNEL_TSKID_TO_TCB_RAM(tskid);

		/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
		if ( tcb_ram == NULL )
		{
			mknl_unl_sys();		/* �����ƥ�Υ�å���� */
			return E_NOEXS;		/* ���֥�������̤���� */
		}
#endif
	}

	/* ��ư��ͥ���ٻ���ξ�� */
	if ( tskpri == TPRI_INI )
	{
		tskpri = tcb_ram->tcb_rom->itskpri;
	}

	/* ���֥������Ȥξ��֥����å� */
#ifdef HOS_ERCHK_E_OBJ
	if ( mknl_get_tskstat(&tcb_ram->mtcb) == TTS_DMT )	/* �ٻ߾��֤ʤ�� */
	{
		return E_OBJ;	/* ���֥������Ⱦ��֥��顼 */
	}
#endif

	/* ͥ�����ѹ� */
	mknl_chg_pri(&tcb_ram->mtcb, tskpri);
	
	mknl_exe_dsp();		/* �������ǥ����ѥå��μ¹� */
	mknl_exe_tex();		/* �㳰�����μ¹� */
	
	mknl_unl_sys();		/* �����ƥ�Υ�å���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
