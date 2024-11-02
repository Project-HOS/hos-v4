/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネル HOS 固有部分                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_hos_h__
#define __HOS_V4__knl_hos_h__


#include <stddef.h>
#include "itron.h"
#include "mknl.h"
#include "hoserchk.h"


/* ------------------------------------------ */
/*                マクロ定義                  */
/* ------------------------------------------ */

/* C++ の static_cast 演算子と同じ効果のマクロ */
#define KERNEL_STATIC_CAST(s, m, p)	((s *)((B*)(p))-offsetof(s, m))	/* メンバのアドレスから構造体のアドレス算出 */

/* C言語の構造体を用いてポリモーフィズムを実現する際に */
/* 構造体メンバのポインタから、構造体先頭のポインタを  */
/* 算出することが必須となる。上記は C++ 言語では       */
/* dynamic_cast や static_cast 演算子で安全に行えるが  */
/* C言語ではある程度強引に実装する必要がある。         */



/* ---------------------------------- */
/*        グローバル変数宣言          */
/* ---------------------------------- */

/* カーネルシステム管理 */
extern STAT kernel_ctx_stat;				/* システムのコンテキスト状態 */



/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* カーネルシステム管理 */
ER      sta_hos(void);								/* カーネル動作開始 */


/* カーネル内部関数 */
#define kernel_get_run_tsk()	\
			(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mknl_get_run_tsk()))
													/* 実行中タスク取得(マクロ関数) */


/* コンフィギュレーター生成関数 */
void    kernel_cfg_init(void);						/* 変数の初期化 */
void    kernel_cfg_start(void);						/* 初期化関数呼び出し */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_hos_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
