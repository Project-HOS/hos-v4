/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ���ִ���                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tim.h"



/* �����ޥ��֥������Ȥ�ꥹ�Ȥ��ɲ� */
void kernel_add_tml(
		T_KERNEL_TIM *timobj)	/* ��Ͽ���륿���ޥ��֥������� */
{
	/* ������Ͽ����Ƥ����鲿�⤷�ʤ� */
	if ( timobj->next != NULL )
	{
		return;
	}
	
	/* �ꥹ�Ȥ���Ͽ */
	if ( kernel_tml_head == NULL )
	{
		/* �ꥹ�Ȥ����ξ����ɲ� */
		timobj->next = timobj;
		timobj->prev = timobj;
		kernel_tml_head = timobj;
	}
	else
	{
		/* �ꥹ�Ȥ��������ɲ� */
		timobj->next = kernel_tml_head;
		timobj->prev = kernel_tml_head->prev;
		timobj->next->prev = timobj;
		timobj->prev->next = timobj;
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
