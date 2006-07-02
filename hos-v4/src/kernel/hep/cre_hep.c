/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネル メモリ管理                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include "knl_hep.h"



/* メモリヒープを生成 */
void kernel_cre_hep(
		T_KERNEL_HEPCB *pk_hepcb,
		void           *p_base,
		SIZE           size)
{
	T_KERNEL_HEPBLK *blk_last;
	
	/* サイズのアライメントを調整 */
	size &= ~(KERNEL_HEP_MEMALIGN - 1);

	/* サイズチェック */
	if ( size <= sizeof(T_KERNEL_HEPBLK) )
	{
		pk_hepcb->base = NULL;
		return;
	}

	/* 設定保存 */
	pk_hepcb->base   = (T_KERNEL_HEPBLK *)p_base;
	pk_hepcb->heapsz = size;
	
	/* 終端位置に番人を設定 */
	blk_last = (T_KERNEL_HEPBLK *)((UB *)p_base + size - KERNEL_HEP_BLKSIZE);
	
	/* 全体を空き領域に設定 */
	pk_hepcb->base->prev = NULL;
	pk_hepcb->base->size = size - (KERNEL_HEP_BLKSIZE * 2);
	pk_hepcb->base->flag = KERNEL_HEP_FREE;
	
	/* 終端の番人を利用中に設定 */
	blk_last->prev = NULL;
	blk_last->size = 0;
	blk_last->flag = KERNEL_HEP_USING;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */

