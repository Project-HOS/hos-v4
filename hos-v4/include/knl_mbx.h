/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    カーネル依存情報定義ヘッダ メールボックス                             */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_mbx_h__
#define __HOS_V4__knl_mbx_h__



/* ------------------------------------------ */
/*                  定数定義                  */
/* ------------------------------------------ */

/* IDの範囲 */
#define TMIN_MBXID		1					/* メールボックスIDの最小値 */
#define TMAX_MBXID		(TMIN_MBXID + kernel_mbxcb_cnt - 1)
											/* メールボックスIDの最大値 */


/* 優先度の範囲 */
#define TMIN_MPRI		1					/* メッセージ優先度の最小値 */
#define TMAX_MPRI		65535				/* メッセージ優先度の最大値 */



/* ------------------------------------------ */
/*                 型定義                     */
/* ------------------------------------------ */

/* メールボックスのメッセージヘッダ */
typedef struct t_msg
{
	struct t_msg *next;		/* 次のメッセージへのポインタ */
} T_MSG;

/* メールボックスの優先度付きメッセージヘッダ */
typedef struct t_msg_pri
{
	T_MSG msg;				/* メッセージヘッダ */
	PRI   msgpri;			/* メッセージ優先度 */
} T_MSG_PRI;


/* メールボックスコントロールブロック(ROM部) */
typedef struct t_kernel_mbxcb_rom
{
	ATR       mbxatr;		/* メールボックス属性 */
} T_KERNEL_MBXCB_ROM;

/* メールボックスコントロールブロック(RAM部) */
typedef struct t_kernel_mbxcb_ram
{
	T_MKNL_QUE que;			/* メールボックス待ちタスクキュー */
	T_MSG      *msg;		/* メッセージの先頭番地 */
	const T_KERNEL_MBXCB_ROM *mbxrom;
} T_KERNEL_MBXCB_RAM;



#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------- */
/*        グローバル変数宣言          */
/* ---------------------------------- */

/* メールボックス管理 */
extern       T_KERNEL_MBXCB_RAM *kernel_mbxcb_ram_tbl[];	/* メールボックスコントロールブロックテーブル(RAM部) */
extern const INT kernel_mbxcb_cnt;							/* メールボックスコントロールブロック個数 */

#define KERNEL_MBXID_TO_MBXCB_RAM(mbxid)	(kernel_mbxcb_ram_tbl[(mbxid) - TMIN_MBXID])
															/* メールボックスIDからMBXCB RAMアドレスを取得 */



/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

/* メールボックス */
ER      snd_mbx(ID mbxid, T_MSG *pk_msg);			/* メールボックスへの送信 */
ER      rcv_mbx(ID mbxid, T_MSG **ppk_msg);			/* メールボックスからの受信 */
ER      prcv_mbx(ID mbxid, T_MSG **ppk_msg);		/* メールボックスからの受信(ポーリング) */
ER      trcv_mbx(ID mbxid, T_MSG **ppk_msg, TMO tmout);
													/* メールボックスからの受信(タイムアウトあり) */



#ifdef __cplusplus
}
#endif



#endif	/*__HOS_V4__knl_mbx_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
