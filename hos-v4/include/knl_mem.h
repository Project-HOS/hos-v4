/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネル メモリ管理                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2003 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_mem_h__
#define __HOS_V4__knl_mem_h__


#include "knl_hos.h"
#include "knl_hep.h"



/* --------------------------------------- */
/*            マクロ定義                   */
/* --------------------------------------- */
/* サイズアライメント */
#define TSZ_ALIGNED(size)	(((size) + KERNEL_HEP_MEMALIGN - 1) & ~(KERNEL_HEP_MEMALIGN - 1))



/* ---------------------------------- */
/*        グローバル変数宣言          */
/* ---------------------------------- */

/* カーネルメモリ管理 */
extern T_KERNEL_HEPCB kernel_mem_hep;		/* カーネル用メモリヒープ */



/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* システムメモリ管理 */
void    kernel_ini_mem(void *p_base, SIZE size);	/* メモリ管理を初期化 */
VP      kernel_alc_mem(SIZE size);					/* メモリの割り当て */
void    kernel_fre_mem(VP ptr);						/* メモリの解放 */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_mem_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2003 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
