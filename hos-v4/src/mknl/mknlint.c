/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �̥����ͥ� �����߽���                                               */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* ������ؿ� */
static void mknl_int_ctx(VP_INT exinf);		/* �����ߥ���ƥ����� */


/* �������ѿ� */
static INTNO           mknl_int_intno;		/* �������ֹ� */
static INT             mknl_int_nstcnt = 0;	/* ¿�ų����ߤΥͥ��ȥ������ */
static T_HOSPAC_CTXINF mknl_intctx;			/* �����ߥ���ƥ����� */
static T_HOSPAC_CTXINF mknl_int_orgctx;		/* ���������Υ���ƥ�������¸�� */



/* �����߽����ν���� */
void mknl_ini_int(void)
{
	/* �����ߥ���ƥ����Ȥκ��� */
	hospac_cre_cnt(&mknl_intctx, 0, mknl_int_ctx, mknl_int_stksz, mknl_int_stk);
}


/* �����߽����¹� */
void mknl_exe_int(INTNO intno)
{
	if ( mknl_int_nstcnt++ != 0 )
	{
		/* ¿�ų����� */
		kernel_exe_int(intno);
		mknl_int_nstcnt--;
		return;
	}
	
	/* �����ߥ���ƥ����Ȥ˰ܹ� */
	mknl_sta_ind();
	
	/* �����å������ؤ� */
	mknl_int_intno = intno;
	hospac_swi_cnt(&mknl_int_orgctx, &mknl_intctx);

	/* �����ߥ���ƥ����Ȥν�λ */
	mknl_int_nstcnt--;
	mknl_ext_ind();
}


/* �����ߤν�λ���� */
void mknl_end_int(void)
{
	if ( mknl_int_nstcnt == 0 )
	{
		mknl_dly_dsp();
	}
}


/* �����߽����ѥ���ƥ����� */
void mknl_int_ctx(VP_INT exinf)
{
	for ( ; ; )
	{
		/* �����߽����¹� */
		kernel_exe_int(mknl_int_intno);
		
		/* ���������Υ���ƥ����Ȥ���� */
		hospac_swi_cnt(&mknl_intctx, &mknl_int_orgctx);
	}
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
