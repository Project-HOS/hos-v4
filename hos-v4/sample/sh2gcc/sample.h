/* ------------------------------------------------------------------------ */
/*  HOS-V4 サンプル                                                         */
/*   メインルーチン                                                         */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
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
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
