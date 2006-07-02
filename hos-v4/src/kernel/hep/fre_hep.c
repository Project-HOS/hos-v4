/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ� �������                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_hep.h"



/** ����β��� */
void kernel_fre_hep(
		T_KERNEL_HEPCB *pk_hepcb,
		VP             ptr)
{
	T_KERNEL_HEPBLK *mblk;
	T_KERNEL_HEPBLK *mblktmp;
	T_KERNEL_HEPBLK *mblknext;

	/* %jp{�ݥ����ϰϥ����å� */
	if ( ptr < (VP)pk_hepcb->base || ptr >= (VP)((UB*)pk_hepcb->base + pk_hepcb->heapsz) )
	{
		return;
	}

	/* %jp{����֥�å����֤���� */
	mblk = (T_KERNEL_HEPBLK *)((UB *)ptr - KERNEL_HEP_BLKSIZE);

	/* %jp{�ѥ�᡼���������å� */
	if ( mblk->flag != KERNEL_HEP_USING )	/* %jp{�������̵����� */
	{
		return;
	}

	/* %jp{�ե饰��̤���Ѥ�����} */
	mblk->flag = KERNEL_HEP_FREE;
	
	/* %jp{���Υ֥�å�������å�} */
	mblktmp = (T_KERNEL_HEPBLK *)((UB *)ptr + mblk->size);
	if ( mblktmp->flag == KERNEL_HEP_FREE )
	{
		/* %jp{���Υ֥�å���̤���Ѥʤ��礹��} */
		mblknext = (T_KERNEL_HEPBLK *)((UB *)mblktmp + mblktmp->size + KERNEL_HEP_BLKSIZE);
		mblknext->prev = mblk;
		mblk->size += mblktmp->size + KERNEL_HEP_BLKSIZE;
	}

	/* %jp{���Υ֥�å�������å�} */
	if ( mblk->prev != NULL )
	{
		mblktmp = mblk->prev;
		if ( mblktmp->flag == KERNEL_HEP_FREE )
		{
			/* %jp{���Υ֥�å���̤���Ѥʤ��礹��} */
			mblknext = (T_KERNEL_HEPBLK *)((UB *)mblk + mblk->size + KERNEL_HEP_BLKSIZE);
			mblknext->prev = mblktmp;
			mblktmp->size += mblk->size + KERNEL_HEP_BLKSIZE;
		}
	}
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */

