/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �����ͥ�������                                                    */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* �������Х��ѿ� */
T_KERNEL_MEM_BLK *kernel_mem_base;	/* �����ͥ��ѥ�����Ƭ�֥��å��Υ��ɥ쥹 */



/* ������������� */
void kernel_ini_mem(
		void *p_base,		/* ���������ΰ����Ƭ���ɥ쥹 */
		SIZE size)			/* ���������ΰ�Υ����� */
{
	T_KERNEL_MEM_BLK *mblklast;

	/* �������Υ��饤���Ȥ�Ĵ�� */
	size &= ~(MEMBLK_ALIGN - 1);

	/* ��Ƭ�������� */
	kernel_mem_base = (T_KERNEL_MEM_BLK *)p_base;

	/* ��ü���֤��ֿͤ����� */
	mblklast = (T_KERNEL_MEM_BLK *)((UB *)p_base + size - MEMBLKSIZE);
	
	/* ���Τ�����ΰ������ */
	kernel_mem_base->prev = NULL;
	kernel_mem_base->size = size - (MEMBLKSIZE * 2);
	kernel_mem_base->flag = MEMBLK_FREE;
	
	/* ��ü���ֿͤ������������ */
	mblklast->prev = NULL;
	mblklast->size = 0;
	mblklast->flag = MEMBLK_USING;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */