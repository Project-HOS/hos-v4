/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �̥����ͥ� ����������                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �������ζ����Ԥ���� */
void mknl_rsm_tsk(
		T_MKNL_TCB *mtcb)	/* �����Ԥ�������륿���� */
{
	/* �����Ԥ���� */
	if ( mtcb->tskstat == TTS_WAS )
	{
		mtcb->tskstat = TTS_WAI;		/* ����Ԥ����֤ʤ��Ԥ����� */
	}
	else
	{
		mtcb->tskstat = TTS_RDY;		/* �����Ԥ����֤ʤ�¹Բ�ǽ���� */
		mknl_adf_que(&mknl_rdq_tbl[mtcb->tskpri - TMIN_TPRI], mtcb);
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
