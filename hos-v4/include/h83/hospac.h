/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    プロセッサ抽象化コンポーネント (日立 H8/300H 用)                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#ifndef __HOS_V4__H83__hospac_h__
#define __HOS_V4__H83__hospac_h__



#include "itron.h"



/* ------------------------------------------ */
/*                  定数定義                  */
/* ------------------------------------------ */

/* 割り込みマスク定義 */
#define H83_IMSK_I_BIT		0x80	/* 割り込みマスクビット */
#define H83_IMSK_UI_BIT		0x40	/* ユーザービット／割り込みマスクビット */

#define H83_IMSK_LEVEL0		0x00								/* プライオリティーレベル0/1を許可 */
#define H83_IMSK_LEVEL1		(H83_IMSK_I_BIT)					/* プライオリティーレベル1のみ許可 */
#define H83_IMSK_LEVEL2		(H83_IMSK_I_BIT | H83_IMSK_UI_BIT)	/* すべて禁止 */



/* ------------------------------------------ */
/*                   型定義                   */
/* ------------------------------------------ */

typedef UB	IMSK;		/* 割り込みマスク */


/* コンテキスト情報保存ブロック */
typedef struct t_hos_pac_ctxinf
{
	VP sp;
} T_HOSPAC_CTXINF;



/* ---------------------------------- */
/*        グローバル変数宣言          */
/* ---------------------------------- */

extern UB kernel_h83_imsk;		/* 割り込みマスク値 */
extern UB kernel_h83_ibmsk;		/* 割り込みベースマスク値 */



/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

void hospac_ini_sys(void);			/* システムの初期化 */

void hospac_dis_int(void);			/* 割り込み禁止 */
void hospac_ena_int(void);			/* 割り込み許可 */

void hospac_cre_ctx_asm(T_HOSPAC_CTXINF *pk_ctxinf,
					VP sp, FP task, VP_INT exinf);			/* 実行コンテキストの作成(アセンブラ用) */
#define hospac_cre_ctx(pk_ctxinf, exinf, task, stksz, stk)	\
	hospac_cre_ctx_asm(pk_ctxinf, ((VP)((UB *)(stk) + ((stksz) & 0xfffffffc))), task, exinf)
															/* アセンブラ側で都合がいいように引数を入れ替え */
#define hospac_del_ctx(pk_ctxinf)	do {} while (0)			/* 実行コンテキストの削除(不要) */
void hospac_swi_ctx(T_HOSPAC_CTXINF *pk_pre_ctxinf,
						T_HOSPAC_CTXINF *pk_nxt_ctxinf);	/* 実行コンテキストの切替 */
#define hospac_idle()	do {} while (0)						/* アイドル時の動作(何もしない) */


ER chg_imsk(IMSK imsk);				/* 割り込みマスクのベース値の変更 */
ER get_imsk(IMSK *p_imsk);			/* 割り込みマスクのベース値の参照 */

ER fchg_imsk(IMSK imsk);			/* 現在の割込みマスク値の強制変更 */
ER fget_imsk(IMSK *p_imsk);			/* 現在の割込みマスク値の強制参照 */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__H83__hospac_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
