/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ���顼��ϥ�ɥ�                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_alm.h"



/* ���顼��ϥ�ɥ�Υ����ޥϥ�ɥ� */
void kernel_alm_hdr(
		T_KERNEL_TIM *timobj,	/* �����ޥ��֥������� */
		RELTIM       tic)		/* ������ƥ��å� */
{
	const T_KERNEL_ALMCB_ROM *almcb_rom;
	T_KERNEL_ALMCB_RAM *almcb_ram;
	
	/* upper cast */
	almcb_ram = (T_KERNEL_ALMCB_RAM *)timobj;
	
	/* ���顼�ॿ�����μ¹� */
	if ( almcb_ram->lefttim <= tic )
	{
		almcb_rom = almcb_ram->almcb_rom;
				
		/* ���顼��ϥ�ɥ�򥿥��ޥꥹ�Ȥ��鳰�� */
		kernel_rmv_tml((T_KERNEL_TIM *)almcb_ram);

		/* ���顼��ϥ�ɥ�ƤӽФ� */
		mknl_unl_sys();							/* �����ƥ�Υ�å���� */		
		almcb_rom->almhdr(almcb_rom->exinf);	/* �ϥ�ɥ�ƤӽФ� */
		mknl_loc_sys();							/* �����ƥ�Υ�å� */
	}
	else
	{
		almcb_ram->lefttim -= tic;		/* �Ĥ���֤򸺻� */
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
