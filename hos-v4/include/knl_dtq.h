/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    カーネル依存情報定義ヘッダ データキュー                               */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_dtq_h__
#define __HOS_V4__knl_dtq_h__


#include "knl_hos.h"



/* ------------------------------------------ */
/*                  定数定義                  */
/* ------------------------------------------ */

/* IDの範囲 */
#define TMIN_DTQID		1					/* データキューIDの最小値 */
#define TMAX_DTQID		(TMIN_DTQID + kernel_dtqcb_cnt - 1)
											/* データキューIDの最大値 */



/* ------------------------------------------ */
/*                 マクロ定義                 */
/* ------------------------------------------ */

/* メモリ領域のサイズ */
#define TSZ_DTQ(dtqcnt)		((SIZE)((UINT)(dtqcnt) * sizeof(VP_INT)))



/* ------------------------------------------ */
/*                 型定義                     */
/* ------------------------------------------ */

/* データキュー生成情報 */
typedef struct t_cdtq
{
	ATR    dtqatr;		/* データキュー属性 */
	UINT   dtqcnt;		/* データキュー領域の容量(データの個数) */
	VP     dtq;			/* データキュー領域の先頭番地 */
} T_CDTQ;


/* データキューコントロールブロック(ROM部) */
typedef struct t_kernel_dtqcb_rom
{
	ATR    dtqatr;		/* データキュー属性 */
	UINT   dtqcnt;		/* データキュー領域の容量(データの個数) */
	VP_INT *dtq;		/* データキュー領域の先頭番地 */
} T_KERNEL_DTQCB_ROM;

/* データキューコントロールブロック(RAM部) */
typedef struct t_kernel_dtqcb_ram
{
	T_MKNL_QUE sndque;	/* データキュー送信待ちタスクキュー */
	T_MKNL_QUE rcvque;	/* データキュー送信待ちタスクキュー */
	UINT       head;	/* データの先頭 */
	UINT       datacnt;	/* データの個数 */
	const T_KERNEL_DTQCB_ROM *dtqcb_rom;	/* データキューコントロールブロックROM部へのポインタ */
} T_KERNEL_DTQCB_RAM;



#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------- */
/*        グローバル変数宣言          */
/* ---------------------------------- */

/* データキュー管理 */
extern       T_KERNEL_DTQCB_RAM *kernel_dtqcb_ram_tbl[];	/* データキューコントロールブロックテーブル(RAM部) */
extern const INT kernel_dtqcb_cnt;							/* データキューコントロールブロック個数 */

/* データキューコントロールブロック変換マクロ */
#define KERNEL_DTQID_TO_DTQCB_RAM(dtqid)	(kernel_dtqcb_ram_tbl[(dtqid) - TMIN_DTQID])
															/* データキューIDからDTQCB RAMアドレスを取得 */



/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

/* データキュー */
#define kernel_ini_dtq()									/* データキューの初期化 */
ER      cre_dtq(ID dtqid, const T_CDTQ *pk_cdtq);			/* データキューの生成 */
ER_ID   acre_dtq(const T_CDTQ *pk_cdtq);					/* データキューの生成(ID番号自動割付け) */
ER      kernel_cre_dtq(ID dtqid, const T_CDTQ *pk_cdtq);	/* データキューの生成(カーネル内部関数) */
ER      del_dtq(ID dtqid);									/* データキューの削除 */
ER      snd_dtq(ID dtqid, VP_INT data);						/* データキューへの送信 */
ER      psnd_dtq(ID dtqid, VP_INT data);					/* データキューへの送信(ポーリング) */
#define ipsnd_dtq	psnd_dtq								/* データキューへの送信(ポーリング 非タスクコンテキスト用マクロ) */
ER      tsnd_dtq(ID dtqid, VP_INT data, TMO tmout);			/* データキューへの送信(タイムアウトあり) */
ER      fsnd_dtq(ID dtqid, VP_INT data);					/* データキューへの強制送信 */
#define ifsnd_dtq	fsnd_dtq								/* データキューへの強制送信(非タスクコンテキスト用マクロ) */
ER      rcv_dtq(ID dtqid, VP_INT *p_data);					/* データキューからの受信 */
ER      prcv_dtq(ID dtqid, VP_INT *p_data);					/* データキューからの受信(ポーリング) */
ER      trcv_dtq(ID dtqid, VP_INT *p_data, TMO tmout);		/* データキューからの受信(タイムアウトあり) */



#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_dtq_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
