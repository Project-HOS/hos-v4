/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ����������                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_int.h"



/* �����ߥ���ƥ����Ȥγ��� */
void kernel_sta_int(void)
{
	/* �󥿥�����(�����ߥ���ƥ����Ȥ˰ܹ�) */
	mknl_sta_ind();
}


/* �����ߥ���ƥ����Ȥν�λ */
void kernel_end_int(void)
{
	/* ���������˰ܹ� */
	mknl_ext_ind();

	/* �ٱ�ǥ����ѥå��¹� */
	mknl_dly_dsp();
}


/* �����߽����¹� */
void kernel_exe_int(
		INTNO intno)		/* �������ֹ� */
{
	T_KERNEL_INTCB intcb;
	
	if ( intno < KERNEL_TMIN_INTNO || intno > KERNEL_TMAX_INTNO )
	{
		return;
	}

	
	intcb = KERNEL_INTNO_TO_INTCB(intno);	/* ������˥��ԡ� */
	
	mknl_unl_sys();		/* ¿�ų����ߵ��� */
	
	if ( intcb.isr != NULL )
	{
		intcb.isr(intcb.exinf);			/* �����ߥ����ӥ��롼����¹� */
	}
	
	mknl_loc_sys();		/* ¿�ų����߶ػ� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
