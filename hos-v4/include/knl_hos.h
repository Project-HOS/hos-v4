/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    カーネル HOS独自機能                                                  */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_knl_h__
#define __HOS_V4__knl_knl_h__



/* ------------------------------------------ */
/*                  定数定義                  */
/* ------------------------------------------ */

/* カーネルメモリ管理定数 */
#define MEMBLK_ALIGN	4			/* メモリアライメント */

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

/* カーネルシステム管理 */
extern STAT kernel_ctx_stat;				/* システムのコンテキスト状態 */


/* カーネルメモリ管理 */
extern T_KERNEL_MEM_BLK *kernel_mem_base;	/* カーネル用メモリ先頭ブロックのアドレス */



/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

/* カーネルシステム管理 */
ER      sta_hos(void);								/* カーネル動作開始 */


/* カーネル内部関数 */
#define kernel_get_run_tsk()	\
			(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mknl_get_run_tsk()))
													/* 実行中タスク取得(マクロ関数) */


/* コンフィギュレーター生成関数 */
void    kernel_cfg_init(void);						/* 変数の初期化 */
void    kernel_cfg_start(void);						/* 初期化関数呼び出し */


/* システムメモリ管理 */
void    kernel_ini_mem(void *p_base, SIZE size);	/* メモリ管理を初期化 */
VP      kernel_alc_mem(SIZE size);					/* メモリの割り当て */
void    kernel_fre_mem(VP ptr);						/* メモリの解放 */



#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_knl_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
