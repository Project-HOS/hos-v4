/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル システム状態管理                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sys.h"



/* タスク優先順位の回転 */
ER rot_rdq(
		PRI tskpri)		/* 優先順位を回転する対象の優先度 */
{
	T_MKNL_TCB* mtcb;

	/* 自タスク優先度指定の処理 */
	if ( tskpri == TPRI_SELF )
	{
#ifdef HOS_ERCHK_E_PAR
		if ( sns_ctx() )
		{
			return E_PAR;
		}
		mtcb   = mknl_get_run_tsk();	/* 実行中タスクの取得 */
		tskpri = mknl_get_pri(mtcb);	/* 優先度の取得 */
#endif
	}

	/* パラメーター範囲チェック */
#ifdef HOS_ERCHK_E_PAR
	if ( tskpri < TMIN_TPRI ||  tskpri > TMAX_TPRI )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();			/* システムのロック */

	mknl_rot_rdq(tskpri);	/* タスク優先順位の回転 */
	
	mknl_exe_dsp();			/* タスクディスパッチの実行 */
	mknl_exe_tex();			/* 例外処理の実行 */
	
	mknl_unl_sys();			/* システムのロック解除 */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
