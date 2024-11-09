/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネル依存情報定義ヘッダ イベントフラグ                             */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_flg_h__
#define __HOS_V4__knl_flg_h__


#include "knl_hos.h"



/* ------------------------------------------ */
/*                  定数定義                  */
/* ------------------------------------------ */

/* IDの範囲 */
#define KERNEL_TMIN_FLGID	TMIN_FLGID			/* イベントフラグIDの最小値 */
#define KERNEL_TMAX_FLGID	(KERNEL_TMIN_FLGID + kernel_flgcb_cnt - 1)
												/* イベントフラグIDの最大値 */

/* ビットパターンのビット数 */
#define TBIT_FLGPTN			16					/* イベントフラグのビット数 */



/* ------------------------------------------ */
/*                 型定義                     */
/* ------------------------------------------ */

/* イベントフラグ生成情報 */
typedef struct t_cflg
{
	ATR    flgatr;		/* イベントフラグ属性 */
	FLGPTN iflgptn;		/* イベントフラグのビットパターンの初期値 */
} T_CFLG;

/* イベントフラグ状態 */
typedef struct t_rflg
{
	ID     wtskid;		/* イベントフラグの待ち行列の先頭のタスクのID番号 */
	FLGPTN flgptn;		/* イベントフラグの現在のビットパターン */
} T_RFLG;


/* イベントフラグコントロールブロック(ROM部) */
typedef struct t_kernel_flgcb_rom
{
	ATR    flgatr;		/* イベントフラグ属性 */
	FLGPTN iflgptn;		/* イベントフラグのビットパターンの初期値 */
} T_KERNEL_FLGCB_ROM;

/* イベントフラグコントロールブロック(RAM部) */
typedef struct t_kernel_flgcb_ram
{
	T_MKNL_QUE que;			/* イベントフラグ待ち行列 */
	FLGPTN     flgptn;		/* イベントフラグのビットパターン */
	const T_KERNEL_FLGCB_ROM* flgcb_rom;	/* イベントフラグコントロールブロックROM部へのポインタ */
} T_KERNEL_FLGCB_RAM;


/* 待ちフラグ情報構造体 */
typedef struct t_kernel_flginf
{
	MODE   wfmode;		/* 待ちモード */
	FLGPTN waiptn;		/* 待ちビットパターン（解除時パターンと兼用) */
} T_KERNEL_FLGINF;



/* ---------------------------------- */
/*        グローバル変数宣言          */
/* ---------------------------------- */

/* イベントフラグ管理 */
extern       T_KERNEL_FLGCB_RAM *kernel_flgcb_ram_tbl[];	/* イベントフラグコントロールブロックテーブル(RAM部) */
extern const INT kernel_flgcb_cnt;							/* イベントフラグコントロールブロック個数 */

#define KERNEL_FLGID_TO_FLGCB_RAM(flgid)	(kernel_flgcb_ram_tbl[(flgid) - KERNEL_TMIN_FLGID])
															/* イベントフラグIDからFLGCB RAMアドレスを取得 */



/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* イベントフラグ */
void    kernel_ini_flg(void);								/* イベントフラグの初期化 */
ER      cre_flg(ID flgid, const T_CFLG *pk_cflg);			/* イベントフラグの生成 */
ER_ID   acre_flg(const T_CFLG *pk_cflg);					/* イベントフラグの生成(ID番号自動割付け) */
ER      kernel_cre_flg(ID flgid, const T_CFLG *pk_cflg);	/* イベントフラグの生成(カーネル内部関数) */
ER      del_flg(ID flgid);									/* イベントフラグの削除 */
ER      set_flg(ID flgid, FLGPTN setptn);					/* イベントフラグのセット */
#define iset_flg	set_flg									/* イベントフラグのセット(非タスクコンテキスト用マクロ) */
ER      clr_flg(ID flgid, FLGPTN clrptn);					/* イベントフラグのクリア */
ER      wai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn);
															/* イベントフラグ待ち */
ER      pol_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn);
															/* イベントフラグ待ち(ポーリング) */
ER      twai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn, TMO tmout);
															/* イベントフラグ待ち(タイムアウトあり) */
ER      ref_flg(ID flgid, T_RFLG *pk_rflg);					/* イベントフラグの状態参照 */
BOOL    kernel_chk_flg(T_KERNEL_FLGCB_RAM *flgcb_ram, T_KERNEL_FLGINF *pk_flginf);
															/* フラグが起床条件を満たしているかチェック */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_flg_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
