/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*   �ץ��å���ݲ�����ݡ��ͥ�� (ARM��)  �����ߥޥ�������             */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �����Х��ѿ���� */
UW hospac_arm_imsk  = ARM_IMSK_USR_MODE;		/* �����ߥޥ��� */
UW hospac_arm_bimsk = ARM_IMSK_USR_MODE;		/* �١��������ߥޥ��� */


/* �����ߥޥ������� */
ER chg_imsk(IMSK imsk)
{
	/* �ѥ�᡼���������å� */
#ifdef HOS_ERCHK_E_PAR
	if ( (imsk & ~(ARM_IMSK_FIQ | ARM_IMSK_IRQ)) != 0 )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();		/* �����ƥ�Υ�å� */

	hospac_arm_bimsk = (imsk | ARM_IMSK_USR_MODE);
	
	if ( !mknl_sns_ctx() )
	{
		hospac_arm_imsk = hospac_arm_bimsk;
	}
	else
	{
		hospac_arm_imsk |= hospac_arm_bimsk;
	}

	mknl_unl_sys();		/* �����ƥ�Υ����å� */

	return E_OK;
}


/* �����ߥޥ����λ��� */
ER get_imsk(IMSK *p_imsk)
{
	*p_imsk = (hospac_arm_bimsk & (ARM_IMSK_FIQ | ARM_IMSK_IRQ));
	
	return E_OK;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
