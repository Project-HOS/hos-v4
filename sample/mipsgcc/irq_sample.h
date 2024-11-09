/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2008 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */

#ifndef __irq_sample_h__
#define __irq_sample_h__

#ifdef __cplusplus
extern "C" {
#endif

void int2_init(VP_INT exinf);
void int2_main(VP_INT exinf);

extern	int	flag_tc0;

#ifdef __cplusplus
}
#endif

#endif	/* __irq_sample_h__ */


/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2008 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
