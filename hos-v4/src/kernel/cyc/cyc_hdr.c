/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� �����ϥ�ɥ�                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_cyc.h"



/* �����ϥ�ɥ�Υ����ޥϥ�ɥ� */
void kernel_cyc_hdr(
		T_KERNEL_TIM *timobj,	/* �����ޥ��֥������� */
		RELTIM       tic)		/* ������ƥ��å� */
{
	const T_KERNEL_CYCCB_ROM *cyccb_rom;
	T_KERNEL_CYCCB_RAM *cyccb_ram;
	
	/* upper cast */
	cyccb_ram = (T_KERNEL_CYCCB_RAM *)timobj;
	
	/* �����������μ¹� */
	if ( cyccb_ram->lefttim <= tic )
	{
		cyccb_rom = cyccb_ram->cyccb_rom;
				
		/* �����ͤ����� */
		cyccb_ram->lefttim += cyccb_rom->cyctim - tic;

		/* �����ϥ�ɥ�ƤӽФ� */
		mknl_unl_sys();							/* �����ƥ�Υ�å���� */		
		cyccb_rom->cychdr(cyccb_rom->exinf);	/* �ϥ�ɥ�ƤӽФ� */
		mknl_loc_sys();							/* �����ƥ�Υ�å� */
	}
	else
	{
		cyccb_ram->lefttim -= tic;
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
