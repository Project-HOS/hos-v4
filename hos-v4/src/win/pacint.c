/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �ץ��å���ݲ�����ݡ��ͥ�� (Windows��)                            */
/*    �����߽���                                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* ���������ߤΥ��ߥ�졼��(ITRON�������Ȥ�̵�ط��Υ���åɤ���Ƥ֤���) */
void hospac_win_int(INTNO intno)
{
	T_HOSPAC_CTXINF *ctxinf;

	/* �ϰϥ����å� */
	if ( intno < KERNEL_TMIN_INTNO || intno > KERNEL_TMAX_INTNO )
	{
		return;
	}

	/* ���ޥե����� */
	WaitForSingleObject(hospac_hSem, INFINITE);

	/* �¹��楹��åɤ򥵥��ڥ�ɤ��� */
	if ( mknl_run_mtcb != NULL )
	{
		ctxinf = &mknl_run_mtcb->ctxinf;
	}
	else
	{
		ctxinf = &mknl_idlctx;
	}
	SuspendThread(ctxinf->hThread);
	ctxinf->blIntSuspend = TRUE;

	/* �����ߥե饰���å� */
	hospac_blInt = TRUE;

	/* �󥿥�����(�����ߥ���ƥ����Ȥ˰ܹ�) */
	mknl_sta_ind();
	
	/* �����ߤμ¹� */
	if ( kernel_intcb_tbl[intno].isr != NULL )
	{
		kernel_intcb_tbl[intno].isr(kernel_intcb_tbl[intno].exinf);			/* �����ߥ����ӥ��롼����¹� */
	}

	/* ���������˰ܹ� */
	mknl_ext_ind();

	/* �����ߥե饰���ꥢ */
	hospac_blInt = FALSE;

	/* �ٱ�ե饰���ꥢ */
	mknl_ctx_stat = MKNL_TSS_TSK;

	/* �ǹ�ͥ���٤μ¹Բ�ǽ��������õ�� */
	mknl_run_mtcb = mknl_srh_top();
	if ( mknl_run_mtcb != NULL )
	{
		ctxinf = &mknl_run_mtcb->ctxinf;
	}
	else
	{
		ctxinf = &mknl_idlctx;
	}

	/* ���ޥե����ֵ� */
	if ( ctxinf->blIntSuspend )
	{
		ctxinf->blIntSuspend = FALSE;
		ReleaseSemaphore(hospac_hSem, 1, NULL);
	}

	/* �¹��楹��åɤ����� */
	ResumeThread(ctxinf->hThread);
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
