/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ� �������                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include "knl_hep.h"



/* ����ҡ��פ����� */
void kernel_cre_hep(
		T_KERNEL_HEPCB *pk_hepcb,
		void           *p_base,
		SIZE           size)
{
	T_KERNEL_HEPBLK *blk_last;
	
	/* �������Υ��饤���Ȥ�Ĵ�� */
	size &= ~(KERNEL_HEP_MEMALIGN - 1);

	/* �����������å� */
	if ( size <= sizeof(T_KERNEL_HEPBLK) )
	{
		pk_hepcb->base = NULL;
		return;
	}

	/* ������¸ */
	pk_hepcb->base   = (T_KERNEL_HEPBLK *)p_base;
	pk_hepcb->heapsz = size;
	
	/* ��ü���֤��ֿͤ����� */
	blk_last = (T_KERNEL_HEPBLK *)((UB *)p_base + size - KERNEL_HEP_BLKSIZE);
	
	/* ���Τ�����ΰ������ */
	pk_hepcb->base->prev = NULL;
	pk_hepcb->base->size = size - (KERNEL_HEP_BLKSIZE * 2);
	pk_hepcb->base->flag = KERNEL_HEP_FREE;
	
	/* ��ü���ֿͤ������������ */
	blk_last->prev = NULL;
	blk_last->size = 0;
	blk_last->flag = KERNEL_HEP_USING;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */

