/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル メールボックス                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_mbx.h"
#include "knl_mem.h"



/* メールボックスの削除 */
ER del_mbx(
		ID mbxid)	/* 削除対象のメールボックスのID番号 */
{
	T_KERNEL_MBXCB_RAM *mbxcb_ram;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( mbxid < TMIN_MBXID || mbxid > TMAX_MBXID )
	{
		return E_ID;	/* 不正ID */
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	mbxcb_ram = kernel_mbxcb_ram_tbl[mbxid - TMIN_MBXID];

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mbxcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif
	
	/* 待ちタスクの解除 */
	mknl_clr_que(&mbxcb_ram->que);
	
	/* メモリの解放 */
	kernel_fre_mem(mbxcb_ram);
	kernel_mbxcb_ram_tbl[mbxid - TMIN_MBXID] = NULL;
	
	mknl_exe_dsp();		/* タスクディスパッチの実行 */
	mknl_exe_tex();		/* 例外処理の実行 */
	
	mknl_unl_sys();	/* システムのロック解除 */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
