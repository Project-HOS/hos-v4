/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� �����ƥ���ִ���                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sys.h"



/* ������ͥ���̤β�ž */
ER rot_rdq(
		PRI tskpri)		/* ͥ���̤��ž�����оݤ�ͥ���� */
{
	T_MKNL_TCB* mtcb;

	/* ��������ͥ���ٻ���ν��� */
	if ( tskpri == TPRI_SELF )
	{
#ifdef HOS_ERCHK_E_PAR
		if ( sns_ctx() )
		{
			return E_PAR;
		}
		mtcb   = mknl_get_run_tsk();	/* �¹��楿�����μ��� */
		tskpri = mknl_get_pri(mtcb);	/* ͥ���٤μ��� */
#endif
	}

	/* �ѥ�᡼�����ϰϥ����å� */
#ifdef HOS_ERCHK_E_PAR
	if ( tskpri < TMIN_TPRI ||  tskpri > TMAX_TPRI )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();			/* �����ƥ�Υ�å� */

	mknl_rot_rdq(tskpri);	/* ������ͥ���̤β�ž */
	
	mknl_exe_dsp();			/* �������ǥ����ѥå��μ¹� */
	mknl_exe_tex();			/* �㳰�����μ¹� */
	
	mknl_unl_sys();			/* �����ƥ�Υ�å���� */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
