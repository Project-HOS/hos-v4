/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ����ץ�ץ������                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include "kernel.h"
#include "kernel_id.h"
#include "h83664f.h"
#include "h8t_sci.h"



/* �ᥤ��ؿ� */
int main()
{
	/* SCI�ν���� */
	Sci_Initialize(SCI_19200);

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
/*      act_tsk(TSKID_SAMPLE1);*/
}

int foo( int a, int b, int c, int d)
{
    return a+b-c-d;
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
/*  Copyright (C) 1998-2003 by Project HOS                                  */
/* ------------------------------------------------------------------------ */