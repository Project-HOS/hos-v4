/*******************************************************************************
 * Hyper Operating System V4  サンプルプログラム
 *
 *                                      Copyright (C) 1998-2007 by Project HOS
 *                                      http://sourceforge.jp/projects/hos/
 *******************************************************************************/
#ifndef __SAMPLE_H__
#define __SAMPLE_H__

void
sample_init (VP_INT exinf);

void
sample_task_1 (VP_INT exinf);

void
sample_task_2 (VP_INT exinf);

void
sample_print (int no);

void
sample_cycle_handler (VP_INT exinf);

#endif /* __SAMPLE_H__ */
