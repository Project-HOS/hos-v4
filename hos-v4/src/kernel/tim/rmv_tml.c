/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ���ִ���                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tim.h"



/* �����ޥ��֥������Ȥ�ꥹ�Ȥ����� */
void kernel_rmv_tml(
		T_KERNEL_TIM *timobj)	/* ������륿���ޥ��֥������� */
{
	/* ̤��Ͽ�ʤ鲿�⤷�ʤ� */
	if ( timobj->next == NULL )
	{
		return;
	}
	
	/* ������Υ����ޤʤ�ݥ��󥿤򤺤餹(�����к�) */
	if ( timobj == kernel_tml_ptr )
	{
		if ( timobj->next == kernel_tml_head )
		{
			kernel_tml_ptr = NULL;			/* �����ʤ顢���Υݥ��󥿤�̵�� */
		}
		else
		{
			kernel_tml_ptr = timobj->next;	/* ���Υ��֥������Ȥ˰�ư */
		}
	}
	
	/* �ꥹ�Ȥ����� */
	if ( timobj == timobj->next )
	{
		/* �ꥹ�Ȥ����ˤʤ��� */
		kernel_tml_head = NULL;
	}
	else
	{
		/* ��Ƭ�ʤ���Ƭ���֤򤺤餹 */
		if ( timobj == kernel_tml_head )
		{
			kernel_tml_head = timobj->next;
		}
		
		/* �ꥹ�Ȥ����� */
		timobj->next->prev = timobj->prev;
		timobj->prev->next = timobj->next;
	}

	/* ̤��Ͽ������ */
	timobj->next = NULL;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
