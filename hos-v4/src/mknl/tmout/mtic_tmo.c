/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �̥����ͥ� �����ॢ���ȥ��塼����                                     */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �����Х��ѿ� */
T_MKNL_TCB *mknl_timout_head;		/* �����ॢ���ȥ��塼����Ƭ */



/* �����ॢ���Ȥ˥�����ƥ��å����� */
void mknl_tic_tmout(
		RELTIM tictim)		/* �ɲä��륿����ƥ��å� */
{
	register T_MKNL_TCB *mtcb;

	/* ������˥��ԡ� */
	mtcb = mknl_timout_head;

	/* �����ॢ���ȥ��塼�����ʤ�꥿���� */
	if ( mtcb == NULL )
	{
		return;
	}

	/* �����ॢ���ȥ��塼�ν��� */
	for ( ; ; )
	{
		/* �����ॢ���Ȥ�ã���ʤ��ʤ� */
		if ( tictim < mtcb->diftim )
		{
			mtcb->diftim -= tictim;		/* �����ॢ���Ȼ��֤򸺻� */
			break;
		}
		
		tictim -= mtcb->diftim;			/* ������ƥ��å��򸺻� */
		
		mknl_wup_tsk(mtcb, E_TMOUT);	/* �����ॢ���ȵ��� */
		mknl_exe_dsp();					/* �ٱ�ǥ����ѥå�ͽ���Ԥ� */
		
		/* ���塼���鳰�� */
		if ( mtcb->tm_next == mtcb )	/* �Ǹ�Σ��Ĥʤ� */
		{
			/* ���塼����ˤ��� */
			mtcb->tm_prev = NULL;
			mtcb          = NULL;
			break;
		}
		else
		{
			/* ���塼�����곰�� */
			mtcb->tm_next->tm_prev = mtcb->tm_prev;
			mtcb->tm_prev->tm_next = mtcb->tm_next;
			mtcb->tm_prev = NULL;
			mtcb = mtcb->tm_next;
		}

		/* �����ǰ��١�¿�ų����ߤε����Ϳ���� */
		mknl_unl_sys();		/* �����ƥ�Υ�å���� */
		mknl_loc_sys();		/* �����ƥ�Υ�å� */
	}
	
	/* ����˽��᤹ */
	mknl_timout_head = mtcb;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
