/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*   �ץ��å���ݲ�����ݡ��ͥ�� (SH��)  �����ߥޥ�������              */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* �����Х��ѿ���� */
UW hospac_sh_imsk      = 0;		/* �����ߥޥ��� */
UW hospac_sh_imsk_base = 0;		/* �����ߥޥ����١����� */



/* �����ߥޥ������� */
ER chg_imsk(IMSK imsk)
{
	/* �ѥ�᡼���������å� */
#ifdef HOS_ERCHK_E_PAR
	if ( imsk < 0 || imsk > 15 )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();		/* �����ƥ�Υ�å� */
	
	hospac_sh_imsk_base = (imsk << 4);
	if ( mknl_sns_ctx() || hospac_sh_imsk < hospac_sh_imsk_base )
	{
		hospac_sh_imsk = hospac_sh_imsk_base;
	}
	
	mknl_unl_sys();		/* �����ƥ�Υ����å� */

	return E_OK;
}


/* �����ߥޥ����λ��� */
ER get_imsk(IMSK *p_imsk)
{
	*p_imsk = hospac_sh_imsk_base >> 4;
	
	return E_OK;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
