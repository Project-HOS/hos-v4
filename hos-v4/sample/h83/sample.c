/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ����ץ�ץ����                           */
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
	/* SCI�ν���� */
	Sci_Initialize(SCI_31250 /*0x19*/);
	
	/*
	ASTCR = 0xff;
	WCR   = 0xf0;
	*/
	
	/* ���ϥ�å����� */
	Sci_PutChar('H');
	Sci_PutChar('O');
	Sci_PutChar('S');
	Sci_PutChar('\r');
	Sci_PutChar('\n');
	
	sta_hos();
	
	return 0;
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
		Sci_PutChar('0' + (st.ltime / 10000) % 10);
		Sci_PutChar('0' + (st.ltime / 1000) % 10);
		Sci_PutChar('0' + (st.ltime / 100) % 10);
		Sci_PutChar('0' + (st.ltime / 10) % 10);
		Sci_PutChar('0' + (st.ltime / 1) % 10);
		Sci_PutChar(':');
		
		/* ��������å����� */
		Sci_PutChar('T');
		Sci_PutChar('a');
		Sci_PutChar('s');
		Sci_PutChar('k');
		Sci_PutChar('1');
		Sci_PutChar('\r');
		Sci_PutChar('\n');
		
		/* 1���Ԥ� */
		dly_tsk(1000);
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
