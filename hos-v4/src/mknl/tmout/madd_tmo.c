/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �̥����ͥ� �����ॢ���ȥ��塼����                                     */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



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


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
