/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*   いわゆる哲学者の食事の問題                                             */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __sample_h__
#define __sample_h__


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
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
