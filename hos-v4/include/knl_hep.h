/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネル メモリヒープ                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_hep_h__
#define __HOS_V4__knl_hep_h__


#include "itron.h"


#define KERNEL_HEP_MEMALIGN		32			/**< %jp{メモリアライメント} */
#define KERNEL_HEP_USING			0x1234		/**< %jp{使用中} */
#define KERNEL_HEP_FREE			0xabcd		/**< %jp{未使用} */



/** %jp{サイズアライメント} */
#define KERNEL_HEP_ALIGNED(size)	(((size) + KERNEL_HEP_MEMALIGN - 1) & ~(KERNEL_HEP_MEMALIGN - 1))


/** %jp{ヒープメモリブロック} */
typedef struct kernel_t_hepblk
{
	struct kernel_t_hepblk* prev;	/**< %jp{前のブロック} */
	SIZE   size;					/**< %jp{ブロックのサイズ} */
	INT    flag;					/**< %jp{使用中フラグ} */
} T_KERNEL_HEPBLK;


/** %jp{ヒープ制御ブロック} */
typedef struct kernel_t_hepcb
{
	T_KERNEL_HEPBLK *base;			/**< %jp{カーネル用メモリ先頭ブロックのアドレス} */
	SIZE            heapsz;			/**< %jp{カーネル用メモリサイズ} */
} T_KERNEL_HEPCB;


/** %jp{カーネルメモリ管理ブロックサイズ} */
#define KERNEL_HEP_BLKSIZE			KERNEL_HEP_ALIGNED(sizeof(T_KERNEL_HEPBLK))


#ifdef __cplusplus
extern "C" {
#endif

void    kernel_cre_hep(T_KERNEL_HEPCB *pk_hepcb, void *p_base, SIZE size);	/**< %jp{メモリヒープを生成} */
#define kernel_del_hep(pk_hepcb)	do {} while(0)								/**< %jp{メモリヒープを削除} */
VP      kernel_alc_hep(T_KERNEL_HEPCB *pk_hepcb, SIZE size);					/**< %jp{メモリの割り当て} */
void    kernel_fre_hep(T_KERNEL_HEPCB *pk_hepcb, VP ptr);						/**< %jp{メモリの解放} */
#define kernel_alg_hep(size)		KERNEL_HEP_ALIGNED(size)					/**< %jp{メモリサイズのアライメントを合わせる} */

#ifdef __cplusplus
}
#endif


#endif	/* __HOS_V4__knl_hep_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
