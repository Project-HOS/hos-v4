/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �����ͥ�������                                                    */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#include "kernel.h"



/* ����γ������ */
VP kernel_alc_mem(
		SIZE size)		/* ���������ΰ�Υ����� */
{
	T_KERNEL_MEM_BLK *mblk;
	T_KERNEL_MEM_BLK *mblk_next;

	/* �������Υ��饤���Ȥ�Ĵ�� */
	size = (size + MEMBLK_ALIGN - 1) & ~(MEMBLK_ALIGN - 1);
	
	/* �����ΰ�򸡺� */
	mblk = kernel_mem_base;
	while ( mblk->size != 0 )
	{
		if ( mblk->flag == MEMBLK_FREE && mblk->size >= size )
		{
			/* ��ʬ�����̤����ä��� */
			if ( mblk->size - size > MEMBLKSIZE + MEMBLK_ALIGN )
			{
				/* �֥�å���ʬ�䤹�� */
				mblk_next = (T_KERNEL_MEM_BLK *)((UB *)mblk + size);
				mblk_next->prev = mblk;
				mblk_next->size = mblk->size - size - MEMBLKSIZE;
				mblk_next->flag = MEMBLK_FREE;
				mblk->size      = size;
			}
			mblk->flag = MEMBLK_USING;
			
			return (VP)((UB *)mblk + MEMBLKSIZE);
		}
		
		/* ���Υ֥�å��ؿʤ� */
		mblk = (T_KERNEL_MEM_BLK *)((UB *)mblk + mblk->size + MEMBLKSIZE);
	}

	return NULL;	/* ������̵�� */
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
