/* ------------------------------------------------------------------------ */
/*  HOS-V4 サンプル                                                         */
/*   メインルーチン                                                         */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __sample_h__
#define __sample_h__


/* 哲学者タスクとフォークセマフォのIDを固定値で指定 */
#define TSKID_PHILOSOPHER1	1
#define TSKID_PHILOSOPHER2	2
#define TSKID_PHILOSOPHER3	3
#define TSKID_PHILOSOPHER4	4
#define TSKID_PHILOSOPHER5	5
#define SEMID_FORK1			1
#define SEMID_FORK2			2
#define SEMID_FORK3			3
#define SEMID_FORK4			4
#define SEMID_FORK5			5


#ifdef __cplusplus
extern "C" {
#endif

void SampleInitialize(VP_INT exinf);	/* ATT_INI 登録の関数 */
void PhilosopherTask(VP_INT exinf);		/* 哲学者タスク */


#ifdef __cplusplus
}
#endif



#endif	/* __sample_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
