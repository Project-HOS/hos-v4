/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    プロセッサ抽象化コンポーネント (MIPS用)                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2008 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#ifndef __HOS_V4__MIPS__hospac_h__
#define __HOS_V4__MIPS__hospac_h__

/* ------------------------------------------ */
/*                   型定義                   */
/* ------------------------------------------ */

/* コンテキスト情報保存ブロック */
typedef struct t_hos_pac_ctxinf
{
	VP sp;			/* スタックポインタ保存領域 */
} T_HOSPAC_CTXINF;



/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

#define hospac_ini_sys()								/* プロセッサ抽象化コンポーネントの初期化 */
void hospac_dis_int(void);								/* 割り込み禁止 */
void hospac_ena_int(void);								/* 割り込み許可 */

void hospac_cre_ctx_asm(T_HOSPAC_CTXINF *pk_ctxinf, VP_INT exinf, FP task, VP stk);
														/* 実行コンテキストの作成(アセンブラ用) */

#define hospac_cre_ctx(pk_ctxinf, exinf, task, stksz, stk)	\
		hospac_cre_ctx_asm(pk_ctxinf, exinf, task, stk+stksz)	/* 実行コンテキストの作成 */

#define hospac_del_ctx(pk_ctxinf)						/* 実行コンテキストの削除 */
void hospac_swi_ctx(T_HOSPAC_CTXINF *pk_pre_ctxinf,
					T_HOSPAC_CTXINF *pk_nxt_ctxinf);	/* 実行コンテキストの切替 */
#define hospac_idle()   /* アイドル時処理 */

#ifdef __cplusplus
}
#endif

#endif	/* __HOS_V4__MIPS__hospac_h__ */

/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2008 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
