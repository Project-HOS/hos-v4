/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ���٥�ȥե饰                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"



/* ���٥�ȥե饰�Ԥ�(�ݡ����) */
ER pol_flg(
		ID     flgid,
		FLGPTN waiptn,
		MODE   wfmode,
		FLGPTN *p_flgptn)
{
	const T_KERNEL_FLGCB_ROM *flgcb_rom;
	T_KERNEL_FLGCB_RAM       *flgcb_ram;
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

	flgcb_ram = KERNEL_FLGID_TO_FLGCB_RAM(flgid);
	flgcb_rom = flgcb_ram->flgcb_rom;

	/* ���֥������Ȥ�¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( flgcb_ram == NULL )
	{
		mknl_unl_sys();		/* �����ƥ�Υ�å���� */
		return E_NOEXS;
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
		/* ���˾����������Ƥ��ʤ���Х����ॢ���� */
		ercd = E_TMOUT;
	}

	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return ercd;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
