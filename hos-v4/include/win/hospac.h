/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    プロセッサ抽象化コンポーネント (Windows用)                            */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#ifndef __HOS4_hospac_win_h__
#define __HOS4_hospac_win_h__



/* Windows ヘッダファイルの読みこみ */
#define SIZE  WIN_SIZE
#include <windows.h>
#undef  SIZE

/*   Windows 標準の SIZE 構造体が ITRON の標準型と重なるので */
/* 上記のように強制的に WIN_SIZE に名前を変えている          */
/* Windows APIで SIZE を利用するときは要注意                 */

#include <itron.h>


/* ------------------------------------------ */
/*                   型定義                   */
/* ------------------------------------------ */

/* コンテキスト情報保存ブロック */
typedef struct t_hos_pac_ctxinf
{
	HANDLE hThread;			/* スレッドハンドル */
	DWORD  dwThreadId;		/* スレッドID */
} T_HOSPAC_CTXINF;



/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

void hospac_ini_sys(void);			/* システムの初期化 */
void hospac_ena_int(void);			/* 割り込み許可 */
void hospac_dis_int(void);			/* 割り込み禁止 */
void hospac_cre_cnt(T_HOSPAC_CTXINF *pk_ctxinf,
					VP_INT exinf, FP task,
					SIZE stksz, VP stk);					/* 実行コンテキストの作成 */
void hospac_del_cnt(T_HOSPAC_CTXINF *pk_ctxinf);			/* 実行コンテキストの削除 */
void hospac_swi_cnt(T_HOSPAC_CTXINF *pk_pre_ctxinf,
						T_HOSPAC_CTXINF *pk_nxt_ctxinf);	/* 実行コンテキストの切替 */
void hospac_set_tex(T_HOSPAC_CTXINF *pk_pre_ctxinf,
					void (*exp)(TEXPTN), TEXPTN rasptn);	/* 例外処理実行設定 */
void hospac_idle(void);				/* アイドル時の処理 */

#ifdef __cplusplus
}
#endif


#endif	/* __HOS4_hospac_win_h__ */



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
