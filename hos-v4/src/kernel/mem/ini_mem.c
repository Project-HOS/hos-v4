/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネルメモリ管理                                                    */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mem.h"



/* グローバル変数 */
T_KERNEL_MEM_BLK *kernel_mem_base = NULL;	/* カーネル用メモリ先頭ブロックのアドレス */
SIZE             kernel_mem_szie;			/* カーネル用メモリサイズ */


/* メモリ管理を初期化 */
void kernel_ini_mem(
		void *p_base,		/* 管理する領域の先頭アドレス */
		SIZE size)			/* 管理する領域のサイズ */
{
	T_KERNEL_MEM_BLK *mblklast;
	
	/* サイズのアライメントを調整 */
	size &= ~(MEMBLK_ALIGN - 1);
	
	/* サイズチェック */
	if ( size <= sizeof(T_KERNEL_MEM_BLK) )
	{
		return;
	}
	
	/* 設定保存 */
	kernel_mem_base = (T_KERNEL_MEM_BLK *)p_base;
	kernel_mem_szie = size;
	
	/* 終端位置に番人を設定 */
	mblklast = (T_KERNEL_MEM_BLK *)((UB *)p_base + size - MEMBLKSIZE);
	
	/* 全体を空き領域に設定 */
	kernel_mem_base->prev = NULL;
	kernel_mem_base->size = size - (MEMBLKSIZE * 2);
	kernel_mem_base->flag = MEMBLK_FREE;
	
	/* 終端の番人を利用中に設定 */
	mblklast->prev = NULL;
	mblklast->size = 0;
	mblklast->flag = MEMBLK_USING;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
