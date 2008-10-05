/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*   OS用タイマ                                                             */
/*                                                                          */
/*                                  Copyright (C) 1998-2007 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */

#ifndef __ostimer_h__
#define __ostimer_h__

#ifdef __cplusplus
extern "C" {
#endif

void	ostim_init( VP_INT exinf );		/* OS用タイマ初期化 */
void	ostim_hdr( VP_INT exinf );		/* OSタイマ用ハンドラ */

#ifdef __cplusplus
}
#endif

#endif	/* __ostimer_h__ */


/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2007 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
