/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    カーネル依存情報定義ヘッダ イベントフラグ                             */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_flg_h__
#define __HOS_V4__knl_flg_h__



/* ------------------------------------------ */
/*                  定数定義                  */
/* ------------------------------------------ */

/* IDの範囲 */
#define TMIN_FLGID		1					/* イベントフラグIDの最小値 */
#define TMAX_FLGID		(TMIN_FLGID + kernel_flgcb_cnt - 1)
											/* イベントフラグIDの最大値 */

/* ビットパターンのビット数 */
#define TBIT_FLGPTN		16					/* イベントフラグのビット数 */



/* ------------------------------------------ */
/*                 型定義                     */
/* ------------------------------------------ */

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
	T_MKNL_TCB *mtcb;		/* イベントフラグ待ちタスク */
	FLGPTN     flgptn;		/* イベントフラグのビットパターン */
	const T_KERNEL_FLGCB_ROM* flgcbrom;	/* イベントフラグコントロールブロックROM部へのポインタ */
} T_KERNEL_FLGCB_RAM;

/* 待ちフラグ情報構造体 */
typedef struct t_kernel_flginf
{
	MODE   wfmode;		/* 待ちモード */
	FLGPTN waiptn;		/* 待ちビットパターン（解除時パターンと兼用) */
} T_KERNEL_FLGINF;


#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------- */
/*        グローバル変数宣言          */
/* ---------------------------------- */

/* イベントフラグ管理 */
extern       T_KERNEL_FLGCB_RAM *kernel_flgcb_ram_tbl[];	/* イベントフラグコントロールブロックテーブル(RAM部) */
extern const INT kernel_flgcb_cnt;							/* イベントフラグコントロールブロック個数 */

#define KERNEL_FLGID_TO_FLGCB_RAM(flgid)	(kernel_flgcb_ram_tbl[(flgid) - TMIN_FLGID])
															/* イベントフラグIDからFLGCB RAMアドレスを取得 */



/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

/* イベントフラグ */
void    kernel_ini_flg(void);						/* イベントフラグの初期化 */
ER      set_flg(ID flgid, FLGPTN setptn);			/* イベントフラグのセット */
#define iset_flg	set_flg							/* イベントフラグのセット(非タスクコンテキスト用マクロ) */
ER      clr_flg(ID flgid, FLGPTN clrptn);			/* イベントフラグのクリア */
ER      wai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn);
													/* イベントフラグ待ち */
ER      pol_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn);
													/* イベントフラグ待ち(ポーリング) */
ER      twai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn, TMO tmout);
													/* イベントフラグ待ち(タイムアウトあり) */
BOOL    kernel_chk_flg(T_KERNEL_FLGCB_RAM *flgcb_ram, T_KERNEL_FLGINF *pk_flginf);
													/* フラグが起床条件を満たしているかチェック */



#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_flg_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
