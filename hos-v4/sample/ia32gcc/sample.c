/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ����ץ�ץ����                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#include "kernel.h"
#include "kernel_id.h"
#include "printk.h"


/* ������ϥ�ɥ� */
void Initialize(VP_INT exinf)
{
  cls();
  printk("HOS-V4/IA32 test program start.\n");
  act_tsk(TSKID_SAMPLE1);
}
/* ����ץ륿���� */
void Task1(VP_INT exinf)
{
	SYSTIM st;
	char timer[6];
	unsigned int count=0;
	for (count=0 ;count<100 ;++count )
	{
		/* �������ͼ��� */
		get_tim(&st);
		
		/* �������ͽ��� */
		timer[0]='0' + (st.ltime / 10000) % 10;
		timer[1]='0' + (st.ltime / 1000) % 10;
		timer[2]='0' + (st.ltime / 100) % 10;
		timer[3]='0' + (st.ltime / 10) % 10;
		timer[4]='0' + (st.ltime / 1) % 10;
		timer[5]='\0';
		printk("time:%s\n",timer);
		
		/* ��������å����� */
		printk("Task1\n");
		
		/* 1���Ԥ� */
		dly_tsk(1000);
	}
	__asm__("int3\n\t");
}


/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
