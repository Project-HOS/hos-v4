/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �̥����ͥ� �����ॢ���ȥ��塼����                                     */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#include "mknl.h"



/* �����ॢ���ȥ��塼�ϸ�Ψ������ͥ���ñ�㸡���Ȥ��Ƥ���   */
/* �����ॢ�����Ԥ���Ԥ��������������ʤ����Ȥ�����Ȥ��Ƥ��뤬 */
/* ��˾������� I/F ���Ѥ��������������Heap���Ѥ����ꡢTCB��   */
/* �����ॢ�����Ѥ�Ϣ��ݥ��󥿤��Ѱդ���Ⱦ����ڤǴ�������褦 */
/* �ѹ����������ǽ�Ǥ���                                       */


INT mknl_timout_tskcnt = 0;		/* �����ॢ�����Ԥ�����Υ������Ŀ� */



/* �����ॢ���Ȥ˥�����ƥ��å����� */
void mknl_tic_tmout(
		RELTIM tictim)		/* �ɲä��륿����ƥ��å� */
{
	int i;

	/* �����ॢ�����Ԥ�����Υ��������� */
	while ( (volatile INT)mknl_timout_tskcnt > 0 )
	{
		/* �����ॢ���Ȥ��ɤ���Ƚ�� */
		if ( mknl_timout[0].diftim > tictim )
		{
			/* �����ॢ���ȤǤʤ���л��֤򸺤��ƥ롼�פ�ȴ���� */
			mknl_timout[0].diftim -= tictim;
			break;
		}

		/* �����ॢ���Ȥʤ� */
		mknl_wup_tsk(mknl_timout[0].mtcb, E_TMOUT);	/* �����ॢ���ȵ��� */

		/* ��Ƭ���Ԥ��������򳰤� */
		mknl_timout[1].diftim += mknl_timout[0].diftim;	/* �������ʤ��ƤⳲ��̵�� */
		for ( i = 1; i < mknl_timout_tskcnt; i++ )
		{
			mknl_timout[i - 1] = mknl_timout[i];
		}
		mknl_timout_tskcnt--;

		mknl_exe_dsp();		/* �ٱ�ǥ����ѥå�ͽ���Ԥ� */

		/* �����ǰ��١�¿�ų����ߤε����Ϳ���� */
		mknl_unl_sys();		/* �����ƥ�Υ�å���� */
		mknl_loc_sys();		/* �����ƥ�Υ�å� */
	}
}


/* �����ॢ�����Ԥ�����˥��������ɲ� */
ER mknl_add_tmout(
		T_MKNL_TCB *mtcbs,	/* �Ԥ�����˲ä��륿���� */
		RELTIM     tmout)	/* �����ॢ���ȤޤǤλ��� */
{
	INT i, j;

	/* �Ԥ������������å� */
#ifdef HOS_ERCHK_E_NOMEM
	if ( mknl_timout_tskcnt >= mknl_timout_size )
	{
		return E_NOMEM;
	}
#endif

	/* �������֤򸡺�(���ֽ������) */
	for ( i = 0; i < mknl_timout_tskcnt; i++ )
	{
		if ( mknl_timout[i].diftim < tmout )
		{
			break;	/* ���������褿��ȴ���� */
		}
		tmout -= mknl_timout[i].diftim;	/* ���֤κ�ʬ�Ǵ������� */
	}
	if ( i < mknl_timout_tskcnt )
	{
		/* ����ʤ������ΰ٤˸����ư */
		for ( j = mknl_timout_tskcnt; j > i; j-- )
		{
			mknl_timout[j] = mknl_timout[j - 1];
		}
		mknl_timout[j].diftim -= tmout;
	}
	mknl_timout[i].mtcb   = mtcbs;
	mknl_timout[i].diftim = tmout;

	mknl_timout_tskcnt++;

	return E_OK;
}


/* �����ॢ�����Ԥ����󤫤饿�������� */
void mknl_del_tmout(
		T_MKNL_TCB *mtcbs)	/* �Ԥ����󤫤������륿���� */
{
	INT i;

	/* �������򸡺� */
	for ( i = 0; i < mknl_timout_tskcnt; i++ )
	{
		if ( mknl_timout[i].mtcb == mtcbs )
		{
			/* ��� */
			if ( i < mknl_timout_tskcnt - 1 )
			{
				mknl_timout[i + 1].diftim += mknl_timout[i].diftim;
				for ( i++; i < mknl_timout_tskcnt; i++ )
				{
					mknl_timout[i - 1] = mknl_timout[i];
				}
			}
			mknl_timout_tskcnt--;
			break;
		}
	}
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
