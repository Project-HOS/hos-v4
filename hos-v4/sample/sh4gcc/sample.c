/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ����ץ�ץ����                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include "kernel.h"
#include "kernel_id.h"
#include "sh7750.h"
#include "scif.h"


/* �ᥤ��ؿ� */
int main()
{
	/* ���ϥ�å����� */
	scif_puts("HOS-V4/SH4 test program start.\n");
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
		scif_putc('0' + (st.ltime / 10000) % 10);
		scif_putc('0' + (st.ltime / 1000) % 10);
		scif_putc('0' + (st.ltime / 100) % 10);
		scif_putc('0' + (st.ltime / 10) % 10);
		scif_putc('0' + (st.ltime / 1) % 10);
		scif_putc(':');
		
		/* ��������å����� */
		scif_puts("Task1\r\n");
		
		/* 1���Ԥ� */
		dly_tsk(1000);
	}
}


/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
