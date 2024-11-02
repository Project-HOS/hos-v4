/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル システム状態管理                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sys.h"



/* バージョン番号の参照 */
ER ref_ver(
	T_RVER *pk_rver)	/* バージョン情報を返すパケットへのポインタ */
{
	pk_rver->maker   = TKERNEL_MAKER;	/* カーネルのメーカーコード */
	pk_rver->prid    = TKERNEL_PRID;	/* カーネルの識別番号 */
	pk_rver->spver   = TKERNEL_SPVER;	/* ITRON仕様のバージョン情報 */
	pk_rver->prver   = TKERNEL_PRVER;	/* カーネルのバージョン番号 */
	pk_rver->prno[0] = 0;				/* カーネル製品の管理情報(1) */
	pk_rver->prno[1] = 0;				/* カーネル製品の管理情報(2) */
	pk_rver->prno[2] = 0;				/* カーネル製品の管理情報(3) */
	pk_rver->prno[3] = 0;				/* カーネル製品の管理情報(4) */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
