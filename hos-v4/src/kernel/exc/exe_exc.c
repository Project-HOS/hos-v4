/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� CPU�㳰�ϥ�ɥ����                                     */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#include "knl_exc.h"



/* CPU�㳰�ϥ�ɥ�γ��� */
void kernel_sta_exc(void)
{
	/* �󥿥�����(�����ߥ���ƥ����Ȥ˰ܹ�) */
	mknl_sta_ind();
}


/* CPU�㳰�ϥ�ɥ�ν�λ */
void kernel_end_exc(void)
{
	/* ���������˰ܹ� */
	mknl_ext_ind();

	/* �ٱ�ǥ����ѥå��¹� */
	mknl_dly_dsp();
}


/* CPU�㳰�ϥ�ɥ�߽����¹� */
void kernel_exe_exc(
		EXCNO excno)		/* CPU�㳰�ϥ�ɥ��ֹ� */
{
	T_KERNEL_EXCCB exccb;
	
	if ( excno < TMIN_EXCNO || excno > TMAX_EXCNO )
	{
		return;
	}
	
	exccb = kernel_exccb_tbl[excno];	/* ������˥��ԡ� */
	
	mknl_unl_sys();		/* ¿�ų����ߵ��� */
	
	if ( exccb.exchdr != NULL )
	{
		exccb.exchdr();			/* CPU�㳰�ϥ�ɥ�¹� */
	}
	
	mknl_loc_sys();		/* ¿�ų����߶ػ� */
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
