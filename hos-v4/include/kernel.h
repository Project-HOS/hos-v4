/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    カーネル依存情報定義ヘッダ                                            */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#ifndef __HOS_V4__kernel_h__
#define __HOS_V4__kernel_h__



#include <stddef.h>
#include "itron.h"
#include "mknl.h"
#include "hoserchk.h"


/* ------------------------------------------ */
/*                  定数定義                  */
/* ------------------------------------------ */

#define TBIT_RDVPTN		16					/* ランデブ条件のビット数 */

/* IDの範囲 */
#define TMIN_MTXID		1					/* ミューテックスIDの最小値 */
#define TMIN_PORID		1					/* ランデブIDの最小値 */
#define TMIN_MPLID		1					/* 可変長メモリプールIDの最小値 */
#define TMIN_ALMID		1					/* アラームハンドラIDの最小値 */
#define TMIN_OVRID		1					/* オーバーランハンドラIDの最小値 */



/* C++ の static_cast 演算子と同じ効果のマクロ */
#define KERNEL_STATIC_CAST(s, m, p)	((s *)((B*)(p))-offsetof(s, m))	/* メンバのアドレスから構造体のアドレス算出 */

/* C言語の構造体を用いてポリモーフィズムを実現する際に */
/* 構造体メンバのポインタから、構造体先頭のポインタを  */
/* 算出することが必須となる。上記は C++ 言語では       */
/* dynamic_cast や static_cast 演算子で安全に行えるが  */
/* C言語ではある程度強引に実装する必要がある。         */


#include "knl_hos.h"
#include "knl_tsk.h"
#include "knl_sem.h"
#include "knl_flg.h"
#include "knl_dtq.h"
#include "knl_mbx.h"
#include "knl_mpf.h"
#include "knl_tim.h"
#include "knl_sys.h"
#include "knl_int.h"
#include "knl_exc.h"


/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif


/* ミューテックス */
ER      loc_mtx(ID mtxid);							/* ミューテックスのロック */
ER      ploc_mtx(ID mtxid);							/* ミューテックスのロック(ポーリング) */
ER      tloc_mtx(ID mtxid);							/* ミューテックスのロック(タイムアウトあり) */
ER      unl_mtx(ID mtxid);							/* ミューテックスのロック解除 */

/* メッセージバッファ */
ER      snd_mbf(ID mbfid, VP msg, UINT msgsz);		/* メッセージバッファへの送信 */
ER      psnd_mbf(ID mbfid, VP msg, UINT msgsz);		/* メッセージバッファへの送信(ポーリング) */
ER      tsnd_mbf(ID mbfid, VP msg, UINT msgsz, TMO tmout);
													/* メッセージバッファへの送信(タイムアウトあり) */



#ifdef __cplusplus
}
#endif



#endif /* __HOS_V4__kernel_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
