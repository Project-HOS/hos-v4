/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �̥����ͥ� �����ƥ�����                                               */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#include "mknl.h"
#include "kernel.h"


/* �����Х��ѿ���� */
STAT            mknl_ctx_stat;			/* �����ƥ�Υ���ƥ����Ⱦ��� */
T_MKNL_TCB      *mknl_run_mtcb = NULL;	/* �¹��楿��������ȥ���֥�å� */
T_HOSPAC_CTXINF mknl_idlctx;			/* �����ɥ�롼�פΥ���ƥ����� */


/* �̥����ͥ륷���ƥ�ν���� */
void mknl_ini_sys(void)
{
	hospac_ini_sys();					/* �ץ��å���ݲ�����ݡ��ͥ�Ȥν���� */
}



/* �������ȥ��åץ롼����γ��Ͻ��� */
void mknl_sta_startup(void)
{
	mknl_ctx_stat = TSS_INDP | TSS_DINT;	/* �����߶ػߤǥ�������Ω�������� */
}


/* �������ȥ��åץ롼����ν�λ���� */
void mknl_ext_startup(void)
{						
	T_MKNL_TCB *mtcb;

	mknl_ctx_stat = TSS_TSK;	/* �������������� */

	/* �ǹ�ͥ���٤μ¹Բ�ǽ��������õ�� */
	mtcb = mknl_srh_top();

	/* ���δؿ���ƤӽФ�������ƥ����Ȥ򥢥��ɥ륿�����Ȥ��ƽ������� */
	if ( mtcb != NULL )
	{
		mknl_run_mtcb = mtcb;
		hospac_swi_ctx(&mknl_idlctx, &mtcb->ctxinf);	/* �������򳫻� */
		mknl_run_mtcb = NULL;
	}
	else
	{
		mknl_run_mtcb = NULL;
		hospac_swi_ctx(&mknl_idlctx, &mknl_idlctx);		/* �����ɥ륳��ƥ�������Ͽ�Τ� */
	}

	hospac_ena_int();	/* �����ߤε��� */
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
