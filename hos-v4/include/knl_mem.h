/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ� �������                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2003 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_mem_h__
#define __HOS_V4__knl_mem_h__


#include "knl_hos.h"
#include "knl_hep.h"



/* --------------------------------------- */
/*            �ޥ������                   */
/* --------------------------------------- */
/* ���������饤���� */
#define TSZ_ALIGNED(size)	(((size) + KERNEL_HEP_MEMALIGN - 1) & ~(KERNEL_HEP_MEMALIGN - 1))



/* ---------------------------------- */
/*        �����Х��ѿ����          */
/* ---------------------------------- */

/* �����ͥ������� */
extern T_KERNEL_HEPCB kernel_mem_hep;		/* �����ͥ��ѥ���ҡ��� */



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* �����ƥ������� */
void    kernel_ini_mem(void *p_base, SIZE size);	/* ������������� */
VP      kernel_alc_mem(SIZE size);					/* ����γ������ */
void    kernel_fre_mem(VP ptr);						/* ����β��� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_mem_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2003 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
