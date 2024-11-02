/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*   いわゆる哲学者の食事の問題                                             */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include <stdio.h>
#include <stdlib.h>
#include "kernel.h"
#include "kernel_id.h"
#include "user_id.h"
#include "sh7045.h"
#include "sci.h"
#include "sample.h"


#define SCIID			ID_SCI1


#define LEFT_FORK(id)	((id) % 5 + 1)
#define RIGHT_FORK(id)	(id)



void SetLed(INT id);		/* 対応のLED点灯 */
void ResetLed(INT id);		/* 対応LDEの消灯 */

int led = 0;

/* メイン関数 */
int main()
{
	/* I/O の初期化 */
	*SH_PEIOR   = 0x00ff;
	*SH_PEDR    = 0;
	*SH_PACRL2 |= 0x0100;
	*SH_PEDR    = 0xff;
	
	/* HOS-V4 の開始 */
	sta_hos();
	
	return 0;
}


/* ATT_INI 登録の関数 */
void SampleInitialize(VP_INT exinf)
{
	/* タスク起動 */
	act_tsk(TSKID_PHILOSOPHER1);
	act_tsk(TSKID_PHILOSOPHER1);
	act_tsk(TSKID_PHILOSOPHER1);
	act_tsk(TSKID_PHILOSOPHER1);
//	act_tsk(TSKID_PHILOSOPHER1);
}


/* 哲学者タスク */
void PhilosopherTask(VP_INT exinf)
{
	INT id;
	INT i;
	
	*SH_PEDR = ~led;
	led++;
	ext_tsk();
	
	*SH_PEDR = 0xaaaa;
	for ( ; ; )
		;
	
	id = (INT)exinf;
	
	/* 超お馬鹿アルゴリズム */
	for ( ; ; )
	{
		/* 適当な時間悩んでみる */
		for ( i = rand() % 10 + 5; i > 0; i-- )
		{
			/* 点滅させる */
			SetLed(id);
			dly_tsk(100);
			ResetLed(id);
			dly_tsk(100);
		}
		
		/* 左右のフォークを取る */
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
		SetLed(id);			/* 点灯させる */
		dly_tsk(1000);
		ResetLed(id);
		
		/* フォークを放す */
		sig_sem(LEFT_FORK(id));
		sig_sem(RIGHT_FORK(id));
	}
}


/* 対応のLED点灯 */
void SetLed(INT id)
{
	wai_sem(SEMID_SYSCS);
	*SH_PEDR &= ~(0x01 << (id - 1));
	sig_sem(SEMID_SYSCS);
}


/* 対応LDEの消灯 */
void ResetLed(INT id)
{
	wai_sem(SEMID_SYSCS);
	*SH_PEDR |= (0x01 << (id - 1));
	sig_sem(SEMID_SYSCS);
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
