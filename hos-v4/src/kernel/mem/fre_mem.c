/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ�������                                                    */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mem.h"



/* ����β��� */
void kernel_fre_mem(VP ptr)
{
	T_KERNEL_MEM_BLK *mblk;
	T_KERNEL_MEM_BLK *mblktmp;
	T_KERNEL_MEM_BLK *mblknext;

	/* �ݥ����ϰϥ����å� */
	if ( ptr < (VP)kernel_mem_base || ptr >= (VP)((UB*)kernel_mem_base + kernel_mem_size) )
	{
		return;
	}

	/* ����֥�å����֤���� */
	mblk = (T_KERNEL_MEM_BLK *)((UB *)ptr - MEMBLKSIZE);

	/* �ѥ�᡼���������å� */
#ifdef HOS_ERCHK_E_PAR
	if ( mblk->flag != MEMBLK_USING )	/* �������̵����� */
	{
		return;
	}
#endif

	/* �ե饰��̤���Ѥ����� */
	mblk->flag = MEMBLK_FREE;
	
	/* ���Υ֥�å�������å� */
	mblktmp = (T_KERNEL_MEM_BLK *)((UB *)ptr + mblk->size);
	if ( mblktmp->flag == MEMBLK_FREE )
	{
		/* ���Υ֥�å���̤���Ѥʤ��礹�� */
		mblknext = (T_KERNEL_MEM_BLK *)((UB *)mblktmp + mblktmp->size + MEMBLKSIZE);
		mblknext->prev = mblk;
		mblk->size += mblktmp->size + MEMBLKSIZE;
	}

	/* ���Υ֥�å�������å� */
	if ( mblk->prev != NULL )
	{
		mblktmp = mblk->prev;
		if ( mblktmp->flag == MEMBLK_FREE )
		{
			/* ���Υ֥�å���̤���Ѥʤ��礹�� */
			mblknext = (T_KERNEL_MEM_BLK *)((UB *)mblk + mblk->size + MEMBLKSIZE);
			mblknext->prev = mblktmp;
			mblktmp->size += mblk->size + MEMBLKSIZE;
		}
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
