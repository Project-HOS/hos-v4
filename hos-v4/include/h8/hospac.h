/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    プロセッサ抽象化コンポーネント (日立 H8 300h 用)                      */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#ifndef __HOS4_hospac_h8_300_h__
#define __HOS4_hospac_h8_300_h__



#include <itron.h>



/* ------------------------------------------ */
/*                   型定義                   */
/* ------------------------------------------ */

/* コンテキスト情報保存ブロック */
typedef struct t_hos_pac_ctxinf
{
	VP sp;
} T_HOSPAC_CTXINF;



/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

void hospac_ini_sys(void);			/* システムの初期化 */
void hospac_des_int(void);			/* 割り込み禁止 */
void hospac_ena_int(void);			/* 割り込み許可 */
void hospac_cre_cnt_asm(T_HOSPAC_CTXINF *pk_ctxinf,
					VP sp, FP task, VP_INT exinf);	/* 実行コンテキストの作成(アセンブラ用) */
#define hospac_cre_cnt(pk_ctxinf, exinf, task, stksz, stk) \
	hospac_cre_cnt_asm(pk_ctxinf, ((VP)((UB *)(stk) + ((stksz) & 0xfffffffc))), task, exinf);
													/* アセンブラ側で都合がいいように引数を入れ替え */
void hospac_swi_cnt(T_HOSPAC_CTXINF *pk_pre_ctxinf,
						T_HOSPAC_CTXINF *pk_nxt_ctxinf);	/* 実行コンテキストの切替 */
void hospac_set_tex(T_HOSPAC_CTXINF *pk_pre_ctxinf,
					void (*exp)(TEXPTN), TEXPTN rasptn);	/* 例外処理実行設定 */


/* ------------------------------------------ */
/*               マクロ定義                   */
/* ------------------------------------------ */

#define hospac_del_cnt(pk_ctxinf)			/* 実行コンテキストの削除 */
/* H8 ではコンテキスト削除処理は不要 */



#endif	/* __HOS4_hospac_h8_300_h__ */



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
