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


/* ------------------------------------------ */
/*                  ������                  */
/* ------------------------------------------ */

/* �����ͥ���������� */
#define MEMBLK_ALIGN	sizeof(VP)	/* ���ꥢ�饤���� */

#define MEMBLK_USING	0x1234		/* ������ */
#define MEMBLK_FREE		0xabcd		/* ̤���� */



/* --------------------------------------- */
/*            �ޥ������                   */
/* --------------------------------------- */
/* ���������饤���� */
#define TSZ_ALIGNED(size)	(((size) + MEMBLK_ALIGN - 1) & ~(MEMBLK_ALIGN - 1))


/* ------------------------------------------ */
/*                 �����                     */
/* ------------------------------------------ */

/* �����ͥ��������֥�å� */
typedef struct t_kernel_mem_blk
{
	struct t_kernel_mem_blk* prev;		/* ���Υ֥�å� */
	SIZE   size;						/* �֥�å��Υ����� */
	INT    flag;						/* ������ե饰 */
} T_KERNEL_MEM_BLK;

/* �����ͥ��������֥�å������� */
#define MEMBLKSIZE	TSZ_ALIGNED(sizeof(T_KERNEL_MEM_BLK))



/* ---------------------------------- */
/*        �����Х��ѿ����          */
/* ---------------------------------- */

/* �����ͥ������� */
extern T_KERNEL_MEM_BLK *kernel_mem_base;	/* �����ͥ��ѥ�����Ƭ�֥�å��Υ��ɥ쥹 */
extern SIZE             kernel_mem_size;	/* �����ͥ��ѥ��ꥵ���� */



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
