/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ���٥�ȥե饰                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"



/* �ե饰�����������������Ƥ��뤫�����å� */
BOOL kernel_chk_flg(
		T_KERNEL_FLGCB_RAM *flgcb_ram,	/* ����ȥ���֥�å� RAM�� */
		T_KERNEL_FLGINF    *pk_flginf)	/* �Ԥ��ե饰����ѥ��åȤ���Ƭ���� */
{
	if ( pk_flginf->wfmode == TWF_ANDW )
	{
		/* AND�Ԥ�Ƚ�� */
		return ((flgcb_ram->flgptn & pk_flginf->waiptn) == pk_flginf->waiptn);
	}
	else
	{
		/* OR�Ԥ�Ƚ�� */
		return ((flgcb_ram->flgptn & pk_flginf->waiptn) != 0);
	}
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
