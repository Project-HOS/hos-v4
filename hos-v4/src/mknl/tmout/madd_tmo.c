/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �̥����ͥ� �����ॢ���ȥ��塼����                                     */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �����ॢ�����Ԥ�����˥��������ɲ� */
ER mknl_add_tmout(
		T_MKNL_TCB *mtcb,	/* �Ԥ�����˲ä��륿���� */
		RELTIM     tmout)	/* �����ॢ���ȤޤǤλ��� */
{
	T_MKNL_TCB* mtcb_tmp;

	/* �ǽ�Σ��Ĥʤ� */
	if ( mknl_timout_head == NULL )
	{
		/* �ǽ�Σ��Ĥ򥭥塼����Ͽ */
		mtcb->tm_next    = mtcb;
		mtcb->tm_prev    = mtcb;
		mknl_timout_head = mtcb;

		/* �����ॢ���Ȼ�������� */
		mtcb->diftim = tmout;

		return E_OK;
	}
	
	/* �������򸡺� */
	mtcb_tmp = mknl_timout_head;
	do
	{	
		/* ������� */
		if ( tmout < mtcb_tmp->diftim )
		{
			/* ���֤κ�ʬ������ */
			mtcb_tmp->diftim -= tmout;
			mtcb->diftim      = tmout;

			/* �ꥹ�Ȥ����� */
			mtcb->tm_next          = mtcb_tmp;
			mtcb->tm_prev          = mtcb_tmp->tm_prev;
			mtcb->tm_next->tm_prev = mtcb;
			mtcb->tm_prev->tm_next = mtcb;
			
			/* ��Ƭ�ʤ� */
			if ( mtcb_tmp == mknl_timout_head )
			{
				mknl_timout_head = mtcb;	/* ��Ƭ�ݥ��󥿹��� */
			}
			
			return E_OK;
		}
		
		tmout -= mtcb_tmp->diftim;		/* ��ʬ�򸺻� */
		
		mtcb_tmp = mtcb_tmp->tm_next;	/* ����TCB�ؿʤ� */
	} while ( mtcb_tmp != mknl_timout_head->tm_prev );	/* �ꥹ�Ȥ�������ޤǥ롼�� */
	
	/* �������ɲ� */
	mtcb->tm_next          = mtcb_tmp->tm_next;
	mtcb->tm_prev          = mtcb_tmp;
	mtcb->tm_next->tm_prev = mtcb;
	mtcb->tm_prev->tm_next = mtcb;

	/* �Ĥä���ʬ������ */
	mtcb->diftim = tmout;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
