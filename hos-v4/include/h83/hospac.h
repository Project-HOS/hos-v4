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
#define H83_IMSK_I_BIT		0x80		/* 割り込みマスクビット */
#define H83_IMSK_UI_BIT		0x40		/* ユーザービット／割り込みマスクビット */

#define H38_IMSK_LVL0		


/* ------------------------------------------ */
/*                   型定義                   */
/* ------------------------------------------ */

/* コンテキスト情報保存ブロック */
typedef struct t_hos_pac_ctxinf
{
	VP sp;
} T_HOSPAC_CTXINF;


typedef UB	IMSK;		/* 割り込みマスク */



#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------- */
/*        グローバル変数宣言          */
/* ---------------------------------- */

extern UB kernel_h83_imsk;		/* 割り込みマスク */



/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

void hospac_ini_sys(void);			/* システムの初期化 */
void hospac_dis_int(void);			/* 割り込み禁止 */
void hospac_ena_int(void);			/* 割り込み許可 */
void hospac_cre_ctx_asm(T_HOSPAC_CTXINF *pk_ctxinf,
					VP sp, FP task, VP_INT exinf);	/* 実行コンテキストの作成(アセンブラ用) */
#define hospac_cre_ctx(pk_ctxinf, exinf, task, stksz, stk) \
	hospac_cre_ctx_asm(pk_ctxinf, ((VP)((UB *)(stk) + ((stksz) & 0xfffffffc))), task, exinf);
													/* アセンブラ側で都合がいいように引数を入れ替え */
#define hospac_del_ctx(pk_ctxinf)					/* 実行コンテキストの削除 */
void hospac_swi_ctx(T_HOSPAC_CTXINF *pk_pre_ctxinf,
						T_HOSPAC_CTXINF *pk_nxt_ctxinf);	/* 実行コンテキストの切替 */
void hospac_set_tex(T_HOSPAC_CTXINF *pk_pre_ctxinf,
					void (*exp)(TEXPTN), TEXPTN rasptn);	/* 例外処理実行設定 */

#define hospac_idle()	

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__H83__hospac_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
