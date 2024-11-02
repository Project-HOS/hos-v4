/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    エラーチェックレベル設定                                              */
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
#define HOS_ERCHK_E_OBJ						/* E_OBJ のエラーチェックを行う */
#define HOS_ERCHK_E_NOMEM					/* E_NOMEM のエラーチェックを行う */
#endif

#if _HOS_ERCHK_LEVEL >= 2
#define HOS_ERCHK_E_QOVR					/* E_QOVR のエラーチェックを行う */
#endif

#if _HOS_ERCHK_LEVEL >= 3
#define HOS_ERCHK_E_PAR						/* E_PAR のエラーチェックを行う */
#define HOS_ERCHK_E_ID						/* E_ID のエラーチェックを行う */
#define HOS_ERCHK_E_RSATR					/* E_RSATR のエラーチェックを行う */
#define HOS_ERCHK_E_NOID					/* E_NOID のエラーチェックを行う */
#endif

#if _HOS_ERCHK_LEVEL >= 4
#define HOS_ERCHK_E_NOEXS					/* E_NOEXS のエラーチェックを行う */
#define HOS_ERCHK_E_CTX						/* E_CTX のエラーチェックを行う */
#define HOS_ERCHK_E_ILUSE					/* E_ILUSE のエラーチェックを行う */
#endif



#endif	/* __HOS_V4__hoserchk_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
