/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#ifndef __sample_h
#define __sample_h
#include "itron.h"
/*
 *  関数宣言
 */
void Initialize(VP_INT exinf);
void Task1(VP_INT exinf);
/*
 *  例外ハンドラ関数宣言
 */
void exp_hdr_zero_div(VP_INT exinf);
void exp_hdr_hwdebug(VP_INT exinf);
void exp_hdr_nmi(VP_INT exinf);
void exp_hdr_debug(VP_INT exinf);
void exp_hdr_overflow(VP_INT exinf);
void exp_hdr_bounds(VP_INT exinf);
void exp_hdr_invalid_op(VP_INT exinf);
void exp_hdr_device_not_available(VP_INT exinf);
void exp_hdr_double_fault(VP_INT exinf);
void exp_hdr_coprocessor_segment_overrun(VP_INT exinf);
void exp_hdr_invalid_TSS(VP_INT exinf);
void exp_hdr_segment_not_present(VP_INT exinf);
void exp_hdr_stack_segment(VP_INT exinf);
void exp_hdr_genprot(VP_INT exinf);
void exp_hdr_pg_fault(VP_INT exinf);
void exp_hdr_copro_fault(VP_INT exinf);
void exp_hdr_alignment(VP_INT exinf);
void exp_hdr_machine_check(VP_INT exinf);
void exp_hdr(VP_INT exinf);
#endif  /*  __sample_h  */
/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
