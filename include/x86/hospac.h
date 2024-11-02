/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    プロセッサ抽象化コンポーネント (x86 用)                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#ifndef __HOS_V4__x86__hospac_h__
#define __HOS_V4__x86__hospac_h__



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

#define hospac_ini_sys()							/* プロセッサ抽象化コンポーネントの初期化 */
void hospac_dis_int(void);							/* 割り込み禁止 */
void hospac_ena_int(void);							/* 割り込み許可 */
void hospac_cre_ctx_asm(T_HOSPAC_CTXINF *pk_ctxinf,
					VP sp, FP task, VP_INT exinf);	/* 実行コンテキストの作成(アセンブラ用) */
#define hospac_cre_ctx(pk_ctxinf, exinf, task, stksz, stk) \
	hospac_cre_ctx_asm(pk_ctxinf, (VP)((UB *)(stk) + (stksz)), task, exinf);
													/* アセンブラ側で都合がいいように引数を入れ替え */
#define hospac_del_ctx(pk_ctxinf)					/* 実行コンテキストの削除 */
void hospac_swi_ctx(T_HOSPAC_CTXINF *pk_pre_ctxinf,
						T_HOSPAC_CTXINF *pk_nxt_ctxinf);	/* 実行コンテキストの切替 */

#define hospac_idle()				/* アイドル時処理 */

void  hos_arm_ini_int(void);		/* 割り込み処理の初期化（ユーザー作成関数） */ 
INTNO hos_arm_sta_irq(void);		/* IRQ割り込み処理開始（ユーザー作成関数） */
void  hos_arm_end_irq(void);		/* IRQ割り込み処理終了（ユーザー作成関数） */
INTNO hos_arm_sta_fiq(void);		/* FIQ割り込み処理開始（ユーザー作成関数） */
void  hos_arm_end_fiq(void);		/* FIQ割り込み処理終了（ユーザー作成関数） */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__x86__hospac_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
