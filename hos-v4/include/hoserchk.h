/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ���顼�����å���٥�����                                              */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__hoserchk_h__
#define __HOS_V4__hoserchk_h__


#if !defined(_HOS_ERCHK_LEVEL)
#if defined(_HOS_ERCHK_CUSTOM)
#define _HOS_ERCHK_LEVEL 0
#else
#define _HOS_ERCHK_LEVEL 4
#endif
#endif


#if _HOS_ERCHK_LEVEL >= 1
#define HOS_ERCHK_E_OBJ						/* E_OBJ �Υ��顼�����å���Ԥ� */
#define HOS_ERCHK_E_NOMEM					/* E_NOMEM �Υ��顼�����å���Ԥ� */
#endif

#if _HOS_ERCHK_LEVEL >= 2
#define HOS_ERCHK_E_QOVR					/* E_QOVR �Υ��顼�����å���Ԥ� */
#endif

#if _HOS_ERCHK_LEVEL >= 3
#define HOS_ERCHK_E_PAR						/* E_PAR �Υ��顼�����å���Ԥ� */
#define HOS_ERCHK_E_ID						/* E_ID �Υ��顼�����å���Ԥ� */
#define HOS_ERCHK_E_RSATR					/* E_RSATR �Υ��顼�����å���Ԥ� */
#define HOS_ERCHK_E_NOID					/* E_NOID �Υ��顼�����å���Ԥ� */
#endif

#if _HOS_ERCHK_LEVEL >= 4
#define HOS_ERCHK_E_NOEXS					/* E_NOEXS �Υ��顼�����å���Ԥ� */
#define HOS_ERCHK_E_CTX						/* E_CTX �Υ��顼�����å���Ԥ� */
#define HOS_ERCHK_E_ILUSE					/* E_ILUSE �Υ��顼�����å���Ԥ� */
#endif



#endif	/* __HOS_V4__hoserchk_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
