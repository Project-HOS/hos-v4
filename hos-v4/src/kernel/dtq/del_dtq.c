/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� �ǡ������塼                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_dtq.h"
#include "knl_mem.h"



/* �ǡ������塼�κ�� */
ER del_dtq(
		ID dtqid)	/* ����оݤΥǡ������塼��ID�ֹ� */
{
	const T_KERNEL_DTQCB_ROM *dtqcb_rom;
	T_KERNEL_DTQCB_RAM *dtqcb_ram;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( dtqid < KERNEL_TMIN_DTQID || dtqid > KERNEL_TMAX_DTQID )
	{
		return E_ID;	/* ����ID */
	}
#endif

	mknl_loc_sys();		/* �����ƥ�Υ�å� */

	dtqcb_ram = KERNEL_DTQID_TO_DTQCB_RAM(dtqid);
	dtqcb_rom = dtqcb_ram->dtqcb_rom;

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( dtqcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif
	
	/* �������β�� */
	mknl_clr_que(&dtqcb_ram->sndque);	/* �����Ԥ��������β�� */
	mknl_clr_que(&dtqcb_ram->rcvque);	/* �����Ԥ��������β�� */
	
	/* ����β��� */
	kernel_fre_mem(dtqcb_rom->dtq);
	kernel_fre_mem(dtqcb_ram);
	KERNEL_DTQID_TO_DTQCB_RAM(dtqid) = NULL;
	
	mknl_exe_dsp();		/* �������ǥ����ѥå��μ¹� */
	mknl_exe_tex();		/* �㳰�����μ¹� */
	
	mknl_unl_sys();		/* �����ƥ�Υ�å���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
