/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ���٥�ȥե饰                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"



/* ���٥�ȥե饰�Ԥ� */
ER wai_flg(
		ID     flgid,		/* �Ԥ��оݤΥ��٥�ȥե饰��ID�ֹ� */
		FLGPTN waiptn,		/* �Ԥ��ӥåȥѥ����� */
		MODE   wfmode,		/* �Ԥ��⡼�� */
		FLGPTN *p_flgptn)	/* �Ԥ�������Υӥåȥѥ������Ǽ���ɥ쥹 */
{
	const T_KERNEL_FLGCB_ROM *flgcb_rom;
	T_KERNEL_FLGCB_RAM       *flgcb_ram;
	T_MKNL_TCB      *mtcb;
	T_KERNEL_FLGINF flginf;
	ER ercd;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( flgid < TMIN_FLGID || flgid > TMAX_FLGID )
	{
		return E_ID;	/* ����ID�ֹ� */
	}
#endif

	/* �ѥ�᡼���Υ����å� */
#ifdef HOS_ERCHK_E_PAR
	if ( (wfmode != TWF_ANDW && wfmode != TWF_ORW) || waiptn == 0)
	{
		return E_PAR;	/* �ѥ�᡼�����顼 */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	/* ����ƥ����ȥ����å� */
#ifdef HOS_ERCHK_E_CTX
	if ( mknl_sns_wai() )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_CTX;	/* ����ƥ��������� */
	}
#endif

	flgcb_ram = KERNEL_FLGID_TO_FLGCB_RAM(flgid);
	flgcb_rom = flgcb_ram->flgcb_rom;

	/* ���֥������Ȥ�¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( flgcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif

	/* �����ӥ��������������ѥ����å� */
#ifdef HOS_ERCHK_E_ILUSE
	if ( !(flgcb_rom->flgatr & TA_WMUL) && mknl_ref_qhd(&flgcb_ram->que) != NULL )
	{
		mknl_unl_sys();		/* �����ƥ�Υ�å���� */
		return E_ILUSE;		/* �����ӥ��������������� */
	}
#endif

	/* �Ԥ�������� */
	flginf.waiptn = waiptn;
	flginf.wfmode = wfmode;
	
	/* �ե饰�����å� */
	if ( kernel_chk_flg(flgcb_ram, &flginf) )
	{
		/* ���˾����������Ƥ���ʤ� */
		*p_flgptn = flgcb_ram->flgptn;		/* ������Υե饰�ѥ�������Ǽ */
		if ( flgcb_rom->flgatr & TA_CLR )
		{
			flgcb_ram->flgptn = 0;		/* ���ꥢ°��������Х��ꥢ */
		}
		ercd = E_OK;
	}
	else
	{
		/* �����������Ƥ��ʤ�����Ԥ������� */
		mtcb       = mknl_get_run_tsk();		/* �¹��楿��������� */
		mtcb->data = &flginf;					/* �Ԥ����֤���¸ */
		mknl_wai_tsk(mtcb, TTW_FLG);
		mknl_add_que(&flgcb_ram->que, mtcb, flgcb_rom->flgatr);	/* �Ԥ�������ɲ� */
		
		ercd = (ER)mknl_exe_dsp();	/* �������ǥ����ѥå��¹� */
		
		/* �����������Ʋ�����줿�Τʤ� */
		if ( ercd == E_OK )
		{
			*p_flgptn = flginf.waiptn;			/* ������Υե饰�ѥ�������Ǽ */
		}
		
		mknl_exe_tex();		/* �㳰�����μ¹� */
	}
	
	mknl_unl_sys();	/* �����ƥ�Υ�å���� */
	
	return ercd;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
