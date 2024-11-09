/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*   タイムティック提供                                                     */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */

#ifndef __ostimer_h__
#define __ostimer_h__



#ifdef __cplusplus
extern "C" {
#endif

void OsTimer_Initialize(VP_INT exinf);	/* 初期化 */
void OsTimer_Handler(VP_INT exinf);		/* タイマ割り込みハンドラ */

#ifdef __cplusplus
}
#endif



#endif	/* __ostimer_h__ */



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
