/* ------------------------------------------------------------------------ */
/*  HOS-V4 サンプル                                                         */
/*   メインルーチン                                                         */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#include <stdio.h>
#include "kernel.h"
#include "kernel_id.h"
#include "test.h"



/* メイン関数 */
int main()
{
	/* 必要ならここで ハードウェアの設定など行う */

	/* HOS-V4 の開始 */
	sta_hos();
	
	return 0;
}


/* ATT_INI 登録の関数 */
void TestStart(VP_INT exinf)
{
	/* タスク起動 */
	act_tsk(TSKID_TEST1);
//	act_tsk(TSKID_TEST2);
	act_tsk(TSKID_TEST3);
}


/* サンプルタスク１ */
void Task1(VP_INT exinf)
{
	int i;
	ER ercd;

	printf("Task1:Start\n");

	/* 自身の wup_tsk */
	wup_tsk(TSKID_TEST1);
	slp_tsk();

	/* データキューへの送信 */
	for ( i = 0; i < 16; i++ )
	{
		printf("Task1 snd_dtq : %d\n", i);
		snd_dtq(DTQID_TEST1, (VP_INT)i);
	}

	printf("Task1:slp_tsk()\n");
	ercd = slp_tsk();
	printf("Task1:slp_tsk() ret = %d\n", ercd);

	printf("Task1:End\n");
	ext_tsk();
}


/* サンプルタスク２ */
void Task2(VP_INT exinf)
{
	ER ercd;

	printf("Task2:Start\n");

	printf("Task2:wup_tsk()\n");
	ercd = wup_tsk(1);
	printf("Task2:wup_tsk(1) ret = %d\n", ercd);

	printf("Task2:End\n");
	ext_tsk();
}


/* サンプルタスク3 */
void Task3(VP_INT exinf)
{
	VP_INT msg;
	ER ercd;

	printf("Task3:Start\n");

	for ( ; ; )
	{
		rcv_dtq(DTQID_TEST1, &msg);
		printf("Task3 rcv_dtq : %d\n", (int)msg);
	}

	printf("Task3:wup_tsk(1)\n");
	ercd = wup_tsk(1);
	printf("Task3:wup_tsk(1) ret = %d\n", ercd);

	printf("Task3:End\n");

	ext_tsk();
}



/* 周期ハンドラサンプル */
void CycHandler1(VP_INT exinf)
{
}


/* 割り込みハンドラサンプル */
void IntHndler1(VP_INT exinf)
{
	isig_tim();		/* タイムティックの供給 */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
