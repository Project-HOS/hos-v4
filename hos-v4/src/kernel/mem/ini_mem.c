/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ�������                                                    */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mem.h"



/* �����Х��ѿ� */
T_KERNEL_MEM_BLK *kernel_mem_base = NULL;	/* �����ͥ��ѥ�����Ƭ�֥�å��Υ��ɥ쥹 */
SIZE             kernel_mem_szie;			/* �����ͥ��ѥ��ꥵ���� */


/* ������������� */
void kernel_ini_mem(
		void *p_base,		/* ���������ΰ����Ƭ���ɥ쥹 */
		SIZE size)			/* ���������ΰ�Υ����� */
{
	T_KERNEL_MEM_BLK *mblklast;
	
	/* �������Υ��饤���Ȥ�Ĵ�� */
	size &= ~(MEMBLK_ALIGN - 1);
	
	/* �����������å� */
	if ( size <= sizeof(T_KERNEL_MEM_BLK) )
	{
		return;
	}
	
	/* ������¸ */
	kernel_mem_base = (T_KERNEL_MEM_BLK *)p_base;
	kernel_mem_szie = size;
	
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
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
