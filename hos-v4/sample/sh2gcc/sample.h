/* ------------------------------------------------------------------------ */
/*  HOS-V4 サンプル                                                         */
/*   メインルーチン                                                         */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __Ryuz__test_h__
#define __Ryuz__test_h__



#ifdef __cplusplus
extern "C" {
#endif

void TestStart(VP_INT exinf);	/* ATT_INI 登録の関数 */

void Task1(VP_INT exinf);		/* サンプルタスク1 */
void Task2(VP_INT exinf);		/* サンプルタスク2 */
void Task3(VP_INT exinf);		/* サンプルタスク3 */

void CycHandler1(VP_INT exinf);	/* 周期ハンドラサンプル */

void ostim_hdr(VP_INT exinf);	/* OSタイマ用ハンドラ */

#ifdef __cplusplus
}
#endif



#endif	/* __Ryuz__test_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
