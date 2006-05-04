/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネルメモリ管理                                                    */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mem.h"



/* メモリの解放 */
void kernel_fre_mem(VP ptr)
{
	T_KERNEL_MEM_BLK *mblk;
	T_KERNEL_MEM_BLK *mblktmp;
	T_KERNEL_MEM_BLK *mblknext;

	/* ポインタ範囲チェック */
	if ( ptr < (VP)kernel_mem_base || ptr >= (VP)((UB*)kernel_mem_base + kernel_mem_size) )
	{
		return;
	}

	/* メモリブロック位置を取得 */
	mblk = (T_KERNEL_MEM_BLK *)((UB *)ptr - MEMBLKSIZE);

	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_PAR
	if ( mblk->flag != MEMBLK_USING )	/* 使用中で無ければ */
	{
		return;
	}
#endif

	/* フラグを未使用に設定 */
	mblk->flag = MEMBLK_FREE;
	
	/* 次のブロックをチェック */
	mblktmp = (T_KERNEL_MEM_BLK *)((UB *)ptr + mblk->size);
	if ( mblktmp->flag == MEMBLK_FREE )
	{
		/* 次のブロックが未使用なら結合する */
		mblknext = (T_KERNEL_MEM_BLK *)((UB *)mblktmp + mblktmp->size + MEMBLKSIZE);
		mblknext->prev = mblk;
		mblk->size += mblktmp->size + MEMBLKSIZE;
	}

	/* 前のブロックをチェック */
	if ( mblk->prev != NULL )
	{
		mblktmp = mblk->prev;
		if ( mblktmp->flag == MEMBLK_FREE )
		{
			/* 前のブロックが未使用なら結合する */
			mblknext = (T_KERNEL_MEM_BLK *)((UB *)mblk + mblk->size + MEMBLKSIZE);
			mblknext->prev = mblktmp;
			mblktmp->size += mblk->size + MEMBLKSIZE;
		}
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
