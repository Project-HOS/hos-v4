/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*   �ץ��å���ݲ�����ݡ��ͥ�� (��Ω H8/300H ��)                       */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* �����ߥޥ����Υ١����ͤ��ѹ� */
ER chg_imsk(
		IMSK imsk)		/* ���ꤹ��ޥ����� */
{
	/* �ѥ�᡼���������å� */
#ifdef HOS_ERCHK_E_PAR
	if ( (imsk & ~(H83_IMSK_I_BIT | H83_IMSK_UI_BIT)) != 0 )
	{
		return E_PAR;
	}
#endif
	
	mknl_loc_sys();		/* �����ƥ�Υ�å� */
	
	/* �١����ޥ����ͤ��ѹ� */
	kernel_h83_ibmsk = imsk;
	
	if ( mknl_sns_ctx() )
	{
		/* �����ߥ���ƥ����Ȥʤ�ޥ�����٥�UP�Τ�ȿ�� */
		kernel_h83_imsk |= imsk;
	}
	else
	{
		/* ����������ƥ����Ȥʤ鸽�ߤΥޥ����ͤ�¨���ѹ� */
		kernel_h83_imsk = imsk;
	}
	
	mknl_unl_sys();		/* �����ƥ�Υ����å� */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
