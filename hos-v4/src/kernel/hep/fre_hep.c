/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネル メモリ管理                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_hep.h"



/** メモリの解放 */
void kernel_fre_hep(
		T_KERNEL_HEPCB *pk_hepcb,
		VP             ptr)
{
	T_KERNEL_HEPBLK *mblk;
	T_KERNEL_HEPBLK *mblktmp;
	T_KERNEL_HEPBLK *mblknext;

	/* %jp{ポインタ範囲チェック */
	if ( ptr < (VP)pk_hepcb->base || ptr >= (VP)((UB*)pk_hepcb->base + pk_hepcb->heapsz) )
	{
		return;
	}

	/* %jp{メモリブロック位置を取得 */
	mblk = (T_KERNEL_HEPBLK *)((UB *)ptr - KERNEL_HEP_BLKSIZE);

	/* %jp{パラメーターチェック */
	if ( mblk->flag != KERNEL_HEP_USING )	/* %jp{使用中で無ければ */
	{
		return;
	}

	/* %jp{フラグを未使用に設定} */
	mblk->flag = KERNEL_HEP_FREE;
	
	/* %jp{次のブロックをチェック} */
	mblktmp = (T_KERNEL_HEPBLK *)((UB *)ptr + mblk->size);
	if ( mblktmp->flag == KERNEL_HEP_FREE )
	{
		/* %jp{次のブロックが未使用なら結合する} */
		mblknext = (T_KERNEL_HEPBLK *)((UB *)mblktmp + mblktmp->size + KERNEL_HEP_BLKSIZE);
		mblknext->prev = mblk;
		mblk->size += mblktmp->size + KERNEL_HEP_BLKSIZE;
	}

	/* %jp{前のブロックをチェック} */
	if ( mblk->prev != NULL )
	{
		mblktmp = mblk->prev;
		if ( mblktmp->flag == KERNEL_HEP_FREE )
		{
			/* %jp{前のブロックが未使用なら結合する} */
			mblknext = (T_KERNEL_HEPBLK *)((UB *)mblk + mblk->size + KERNEL_HEP_BLKSIZE);
			mblknext->prev = mblktmp;
			mblktmp->size += mblk->size + KERNEL_HEP_BLKSIZE;
		}
	}
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */

