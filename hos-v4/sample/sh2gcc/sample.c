/* ------------------------------------------------------------------------ */
/*  HOS-V4 サンプルプログラム                                               */
/*   メインルーチン                                                         */
/*                                                                          */
/*                                   Copyright (C) 2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#include <stdio.h>
#include "kernel.h"
#include "kernel_id.h"
#include "sh7045.h"
#include "sci.h"
#include "sample.h"


#define SCIID	ID_SCI1


int main()
{
	char c;
	
	/* I/O の初期化 */
	*SH_PEIOR = 0x00ff;
	*SH_PEDR  = 0;
	*SH_PACRL2 |= 0x0100;
	
	*SH_PEDR = 0x00;
	
	sta_hos();
	
	return 0;
}


/* ATT_INI 登録の関数 */
void TestStart(VP_INT exinf)
{
	/* タスク起動 */
	act_tsk(TSKID_TEST1);
	act_tsk(TSKID_TEST2);
	act_tsk(TSKID_TEST3);
}


/* サンプルタスク１ */
void Task1(VP_INT exinf)
{
	ER ercd;
	UB c;
	SYSTIM st;
	
	sci_open(SCIID, 0x13);
	
	sci_puts(SCIID, "\r\nTask1:Start\r\n");
	
	for ( ; ; )
	{
		c = sci_getc(SCIID);
		sci_putc(SCIID, c);
	}
	
	wup_tsk(1);
	slp_tsk();
	
	ercd = slp_tsk();
	
	
	ext_tsk();
}


/* サンプルタスク２ */
void Task2(VP_INT exinf)
{
	ER ercd;

	ercd = wup_tsk(1);

	ext_tsk();
}


/* サンプルタスク3 */
void Task3(VP_INT exinf)
{
	ER  ercd;
	volatile int i;
	
	ercd = wup_tsk(1);
	
	for ( ; ; )
	{
		*SH_PEDR ^= 0x0080;
		dly_tsk(1000);
	}
	
	ext_tsk();
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
