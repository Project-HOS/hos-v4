/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �̥����ͥ� ����������                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* ������ͥ�����ѹ� */
void mknl_chg_pri(
				T_MKNL_TCB *mtcb,	/* ͥ���٤��ѹ����륿���� */
				PRI tskpri)			/* ���ꤹ��ͥ���� */
{
	/* ͥ�����ѹ� */
	if ( !(mtcb->tskstat & TTS_WAI) )
	{
		/* �Ԥ����֤Ǥʤ���Х�ǥ������塼�˷Ҥ��ʤ��� */
		mknl_rmv_que(mtcb);
		mknl_adf_que(&mknl_rdq_tbl[tskpri - TMIN_TPRI], mtcb);
	}
	mtcb->tskpri = tskpri;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
