/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �̥����ͥ� ����������                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �������㳰�������׵� */
void mknl_ras_tex(
		T_MKNL_TCB *mtcb)	/* �㳰�������׵᤹�륿���� */
{
	if ( mtcb == mknl_run_mtcb && !(mtcb->texstat & MKNL_TTS_DRAS) )
	{
		/* �¹��楿�����ǡ��㳰�ػߤǤʤ�����㳰ȯ�� */
		do
		{
			mtcb->texstat = 0;
			kernel_tex_entry();
		} while ( mtcb->texstat != 0 );	/* �㳰�װ����ʤ��ʤ�ޤǥ롼�� */
	}
	else
	{
		/* �㳰����α���� */
		mtcb->texstat &= MKNL_TTS_RDLY;
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
