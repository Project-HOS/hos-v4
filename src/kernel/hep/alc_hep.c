/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネル メモリ管理                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include "knl_hep.h"


/* メモリの割り当て */
VP kernel_alc_hep(
		T_KERNEL_HEPCB *pk_hepcb,
		SIZE           size)
{
	T_KERNEL_HEPBLK *mblk;
	T_KERNEL_HEPBLK *mblk_next;
	T_KERNEL_HEPBLK *mblk_next2;
	
	/* ヒープの存在チェック */
	if ( pk_hepcb->base == NULL )
	{
		return NULL;
	}
	
	/* サイズのアライメントを調整} */
	size = KERNEL_HEP_ALIGNED(size);
	
	/* 空き領域を検索 */
	mblk = pk_hepcb->base;
	while ( mblk->size != 0 )
	{
		if ( mblk->flag == KERNEL_HEP_FREE && mblk->size >= size )
		{
			/* 十分な容量があったら */
			if ( mblk->size - size > KERNEL_HEP_BLKSIZE + KERNEL_HEP_MEMALIGN )
			{
				/* ブロックを分割する */
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
		
		/* 次のブロックへ進む */
		mblk = (T_KERNEL_HEPBLK *)((UB *)mblk + mblk->size + KERNEL_HEP_BLKSIZE);
	}

	return NULL;	/* 空きが無い */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */

