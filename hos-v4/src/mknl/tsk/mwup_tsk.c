/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �̥����ͥ� ����������                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* ���������Ԥ���� */
void mknl_wup_tsk(
		T_MKNL_TCB *mtcb,	/* ���꡼�ײ�����륿���� */
		ER_UINT    ercd)	/* ������륿�������Ϥ����顼������ */
{
	/* �������Υ��꡼�ײ�� */
	mtcb->ercd = ercd;
	mknl_adf_que(&mknl_rdq_tbl[mtcb->tskpri - TMIN_TPRI], mtcb);
	if ( mtcb->tskstat == TTS_WAI )
	{
		mtcb->tskstat = TTS_RDY;	/* �Ԥ�����ʤ�¹Բ�ǽ���� */
	}
	else
	{
		mtcb->tskstat = TTS_SUS;	/* ����Ԥ����֤ʤ鶯���Ԥ����� */
	}
	mtcb->tskwait = 0;		/* �Ԥ��װ����ꥢ */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
