/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ� ����ҡ���                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_hep_h__
#define __HOS_V4__knl_hep_h__


#include "itron.h"


#define KERNEL_HEP_MEMALIGN		32			/* ���ꥢ�饤���� */
#define KERNEL_HEP_USING		0x1234		/* ������ */
#define KERNEL_HEP_FREE			0xabcd		/* ̤���� */



/** %jp{���������饤����} */
#define KERNEL_HEP_ALIGNED(size)	(((size) + KERNEL_HEP_MEMALIGN - 1) & ~(KERNEL_HEP_MEMALIGN - 1))


/** %jp{�ҡ��ץ���֥�å�} */
typedef struct kernel_t_hepblk
{
	struct kernel_t_hepblk* prev;	/* ���Υ֥�å� */
	SIZE   size;					/* �֥�å��Υ����� */
	INT    flag;					/* ������ե饰 */
} T_KERNEL_HEPBLK;


/** %jp{�ҡ�������֥�å�} */
typedef struct kernel_t_hepcb
{
	T_KERNEL_HEPBLK *base;			/* �����ͥ��ѥ�����Ƭ�֥�å��Υ��ɥ쥹 */
	SIZE            heapsz;			/* �����ͥ��ѥ��ꥵ���� */
} T_KERNEL_HEPCB;


/** %jp{�����ͥ��������֥�å�������} */
#define KERNEL_HEP_BLKSIZE			KERNEL_HEP_ALIGNED(sizeof(T_KERNEL_HEPBLK))


#ifdef __cplusplus
extern "C" {
#endif

void    kernel_cre_hep(T_KERNEL_HEPCB *pk_hepcb, void *p_base, SIZE size);	/* ����ҡ��פ����� */
#define kernel_del_hep(pk_hepcb)	do {} while(0)							/* ����ҡ��פ��� */
VP      kernel_alc_hep(T_KERNEL_HEPCB *pk_hepcb, SIZE size);				/* ����γ������ */
void    kernel_fre_hep(T_KERNEL_HEPCB *pk_hepcb, VP ptr);					/* ����β��� */
#define kernel_alg_hep(size)		KERNEL_HEP_ALIGNED(size)				/* ���ꥵ�����Υ��饤���Ȥ��碌�� */

#ifdef __cplusplus
}
#endif


#endif	/* __HOS_V4__knl_hep_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
