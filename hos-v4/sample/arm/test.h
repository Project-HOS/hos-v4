/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*   サンプルプログラム                                                     */
/*   メインルーチン                                                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __test_h__
#define __test_h__



#ifdef __cplusplus
extern "C" {
#endif

void TestStart(VP_INT exinf);	/* ATT_INI 登録の関数 */

void Task1(VP_INT exinf);		/* サンプルタスク1 */
void Task2(VP_INT exinf);		/* サンプルタスク2 */
void Task3(VP_INT exinf);		/* サンプルタスク3 */

void CycHandler1(VP_INT exinf);	/* 周期ハンドラサンプル */

void IntHndler1(VP_INT exinf);	/* 割り込みハンドラサンプル */

#ifdef __cplusplus
}
#endif



#endif	/* __test_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
