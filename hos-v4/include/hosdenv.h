/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �Ķ���¸����Ƚ��                                                      */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__hosdenv_h__
#define __HOS_V4__hosdenv_h__



#if defined(__CC_ARM) || defined(__arm)	/* ARM����ѥ��� */

#include "arm/hospac.h"	

#elif defined(__CPU__)	/* ��ΩH8����ѥ��� */

#if (__CPU__ == 3)		/* H8/300H */
#include "h83/hospac.h"
#endif

#elif defined(__sh__)	/* gcc SH ����ѥ��� */

#include "sh/hospac.h"

#elif defined(_WIN32)	/* VC++ */

#include "win/hospac.h"

#elif defined(LSI_C)	/* LSI-C(86) */

#include "x86/hospac.h"

#else

#include "hospac.h"		/* ���̤Ǥ��ʤ����ϥ��󥯥롼�ɥѥ��λ������Ԥ��� */

#endif



#endif	/* __HOS_V4__hosdenv_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
