/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*   いわゆる哲学者の食事の問題                                             */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include <stdio.h>
#include "kernel.h"
#include "kernel_id.h"
#include "sample.h"



#define LEFT_FORK(id)	((id) % 5 + 1)
#define RIGHT_FORK(id)	(id)


static char status[] = "TTTTT\n";



/* メイン関数 */
int main()
{
	/* HOS-V4 の開始 */
	sta_hos();
	
	return 0;
}


/* ATT_INI 登録の関数 */
void SampleInitialize(VP_INT exinf)
{
	/* タスク起動 */
	act_tsk(TSKID_PHILOSOPHER1);
	act_tsk(TSKID_PHILOSOPHER2);
	act_tsk(TSKID_PHILOSOPHER3);
	act_tsk(TSKID_PHILOSOPHER4);
	act_tsk(TSKID_PHILOSOPHER5);
}


/* 哲学者タスク */
void PhilosopherTask(VP_INT exinf)
{
	INT id;

	id = (INT)exinf;

	/* 超ばかアルゴリズム */
	for ( ; ; )
	{
		/* 適当な時間悩んでみる */
		status[id -1] = 'T';
		printf(status);
		dly_tsk((rand() % 100) * 10 + 500);

		/* 左右のフォークを取るまで粘る */
		status[id -1] = 'W';
		printf(status);
		for ( ; ; )
		{
			wai_sem(LEFT_FORK(id));
			if ( pol_sem(RIGHT_FORK(id)) == E_OK )
			{
				break;
			}
			sig_sem(LEFT_FORK(id));
			dly_tsk((rand() % 10 + 1) * 10);	/* 適当に待つ */
		}

		/* お食事中 */
		status[id -1] = 'E';
		printf(status);
		dly_tsk(1000);

		/* フォークを放す */
		sig_sem(LEFT_FORK(id));
		sig_sem(RIGHT_FORK(id));
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
