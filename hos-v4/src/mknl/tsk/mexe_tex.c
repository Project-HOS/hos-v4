/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �̥����ͥ� ����������                                                 */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �������㳰�����μ¹� */
void mknl_exe_tex(void)
{
	/* �󥿥�������ƥ����Ȥʤ鲿�⤷�ʤ� */
	if ( mknl_ctx_stat & MKNL_TSS_INDP )
	{
		return;
	}

	if (  (mknl_run_mtcb->texstat & MKNL_TTS_RDLY)
				&& !(mknl_run_mtcb->texstat & MKNL_TTS_DRAS) )
	{
		/* �㳰��α�����ꡢ�㳰�ػߤǤʤ�����㳰ȯ�� */
		do
		{
			mknl_run_mtcb->texstat = 0;
			kernel_tex_entry();
		} while ( mknl_run_mtcb->texstat != 0 );	/* �㳰�װ����ʤ��ʤ�ޤǥ롼�� */
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
