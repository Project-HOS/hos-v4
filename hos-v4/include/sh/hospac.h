/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    プロセッサ抽象化コンポーネント (日立 SH 用)                           */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__SH__hospac_h__
#define __HOS_V4__SH__hospac_h__



/* ------------------------------------------ */
/*                   型定義                   */
/* ------------------------------------------ */

/* SH固有 割り込み管理機構 */
typedef UW		IMSK;			/* 割り込みマスク */


/* コンテキスト情報保存ブロック */
typedef struct t_hos_pac_ctxinf
{
	VP sp;			/* スタックポインタ保存領域 */
} T_HOSPAC_CTXINF;



#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

#define hospac_ini_sys()							/* プロセッサ抽象化コンポーネントの初期化 */
void hospac_dis_int(void);							/* 割り込み禁止 */
void hospac_ena_int(void);							/* 割り込み許可 */
void hospac_cre_ctx_asm(T_HOSPAC_CTXINF *pk_ctxinf,
					VP sp, FP task, VP_INT exinf);	/* 実行コンテキストの作成(アセンブラ用) */
#define hospac_cre_ctx(pk_ctxinf, exinf, task, stksz, stk)	\
	hospac_cre_ctx_asm(pk_ctxinf, (VP)((UB *)(stk) + ((stksz) & 0xfffffffc)), task, exinf)
													/* アセンブラ側で都合がいいように引数を入れ替え */
#define hospac_del_ctx(pk_ctxinf)					/* 実行コンテキストの削除 */
void hospac_swi_ctx(T_HOSPAC_CTXINF *pk_pre_ctxinf,
						T_HOSPAC_CTXINF *pk_nxt_ctxinf);	/* 実行コンテキストの切替 */
#define hospac_idle()				/* アイドル時処理 */


/* SH固有 割り込み管理機構 */
ER   chg_imsk(IMSK imsk);			/* 割り込みマスク指定 */
ER   get_imsk(IMSK *p_imsk);		/* 割り込みマスクの参照 */



#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__SH__hospac_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
