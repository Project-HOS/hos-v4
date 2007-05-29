/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネルメモリ管理                                                    */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mem.h"



/* グローバル変数 */
T_KERNEL_HEPCB kernel_mem_hep;		/* カーネル用メモリヒープ */


/* メモリ管理を初期化 */
void kernel_ini_mem(
		void *p_base,		/* 管理する領域の先頭アドレス */
		SIZE size)			/* 管理する領域のサイズ */
{
	kernel_cre_hep(&kernel_mem_hep, p_base, size);
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
