/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ����ѥ饤�֥��                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__win__hoslib_h__
#define __HOS_V4__win__hoslib_h__



#ifdef _HOS_USE_STDLIB	/* ɸ��饤�֥����Ѥʤ� */

#include <string.h>

#define __hos_bcopy(dst, src, size)		memcpy(dst, src, size)			/* �Х���ñ�̥��ԡ� */
#define __hos_hcopy(dst, src, size)		memcpy(dst, src, (size) * 2)	/* �ϡ��ե��ñ�̥��ԡ� */
#define __hos_wcopy(dst, src, size)		memcpy(dst, src, (size) * 4)	/* ���ñ�̥��ԡ� */

#else	/* ɸ��饤�֥���Ի��Ѥʤ� */

/* �Х���ñ�̥��ԡ� */
#define __hos_bcopy(dst, src, size)					\
	do {											\
		SIZE i;										\
		for ( i = 0; i < (SIZE)(size); i++ )		\
		{											\
			((VB *)(dst))[i] = ((VB *)(src))[i];	\
		}											\
	} while (0)

/* �ϡ��ե��ñ�̥��ԡ� */
#define __hos_hcopy(dst, src, size)					\
	do {											\
		SIZE i;										\
		for ( i = 0; i < (SIZE)(size); i++ )		\
		{											\
			((VH *)(dst))[i] = ((VH *)(src))[i];	\
		}											\
	} while (0)

/* ���ñ�̥��ԡ� */
#define __hos_wcopy(dst, src, size)					\
	do {											\
		SIZE i;										\
		for ( i = 0; i < (SIZE)(size); i++ )		\
		{											\
			((VW *)(dst))[i] = ((VW *)(src))[i];	\
		}											\
	} while (0)

#endif	/* _HOS_USE_STDLIB */



#endif	/* __HOS_V4__win__hospac_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
