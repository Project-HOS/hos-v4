/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    環境依存情報判別                                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__hosdenv_h__
#define __HOS_V4__hosdenv_h__



#if defined(__CC_ARM) || defined(__arm)	/* ARMコンパイラ */

#include "arm/hospac.h"	

#elif defined(__CPU__)	/* 日立H8コンパイラ */

#if (__CPU__ == 3)		/* H8/300H */
#include "h83/hospac.h"
#endif

#elif defined(__H8300H__)	/* gcc H8/300H コンパイラ */

#include "h83/hospac.h"

#elif defined(__sh__) || defined(_SH1) || defined(_SH2) ||  defined(_SH3) || defined(_SH4)	/* SH コンパイラ */

#include "sh/hospac.h"

#elif defined(_WIN32)	/* VC++ */

#include "win/hospac.h"

#elif defined(LSI_C)	/* LSI-C(86) */

#include "x86/hospac.h"

#elif defined(__i386__)	/* i386-elf-gcc */
#include "ia32/hospac.h"

#else

#include "hospac.h"		/* 識別できない場合はインクルードパスの指定を期待する */

#endif



#endif	/* __HOS_V4__hosdenv_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
