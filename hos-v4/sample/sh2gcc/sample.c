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



int main()
{
	char c;
	
	/* I/O の初期化 */
	*SH_PEIOR = 0x00ff;
	*SH_PEDR  = 0;
	*SH_PACRL2 |= 0x0100;
	
	/* タイマ初期化 */
	*SH_CMCSR0 = 0x0041;
	*SH_CMCOR0 = 62499;
	*SH_CMSTR  = 0x0001;
	*SH_IPRG   = 0x00f0;
	
	sci_init();
	
	sci_puts("\r\nStart\r\n");
	
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
	
	sci_puts("\r\nTask1:Start\r\n");
	
	*SH_PEDR |= 0x0001;
	
	wup_tsk(1);
	slp_tsk();
	
	ercd = slp_tsk();

	*SH_PEDR |= 0x0010;

	ext_tsk();
}


/* サンプルタスク２ */
void Task2(VP_INT exinf)
{
	ER ercd;

	*SH_PEDR |= 0x0002;

	ercd = wup_tsk(1);

	*SH_PEDR |= 0x0020;

	ext_tsk();
}


/* サンプルタスク3 */
void Task3(VP_INT exinf)
{
	ER  ercd;
	volatile int i;
	
	*SH_PEDR |= 0x0004;
	
	ercd = wup_tsk(1);
	
	*SH_PEDR |= 0x0040;
	
	*SH_PEDR = 0xaa;
	
	for ( ; ; )
	{
		for ( i = 0; i < 100000; i++ )
			;
		*SH_PEDR ^= 0x0080;
	}
	
	ext_tsk();
}



/* 周期ハンドラサンプル */
void CycHandler1(VP_INT exinf)
{
}


/* 割り込みハンドラサンプル */
void ostim_hdr(VP_INT exinf)	/* OSタイマ用ハンドラ */
{
	*SH_CMCSR0 &= 0xff7f;

	*SH_PEDR = 0x005a;
	
	isig_tim();		/* タイムティックの供給 */
}

/*
static int count = 0;

#pragma interrupt
void Cmt0_Handler(void)
{
	*SH_CMCSR0 &= 0xff7f;
	
	count++;
	if ( count % 1 == 0 )
	{
		*SH_PEDR = ~*SH_PEDR;
	}
}
*/


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
