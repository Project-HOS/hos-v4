/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ����ץ�ץ����                           */
/*   Hitachi H8 �� ����ץ�ץ����                                       */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"
#include "kernel_id.h"
#include "h8_3048.h"
#include "h8_sci.h"



/* �ᥤ��ؿ� */
int main()
{
/*	SCI_Init(0x19); */	/* moniter ROM ����������Ƥ���ΤǤ�����ʤ� (^^;; */
	
	/* ITU0 (�����ƥॿ���ޡ˽���� */
	TCR0   = 0x23;		/* ��/8�ǥ������ */
	TSR0  &= 0xfe;		/* ���ơ������쥸�������ꥢ */
	TIER0  = 0x01;		/* �����ߵ��� */
	GRA0   = 2000 - 1;	/* 1 msec �Υ��󥿡��Х��16MHz���� */
	TSTR  |= 0x01;		/* TCNT0ư��� */
	
	/* ���ϥ�å����� */
	SCI_Putc('H');
	SCI_Putc('O');
	SCI_Putc('S');
	SCI_Putc('\r');
	SCI_Putc('\n');
	
	sta_hos();
}


/* ������ϥ�ɥ� */
void Initialize(VP_INT exinf)
{
	act_tsk(TSKID_SAMPLE1);
}


/* ����ץ륿���� */
void Task1(VP_INT exinf)
{
	SYSTIM st;
	
	for ( ; ; )
	{
		/* �������ͼ��� */
		get_tim(&st);
		
		/* �������ͽ��� */
		SCI_Putc('0' + (st.ltime / 10000) % 10);
		SCI_Putc('0' + (st.ltime / 1000) % 10);
		SCI_Putc('0' + (st.ltime / 100) % 10);
		SCI_Putc('0' + (st.ltime / 10) % 10);
		SCI_Putc('0' + (st.ltime / 1) % 10);
		SCI_Putc(':');
		
		/* ��������å����� */
		SCI_Putc('T');
		SCI_Putc('a');
		SCI_Putc('s');
		SCI_Putc('k');
		SCI_Putc('1');
		SCI_Putc('\r');
		SCI_Putc('\n');
		
		/* 1���Ԥ� */
		dly_tsk(1000);
	}
}


/* �������ѳ����ߥϥ�ɥ� */
void timer_handler(VP_INT exinf)
{
	TSR0 &= 0xfe;
	
	/* ������ƥ��å����� */
	isig_tim();
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
