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


/* debug用 */
#define HOS_ERCHK_ALL


/* ------------------------------------------ */
/*                  定数定義                  */
/* ------------------------------------------ */

/* バージョン情報 */
#define TKERNEL_MAKER	0x0008				/* メーカーコード(個人) */
#define TKERNEL_PRID	0x0000				/* カーネルの識別番号(未定) */
#define TKERNEL_SPVER	0x5401				/* ITRON仕様のバージョン(μITRON Ver 4.01) */
#define TKERNEL_PRVER	0x0001				/* カーネルのバージョン番号 (HOS-V4 Ver 0.01) */

/* ビットパターンのビット数 */
#define TBIT_TEXPTN		16					/* タスク例外要因のビット数 */
#define TBIT_RDVPTN		16					/* ランデブ条件のビット数 */

/* IDの範囲 */
#define TMIN_MTXID		1					/* ミューテックスIDの最小値 */
#define TMIN_PORID		1					/* ランデブIDの最小値 */
#define TMIN_MPLID		1					/* 可変長メモリプールIDの最小値 */
#define TMIN_ALMID		1					/* アラームハンドラIDの最小値 */
#define TMIN_OVRID		1					/* オーバーランハンドラIDの最小値 */


/* エラーチェック(HOS独自) */
#ifdef HOS_ERCHK_ALL
#define HOS_ERCHK_E_PAR						/* E_PAR のエラーチェックを行う */
#define HOS_ERCHK_E_ID						/* E_ID のエラーチェックを行う */
#define HOS_ERCHK_E_CTX						/* E_CTX のエラーチェックを行う */
#define HOS_ERCHK_E_ILUSE					/* E_ILUSE のエラーチェックを行う */
#define HOS_ERCHK_E_NOMEM					/* E_NOMEM のエラーチェックを行う */
#define HOS_ERCHK_E_OBJ						/* E_OBJ のエラーチェックを行う */
#define HOS_ERCHK_E_NOEXS					/* E_NOEXS のエラーチェックを行う */
#define HOS_ERCHK_E_QOVR					/* E_QOVR のエラーチェックを行う */
#endif


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
