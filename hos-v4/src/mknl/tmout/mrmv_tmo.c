/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �̥����ͥ� �����ॢ���ȥ��塼����                                     */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �����ॢ�����Ԥ����󤫤饿����������� */
void mknl_rmv_tmout(
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
