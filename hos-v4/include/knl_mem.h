/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネル メモリ管理                                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_mem_h__
#define __HOS_V4__knl_mem_h__


#include "knl_hos.h"


/* ------------------------------------------ */
/*                  定数定義                  */
/* ------------------------------------------ */

/* カーネルメモリ管理定数 */
#define MEMBLK_ALIGN	sizeof(VP)	/* メモリアライメント */

#define MEMBLK_USING	0x1234		/* 使用中 */
#define MEMBLK_FREE		0xabcd		/* 未使用 */



/* ------------------------------------------ */
/*                 型定義                     */
/* ------------------------------------------ */

/* カーネルメモリ管理ブロック */
typedef struct t_kernel_mem_blk
{
	struct t_kernel_mem_blk* prev;		/* 前のブロック */
	SIZE   size;						/* ブロックのサイズ */
	INT    flag;						/* 使用中フラグ */
} T_KERNEL_MEM_BLK;

/* カーネルメモリ管理ブロックサイズ */
#define MEMBLKSIZE	((sizeof(T_KERNEL_MEM_BLK) + MEMBLK_ALIGN - 1) & ~(MEMBLK_ALIGN - 1))



#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------- */
/*        グローバル変数宣言          */
/* ---------------------------------- */

/* カーネルメモリ管理 */
extern T_KERNEL_MEM_BLK *kernel_mem_base;	/* カーネル用メモリ先頭ブロックのアドレス */
extern SIZE             kernel_mem_szie;	/* カーネル用メモリサイズ */



/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

/* システムメモリ管理 */
void    kernel_ini_mem(void *p_base, SIZE size);	/* メモリ管理を初期化 */
VP      kernel_alc_mem(SIZE size);					/* メモリの割り当て */
void    kernel_fre_mem(VP ptr);						/* メモリの解放 */



#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_mem_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
