/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ���٥�ȥե饰                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* ���٥�ȥե饰�Ԥ� */
ER wai_flg(
		ID     flgid,		/* �Ԥ��оݤΥ��٥�ȥե饰��ID�ֹ� */
		FLGPTN waiptn,		/* �Ԥ��ӥåȥѥ����� */
		MODE   wfmode,		/* �Ԥ��⡼�� */
		FLGPTN *p_flgptn)	/* �Ԥ�������Υӥåȥѥ������Ǽ���ɥ쥹 */
{
	const T_KERNEL_FLGCB_ROM *flgcb_rom;
	T_KERNEL_FLGCB_RAM       *flgcb_ram;
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

	/* ���֥������Ȥ�¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( flgcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif

	/* �����ӥ��������������ѥ����å�(TA_WMUL ̤���ݡ���)  */
#ifdef HOS_ERCHK_E_ILUSE
	if ( flgcb_ram->mtcb != NULL )
	{
		mknl_unl_sys();		/* �����ƥ�Υ�å���� */
		return E_ILUSE;		/* �����ӥ��������������� */
	}
#endif

	/* �Ԥ�������� */
	flgcb_ram->waiptn = waiptn;
	flgcb_ram->wfmode = wfmode;
	
	/* �ե饰�����å� */
	if ( kernel_chk_flg(flgcb_ram) )
	{
		/* ���˾����������Ƥ���ʤ� */
		flgcb_rom = flgcb_ram->flgcbrom;
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
		flgcb_ram->mtcb = mknl_get_run_tsk();
		mknl_wai_tsk(flgcb_ram->mtcb, TTW_FLG);

		/* �������ǥ����ѥå��¹� */
		ercd = (ER)mknl_exe_dsp();

		/* �����������Ʋ�����줿�Τʤ� */
		if ( ercd == E_OK )
		{
			flgcb_rom = flgcb_ram->flgcbrom;
			*p_flgptn = flgcb_ram->flgptn;		/* ������Υե饰�ѥ�������Ǽ */
			if ( flgcb_rom->flgatr & TA_CLR )
			{
				flgcb_ram->flgptn = 0;		/* ���ꥢ°��������Х��ꥢ */
			}		
		}
	}

	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return ercd;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
