/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �̥����ͥ� ����������                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �������γ��� */
void mknl_sta_tsk(
		T_MKNL_TCB *mtcb,					/* �̥����ͥ륿��������ȥ���֥�å� */
		VP_INT     exinf,					/* �������γ�ĥ���� */
		FP         task,					/* �������ε�ư���� */
		PRI        tskpri,					/* �������ε�ư��ͥ���� */
		SIZE       stksz,					/* �������Υ����å��ΰ�Υ����� */
		VP         stk)						/* �������Υ����å��ΰ����Ƭ���� */
{
	/* �¹ԥ���ƥ����Ȥκ��� */
	mtcb->data = exinf;
	hospac_cre_ctx(&mtcb->ctxinf, exinf, task, stksz, stk);

	/* �������ξ������� */
	mtcb->tskstat = TTS_RDY;	/* ��ǥ������֤����� */
	mtcb->texstat = 0;			/* �㳰���ֽ���� */
	mtcb->tskpri  = tskpri;		/* ͥ�������� */
	mtcb->tskwait = 0;			/* �Ԥ��װ������ */

	/* ��ǥ������塼������ */
	mknl_adf_que(&mknl_rdq_tbl[tskpri - TMIN_TPRI], mtcb);
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
