/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*   �ץ��å���ݲ�����ݡ��ͥ�� (ARM��)  �����ߥޥ�������             */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* �����Х��ѿ���� */
UW hospac_arm_imsk = ARM_IMSK_USR_MODE;	/* �����ߥޥ��� */



/* �����ߥޥ������� */
ER chg_imsk(IMASK imsk)
{
	/* �ѥ�᡼���������å� */
#ifdef HOS_ERCHK_E_PAR
	if ( (imsk & ~(ARM_IMSK_FIQ | ARM_IMSK_IRQ)) != 0 )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();		/* �����ƥ�Υ�å� */

	hospac_arm_imsk = (hospac_arm_imsk | ARM_IMSK_USR_MODE);

	mknl_unl_sys();		/* �����ƥ�Υ����å� */

	return E_OK;
}


/* �����ߥޥ����λ��� */
ER get_imsk(IMASK *p_imsk)
{
	*p_imsk = (hospac_arm_imsk & (ARM_IMSK_FIQ | ARM_IMSK_IRQ));
	
	return E_OK;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
