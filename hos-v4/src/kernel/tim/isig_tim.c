/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� �����ƥ���ִ���                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tim.h"



/* �����ޥꥹ�ȴ��� */
T_KERNEL_TIM *kernel_tml_head;		/* �����ޥꥹ����Ƭ���� */
T_KERNEL_TIM *kernel_tml_ptr;		/* �����ޥꥹ�ȥݥ��� */



/* ������ƥ��å��ζ��� */
ER isig_tim(void)
{
	UW     prev_tim;
	RELTIM tic;

	/* �û����륿����ƥ��å��򻻽� */
	/* �㤨�� 10/3 ms �����ʤ� 3, 3, 4, 3, 3, 4, ... �ȥ�����Ȥ��Ƥ��� */
	kernel_tic_cnt--;
	if ( kernel_tic_cnt < kernel_tic_mod )
	{
		tic = kernel_tic_div + 1;	/* ����ڤ�ʤ�ʬ������ */
	}
	else
	{
		tic = kernel_tic_div;
	}
	if ( kernel_tic_cnt == 0 )
	{
		kernel_tic_cnt = kernel_tic_deno;
	}

	mknl_loc_sys();		/* �����ƥ�Υ�å� */

	/* �����ƥॿ����˲û� */
	prev_tim = kernel_systim.ltime;
	kernel_systim.ltime += tic;
	if ( kernel_systim.ltime < prev_tim )	/* ��夬�꤬����ʤ� */
	{
		kernel_systim.utime++;
	}

	/* �����ޥ��֥������ȤΥϥ�ɥ�ƤӽФ� */
	if ( kernel_tml_head != NULL )
	{
		/* �����ݥ������� */
		kernel_tml_ptr = kernel_tml_head;

		do /* �ꥹ�������ޤǷ����֤� */
		{
			/* �����ޥϥ�ɥ�ƤӽФ� */
			kernel_tml_ptr->timhdr(kernel_tml_ptr, tic);
			
			/* �ϥ�ɥ���Ǻ�����줿��� */
			if ( kernel_tml_ptr == NULL )
			{
				break;
			}
			
			/* �ݥ��󥿤���˿ʤ�� */
			kernel_tml_ptr = kernel_tml_ptr->next;
		} while ( kernel_tml_ptr != kernel_tml_head );
		
		/* �����ݥ��󥿤Υ��ꥢ */
		kernel_tml_ptr = NULL;
	}
	
	/* �����ॢ�����Ԥ�����Υ��������� */
	mknl_tic_tmout(tic);	/* �����ॢ���ȥ��塼�˥�����ƥ��å��򶡵� */
	
	mknl_unl_sys();			/* �����ƥ�Υ�å���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
