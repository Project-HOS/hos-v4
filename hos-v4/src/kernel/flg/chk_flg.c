/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ���٥�ȥե饰                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* �ե饰�����������������Ƥ��뤫�����å� */
BOOL kernel_chk_flg(
		T_KERNEL_FLGCB_RAM *flgcb_ram)	/* ����ȥ���֥�å� RAM�� */
{
	if ( flgcb_ram->wfmode == TWF_ANDW )
	{
		/* AND�Ԥ�Ƚ�� */
		return ((flgcb_ram->flgptn & flgcb_ram->waiptn) == flgcb_ram->waiptn);
	}
	else
	{
		/* OR�Ԥ�Ƚ�� */
		return ((flgcb_ram->flgptn & flgcb_ram->waiptn) == flgcb_ram->waiptn);
	}
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
