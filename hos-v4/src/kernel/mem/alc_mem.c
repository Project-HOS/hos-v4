/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネルメモリ管理                                                    */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include "knl_mem.h"



/* メモリの割り当て */
VP kernel_alc_mem(
		SIZE size)		/* 取得する領域のサイズ */
{
	T_KERNEL_MEM_BLK *mblk;
	T_KERNEL_MEM_BLK *mblk_next;
	
	/* ヒープの存在チェック */
	if ( kernel_mem_base == NULL )
	{
		return NULL;
	}
	
	/* サイズのアライメントを調整 */
	size = (size + MEMBLK_ALIGN - 1) & ~(MEMBLK_ALIGN - 1);
	
	/* 空き領域を検索 */
	mblk = kernel_mem_base;
	while ( mblk->size != 0 )
	{
		if ( mblk->flag == MEMBLK_FREE && mblk->size >= size )
		{
			/* 十分な容量があったら */
			if ( mblk->size - size > MEMBLKSIZE + MEMBLK_ALIGN )
			{
				/* ブロックを分割する */
				mblk_next = (T_KERNEL_MEM_BLK *)((UB *)mblk + MEMBLKSIZE + size);
				mblk_next->prev = mblk;
				mblk_next->size = mblk->size - size - MEMBLKSIZE;
				mblk_next->flag = MEMBLK_FREE;
				mblk->size      = size;
			}
			mblk->flag = MEMBLK_USING;
			
			return (VP)((UB *)mblk + MEMBLKSIZE);
		}
		
		/* 次のブロックへ進む */
		mblk = (T_KERNEL_MEM_BLK *)((UB *)mblk + mblk->size + MEMBLKSIZE);
	}

	return NULL;	/* 空きが無い */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
