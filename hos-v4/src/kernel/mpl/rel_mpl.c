/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ����Ĺ����ס���                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpl.h"



/* ����Ĺ����֥�å����ֵ� */
ER rel_mpl(
		ID mplid,		/* ����֥�å������оݤβ���Ĺ����ס����ID�ֹ� */
		VP blk)			/* �ֵѤ������֥�å�����Ƭ���� */
{
	T_KERNEL_MPLCB_RAM *mplcb_ram;
	T_MKNL_TCB         *mtcb;
	T_KERNEL_MPLINF    *mplinf;
	VP                 mem;
	BOOL               wup = FALSE;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( mplid < KERNEL_TMIN_MPLID || mplid > KERNEL_TMAX_MPLID )
	{
		return E_ID;	/* ID���� */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	mplcb_ram = KERNEL_MPLID_TO_MPLCB_RAM(mplid);

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mplcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif

	/* ����ס�����ֵ� */
	kernel_fre_hep(&mplcb_ram->hep, blk);

	/* �Ԥ��������ε��� */
	for ( ; ; )
	{
		/* �Ԥ�������Ƭ���饿�������Ф� */
		mtcb = mknl_ref_qhd(&mplcb_ram->que);
		if ( mtcb == NULL )
		{
			break;
		}
		
		/* ������ݤ˥ȥ饤 */
		mplinf = (T_KERNEL_MPLINF *)mtcb->data;
		mem = kernel_alc_hep(&mplcb_ram->hep, mplinf->blksz);
		if ( mem == NULL )
		{
			break;
		}

		/* �Ԥ���������������Ԥ���� */
		*mplinf->p_blk = mem;
		mknl_rmv_que(mtcb);					/* ����ס�����Ԥ����󤫤��� */
		mknl_rmv_tmout(mtcb);				/* �����ॢ�����Ԥ����󤫤��� */
		mknl_wup_tsk(mtcb, E_OK);			/* ���������Ԥ���� */
		
		wup = TRUE;
	}
	
	if ( wup )
	{
		mknl_exe_dsp();		/* �������ǥ����ѥå��μ¹� */
		mknl_exe_tex();		/* �㳰�����μ¹� */
	}

	mknl_unl_sys();		/* �����ƥ�Υ�å���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
