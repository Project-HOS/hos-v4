/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    カーネル依存情報定義ヘッダ タスク管理                                 */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_tsk_h__
#define __HOS_V4__knl_tsk_h__


#include "knl_hos.h"



/* ------------------------------------------ */
/*                  定数定義                  */
/* ------------------------------------------ */

/* IDの範囲 */
#define TMIN_TSKID		1					/* タスクIDの最小値 */
#define TMAX_TSKID		(TMIN_TSKID + kernel_tcb_cnt - 1)

/* ビットパターンのビット数 */
#define TBIT_TEXPTN		16					/* タスク例外要因のビット数 */
											/* タスクIDの最大値 */


/* キューイング／ネスト回数の最大値 */
#define TMAX_ACTCNT		255					/* タスク起動要求キューイング数の最大値 */
#define TMAX_WUPCNT		65535				/* タスク起床要求キューイング数の最大値 */
#define TMAX_SUSCNT		255					/* タスク強制待ち要求ネスト数の最大値 */



/* ------------------------------------------ */
/*                 型定義                     */
/* ------------------------------------------ */

/* タスク生成情報 */
typedef struct t_ctsk
{
	ATR     tskatr;			/* タスク属性 */
	VP_INT  exinf;			/* タスクの拡張情報 */
	FP      task;			/* タスクの起動番地 */
	PRI     itskpri;		/* タスクの起動時優先度 */
	SIZE    stksz;			/* スタック領域のサイズ(バイト数) */
	VP      stk;			/* スタック領域の先頭番地 */
} T_CTSK;

/* タスク状態 */
typedef struct t_rtsk
{
	STAT   tskstat;			/* タスク状態 */
	PRI    tskpri;			/* タスクの現在優先度 */
	PRI	   tskbpri;			/* タスクのベース優先度 */
	STAT   tskwait;			/* 待ち要因 */
	ID     wobjid;			/* 待ち対象のオブジェクトのID番号 */
	TMO    lefttmo;			/* タイムアウトするまでの時間 */
	UINT   actcnt;			/* 起動要求キューイング回数 */
	UINT   wupcnt;			/* 起床要求キューイング回数 */
	UINT   suscnt;			/* 強制待ち要求ネスト回数 */
	VP_INT exinf;			/* タスクの拡張情報 */
} T_RTSK;

/* タスク状態(簡易版) */
typedef struct t_rtst
{
	STAT   tskstat;			/* タスク状態 */
	STAT   tskwait;			/* 待ち要因 */
	VP_INT exinf;			/* タスクの拡張情報 */
} T_RTST;


/* タスク例外処理コントロールブロック(RAM部) */
typedef struct t_kernel_texcb_ram
{
	TEXPTN rasptn;			/* タスク例外処理のタスク例外要因 */
	FP     texrtn;			/* タスク例外処理の起動番地 */
} T_KERNEL_TEXCB_RAM;


/* タスクコントロールブロック(ROM部) */
typedef struct t_kernel_tcb_rom
{
	ATR    tskatr;			/* タスク属性 */
	VP_INT exinf;			/* タスクの拡張情報 */
	FP     task;			/* タスクの起動番地 */
	PRI    itskpri;			/* タスクの起動時優先度 */
	SIZE   stksz;			/* タスクのスタックのサイズ（バイト数） */
	VP	   stk;				/* タスクのスタック領域の先頭番地 */
} T_KERNEL_TCB_ROM;


/* タスクコントロールブロック(RAM部) */
typedef struct t_kernel_tcb_ram
{
	T_MKNL_TCB mtcb;		/* μカーネル タスクコントロールブロック */	
	UB         actcnt;		/* 起動要求キューイング数 */
	UB         suscnt;		/* SUSPEND要求ネスト数 */
	UH         wupcnt;		/* 起床要求キューイング数 */
	T_KERNEL_TEXCB_RAM     *texcb;		/* タスク例外処理コントロールブロックへのポインタ */
	const T_KERNEL_TCB_ROM *tcb_rom;	/* タスクコントロールブロックROM部へのポインタ */
} T_KERNEL_TCB_RAM;



#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------- */
/*        グローバル変数宣言          */
/* ---------------------------------- */

/* タスク管理 */
extern       T_KERNEL_TCB_RAM* kernel_tcb_ram_tbl[];		/* タスクコントロールブロックテーブル(RAM部) */
extern const INT kernel_tcb_cnt;							/* タスクコントロールブロック個数 */

/* 変換マクロ */
#define KERNEL_TSKID_TO_TCB_RAM(tskid)	(kernel_tcb_ram_tbl[(tskid) - TMIN_TSKID])
															/* タスクIDからTCB RAMアドレスを取得 */



/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

/* タスク管理機能 */
void    kernel_ini_tsk(void);								/* タスクの初期化 */
ER      cre_tsk(ID tskid, const T_CTSK *pk_ctsk);			/* タスクの生成 */
ER_ID   acre_tsk(const T_CTSK *pk_ctsk);					/* タスクの生成(ID番号自動割付け) */
ER      kernel_cre_tsk(ID tskid, const T_CTSK *pk_ctsk);	/* タスク生成(カーネル内部) */
ER      del_tsk(ID tskid);									/* タスクの削除 */
ER      act_tsk(ID tskid);									/* タスクの起動 */
#define	iact_tsk	act_tsk									/* タスクの起動(非タスクコンテキスト用マクロ) */
ER_UINT can_act(ID tskid);									/* タスク起動要求のキャンセル */
ER      sta_tsk(ID tskid, VP_INT stacd);					/* タスクの起動(起動コード指定) */
void    ext_tsk(void);										/* 自タスクの終了 */
void    exd_tsk(void);										/* 自タスクの終了と削除 */
ER      ter_tsk(ID tskid);									/* タスクの強制終了 */
ER      chg_pri(ID tskid, PRI tskpri);						/* タスク優先度の変更 */
ER      get_pri(ID tskid, PRI *p_tskpri);					/* タスク優先度の参照 */
ER      ref_tsk(ID tskid, T_RTSK *p_rtsk);					/* タスクの状態参照 */
ER      ref_tst(ID tskid, T_RTST *p_rtst);					/* タスクの状態参照(簡易版) */

/* タスク付属同期機能 */
ER      slp_tsk(void);										/* タスクの起床待ち */
ER      tslp_tsk(TMO tmout);								/* タスクの起床待ち(タイムアウトあり) */
ER      wup_tsk(ID tskid);									/* タスクの起床 */
#define	iwup_tsk	wup_tsk									/* タスクの起床(非タスクコンテキスト用マクロ) */
ER_UINT can_wup(ID tskid);									/* タスク起床要求のキャンセル */
ER      rel_wai(ID tskid);									/* 待ち状態の強制解除 */
#define	irel_wai	rel_wai									/* 待ち状態の強制解除(非タスクコンテキスト用マクロ) */
ER      sus_tsk(ID tskid);									/* 強制待ち状態への移行 */
ER      rsm_tsk(ID tskid);									/* 強制待ち状態からの再開 */
ER      frsm_tsk(ID tskid);									/* 強制待ち状態からの強制再開 */
ER      dly_tsk(RELTIM dlytim);								/* 自タスクの遅延 */

/* タスク例外処理機能 */
ER      ras_tex(ID tskid, TEXPTN rasptn);					/* タスク例外処理の要求 */
#define iras_tex	ras_tex									/* タスク例外処理の要求(非タスクコンテキスト用マクロ) */
ER      dis_tex(void);										/* タスク例外処理の禁止 */
ER      ena_tex(void);										/* タスク例外処理の禁止 */
BOOL    sns_tex(void);										/* タスク例外処理禁止状態の参照 */



#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_tsk_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
