/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �̥����ͥ� �����ॢ���ȥ��塼����                                     */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �����ॢ�����Ԥ����󤫤饿����������� */
void mknl_rmv_tmout(
		T_MKNL_TCB *mtcb)	/* �Ԥ����󤫤������륿���� */
{
	/* �����ॢ���ȥ��塼��̤��³�ʤ�̵�� */
	if ( mtcb->tm_prev == NULL )
	{
		return;
	}

	/* ���塼�κǸ�Σ��ĥ������ʤ� */
	if ( mtcb->tm_next == mtcb )
	{
		mknl_timout_head = NULL;	/* �����ॢ���ȥ��塼����ˤ��� */
	}
	else
	{
		/* �����Ǥʤ���� */
		if ( mtcb != mknl_timout_head->tm_prev )
		{
			/* ���ֺ�ʬ������ */
			mtcb->tm_next->diftim += mtcb->diftim;
		}
	
		/* ��Ƭ�ʤ� */
		if ( mtcb == mknl_timout_head )
		{
			mknl_timout_head = mtcb->tm_next;	/* ��Ƭ���ֹ��� */
		}
		
		/* ���塼���鳰�� */
		mtcb->tm_next->tm_prev = mtcb->tm_prev;
		mtcb->tm_prev->tm_next = mtcb->tm_next;
	}
	
	/* ̤��³������ */
	mtcb->tm_prev = NULL;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
