/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ����������                                            */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#include "kernel.h"



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
	
	if ( intno < TMIN_INTNO || intno > TMAX_INTNO )
	{
		return;
	}
	
	intcb = kernel_intcb_tbl[intno];	/* ��������˥��ԡ� */
	
	mknl_unl_sys();		/* ¿�ų����ߵ��� */
	
	if ( intcb.isr != NULL )
	{
		intcb.isr(intcb.exinf);			/* �����ߥ����ӥ��롼����¹� */
	}
	
	mknl_loc_sys();		/* ¿�ų����߶ػ� */
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */