/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネル依存情報定義ヘッダ メッセージバッファ                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_mbf_h__
#define __HOS_V4__knl_mbf_h__


#include "knl_hos.h"



/* ------------------------------------------ */
/*                  定数定義                  */
/* ------------------------------------------ */

/* IDの範囲 */
#define TMIN_MBFID		1					/* メッセージバッファIDの最小値 */
#define TMAX_MBFID		(TMIN_MBFID + kernel_mbfcb_cnt - 1)
											/* メッセージバッファIDの最大値 */



/* ------------------------------------------ */
/*                 型定義                     */
/* ------------------------------------------ */

/* メッセージバッファ生成情報 */
typedef struct t_cmbf
{
	ATR  mbfatr;		/* メッセージバッファ属性 */
	UINT maxmsz;		/* メッセージの最大サイズ(バイト数) */
	SIZE mbfsz;			/* メッセージバッファ領域のサイズ(バイト数) */
    VP   mbf;			/* メッセージバッファ領域の先頭番地 */
} T_CMBF;

/* メッセージバッファ状態情報 */
typedef struct t_rmbf
{
	ID   stskid;		/* メッセージバッファの送信待ち行列の先頭のタスクのID番号 */
	ID   rtskid;		/* メッセージバッファの受信待ち行列の先頭のタスクのID番号 */
	UINT smsgcnt;		/* メッセージバッファに入っているメッセージの数 */
	SIZE fmbfsz;		/* メッセージバッファ領域の空き領域のサイズ(バイト数、最低限の管理領域を除く) */
} T_RMBF;


/* メッセージバッファコントロールブロック(ROM部) */
typedef struct t_kernel_mbfcb_rom
{
	ATR  mbfatr;		/* メッセージバッファ属性 */
	UINT maxmsz;		/* メッセージの最大サイズ(バイト数) */
	SIZE mbfsz;			/* メッセージバッファ領域のサイズ(バイト数) */
    VP   mbf;			/* メッセージバッファ領域の先頭番地 */
} T_KERNEL_MBFCB_ROM;

/* メッセージバッファコントロールブロック(RAM部) */
typedef struct t_kernel_mbfcb_ram
{
	T_MKNL_QUE sndque;	/* メッセージバッファ送信待ちタスクキュー */
	T_MKNL_QUE rcvque;	/* メッセージバッファ受信待ちタスクキュー */
	UINT       head;	/* 先頭メッセージの位置 */
	UINT       tail;	/* 末尾メッセージの位置 */
	const T_KERNEL_MBFCB_ROM *mbfcb_rom;	/* メッセージバッファコントロールブロックROM部へのポインタ */
} T_KERNEL_MBFCB_RAM;

/* 送信メッセージデータ情報 */
typedef struct t_kernel_mbfdat
{
	UINT msgsz;			/* メッセージサイズ */
	VP   msg;			/* メッセージの先頭番地 */
} T_KERNEL_MBFDAT;



#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------- */
/*        グローバル変数宣言          */
/* ---------------------------------- */

/* メッセージバッファ管理 */
extern       T_KERNEL_MBFCB_RAM *kernel_mbfcb_ram_tbl[];	/* メッセージバッファコントロールブロックテーブル(RAM部) */
extern const INT kernel_mbfcb_cnt;							/* メッセージバッファコントロールブロック個数 */

/* メッセージバッファコントロールブロック変換マクロ */
#define KERNEL_MBFID_TO_MBFCB_RAM(mbfid)	(kernel_mbfcb_ram_tbl[(mbfid) - TMIN_MBFID])
															/* メッセージバッファIDからMBFCB RAMアドレスを取得 */



/* ------------------------------------------ */
/*                 マクロ定義                 */
/* ------------------------------------------ */

/* メモリ領域のサイズ */
#define TSZ_MBF(msgcnt, msgsz)		((SIZE)((UINT)(msgcnt) * ((UINT)(msgsz) + 2) + 1))



/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

/* メッセージバッファ */
#define kernel_ini_mbf()									/* メッセージバッファの初期化 */
ER      cre_mbf(ID mbfid, const T_CMBF *pk_cmbf);			/* メッセージバッファの生成 */
ER_ID   acre_mbf(const T_CMBF *pk_cmbf);					/* メッセージバッファの生成(ID番号自動割付け) */
ER      kernel_cre_mbf(ID mbfid, const T_CMBF *pk_cmbf);	/* メッセージバッファの生成(カーネル内部関数) */
ER      del_mbf(ID mbfid);									/* メッセージバッファの削除 */
ER      snd_mbf(ID mbfid, VP msg, UINT msgsz);				/* メッセージバッファへの送信 */
ER      psnd_mbf(ID mbfid, VP msg, UINT msgsz);				/* メッセージバッファへの送信(ポーリング) */
ER      tsnd_mbf(ID mbfid, VP msg, UINT msgsz, TMO tmout);	/* メッセージバッファへの送信(タイムアウトあり) */
ER      kernel_snd_mbf(const T_KERNEL_MBFCB_ROM *mbfcb_rom,
			T_KERNEL_MBFCB_RAM *mbfcb_ram, VP msg, UINT msgsz);	/* メッセージバッファへの送信(カーネル内部関数) */
ER_UINT rcv_mbf(ID mbfid, VP msg);							/* メッセージバッファからの受信 */
ER_UINT prcv_mbf(ID mbfid, VP msg);							/* メッセージバッファからの受信(ポーリング) */
ER_UINT trcv_mbf(ID mbfid, VP msg,  TMO tmout);				/* メッセージバッファからの受信(タイムアウトあり) */
ER_UINT kernel_rcv_mbf(const T_KERNEL_MBFCB_ROM *mbfcb_rom,
			T_KERNEL_MBFCB_RAM *mbfcb_ram, VP msg);			/* メッセージバッファからの受信(カーネル内部関数) */
ER      ref_mbf(ID mbfid, T_RMBF *pk_rmbf);					/* メッセージバッファの状態参照 */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_mbf_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
