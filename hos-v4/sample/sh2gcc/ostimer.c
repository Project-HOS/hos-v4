/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ����ץ�ץ����                           */
/*   OS�ѥ�����                                                             */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"
#include "sh7045.h"
#include "ostimer.h"



/* OS�ѥ����޽���� */
void ostim_init(VP_INT exinf)
{
	/* �����޽���� */
	*SH_CMCSR0 = 0x0040;
	*SH_CMCOR0 = (UH)(INT)exinf;
	*SH_CMSTR  = 0x0001;
	*SH_IPRG   = 0x00f0;
}


/* �����ߥϥ�ɥ饵��ץ� */
void ostim_hdr(VP_INT exinf)	/* OS�������ѥϥ�ɥ� */
{
	*SH_CMCSR0 &= 0xff7f;
	
	isig_tim();		/* ������ƥ��å��ζ��� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
