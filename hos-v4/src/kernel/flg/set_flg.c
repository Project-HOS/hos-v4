/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ���٥�ȥե饰                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* ���٥�ȥե饰�Υ��å� */
ER set_flg(
		ID     flgid,		/* ���å��оݤΥ��٥�ȥե饰��ID�ֹ� */
		FLGPTN setptn)		/* ���åȤ���ӥåȥѥ����� */
{
	const T_KERNEL_FLGCB_ROM *flgcb_rom;
	T_KERNEL_FLGCB_RAM       *flgcb_ram;
	T_KERNEL_FLGINF          *pk_flginf;
	T_MKNL_TCB *mtcb;
	T_MKNL_TCB *mtcb_next;
	BOOL       wupflg = FALSE;	/* ��ư�ե饰 */

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( flgid < TMIN_FLGID || flgid > TMAX_FLGID )
	{
		return E_ID;	/* ����ID�ֹ� */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	flgcb_ram = KERNEL_FLGID_TO_FLGCB_RAM(flgid);
	flgcb_rom = flgcb_ram->flgcbrom;

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( flgcb_ram == NULL )
	{
		mknl_unl_sys();		/* �����ƥ�Υ�å���� */
		return E_NOEXS;
	}
#endif

	/* �ե饰�Υ��å� */
	flgcb_ram->flgptn = (FLGPTN)(flgcb_ram->flgptn | setptn);

	/* �Ԥ�������������е��������å� */
	mtcb = mknl_ref_qhd(&flgcb_ram->que);
	while ( mtcb != NULL )
	{
		mtcb_next = mknl_ref_nxt(&flgcb_ram->que, mtcb);	/* �����Ԥ������������ */
		
		/* �ե饰�����å� */
		pk_flginf = (T_KERNEL_FLGINF *)mtcb->data;
		if ( kernel_chk_flg(flgcb_ram, pk_flginf) )
		{
			/* ���������������Ƥ���ʤ� */
			pk_flginf->waiptn = flgcb_ram->flgptn;	/* ���ߤΥե饰�ѥ�������Ǽ */
			if ( flgcb_rom->flgatr & TA_CLR )
			{
				flgcb_ram->flgptn = 0;				/* ���ꥢ°��������Х��ꥢ */
			}

			/* �Ԥ���� */
			mknl_rmv_que(flgcb_ram->mtcb);			/* �Ԥ����󤫤鳰�� */
			mknl_rmv_tmout(flgcb_ram->mtcb);		/* �����ॢ���Ȳ�� */
			mknl_wup_tsk(flgcb_ram->mtcb, E_OK);	/* �Ԥ��������ε��� */
			wupflg = TRUE;
		}
		mtcb = mtcb_next;	/* ���Υ������˿ʤ�� */
	}

	/* ��ư��Ԥä�������������ʤ�ǥ����ѥå���Ԥ� */
	if ( wupflg )
	{
		mknl_exe_dsp();		/* �������ǥ����ѥå��μ¹� */
		mknl_exe_tex();		/* �㳰�����μ¹� */
	}
	
	mknl_unl_sys();	/* �����ƥ�Υ�å���� */
	
	return E_OK;	/* ���ｪλ */
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
