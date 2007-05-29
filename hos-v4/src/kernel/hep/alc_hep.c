/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ� �������                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include "knl_hep.h"


/* ����γ������ */
VP kernel_alc_hep(
		T_KERNEL_HEPCB *pk_hepcb,
		SIZE           size)
{
	T_KERNEL_HEPBLK *mblk;
	T_KERNEL_HEPBLK *mblk_next;
	T_KERNEL_HEPBLK *mblk_next2;
	
	/* �ҡ��פ�¸�ߥ����å� */
	if ( pk_hepcb->base == NULL )
	{
		return NULL;
	}
	
	/* �������Υ��饤���Ȥ�Ĵ��} */
	size = KERNEL_HEP_ALIGNED(size);
	
	/* �����ΰ�򸡺� */
	mblk = pk_hepcb->base;
	while ( mblk->size != 0 )
	{
		if ( mblk->flag == KERNEL_HEP_FREE && mblk->size >= size )
		{
			/* ��ʬ�����̤����ä��� */
			if ( mblk->size - size > KERNEL_HEP_BLKSIZE + KERNEL_HEP_MEMALIGN )
			{
				/* �֥�å���ʬ�䤹�� */
				mblk_next  = (T_KERNEL_HEPBLK *)((UB *)mblk + KERNEL_HEP_BLKSIZE + size);
				mblk_next2 = (T_KERNEL_HEPBLK *)((UB *)mblk + KERNEL_HEP_BLKSIZE + mblk->size);
				mblk_next->prev  = mblk;
				mblk_next->size  = mblk->size - size - KERNEL_HEP_BLKSIZE;
				mblk_next->flag  = KERNEL_HEP_FREE;
				mblk_next2->prev = mblk_next;
				mblk->size       = size;
			}
			mblk->flag = KERNEL_HEP_USING;
			
			return (VP)((UB *)mblk + KERNEL_HEP_BLKSIZE);
		}
		
		/* ���Υ֥�å��ؿʤ� */
		mblk = (T_KERNEL_HEPBLK *)((UB *)mblk + mblk->size + KERNEL_HEP_BLKSIZE);
	}

	return NULL;	/* ������̵�� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */

