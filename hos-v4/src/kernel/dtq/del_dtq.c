/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� �ǡ������塼                                            */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
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
	if ( dtqid < TMIN_DTQID || dtqid > TMAX_DTQID )
	{
		return E_ID;	/* ����ID */
	}
#endif

	mknl_loc_sys();		/* �����ƥ�Υ��å� */

	dtqcb_ram = kernel_dtqcb_ram_tbl[dtqid - TMIN_DTQID];
	dtqcb_rom = dtqcb_ram->dtqcbrom;

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( dtqcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ��å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif
	
	/* �������β�� */
	mknl_clr_que(&dtqcb_ram->sndque);	/* �����Ԥ��������β�� */
	mknl_clr_que(&dtqcb_ram->rcvque);	/* �����Ԥ��������β�� */
	
	/* ����β��� */
	kernel_fre_mem(dtqcb_rom->dtq);
	kernel_fre_mem(dtqcb_ram);
	kernel_dtqcb_ram_tbl[dtqid - TMIN_DTQID] = NULL;
	
	mknl_exe_dsp();		/* �������ǥ����ѥå��μ¹� */
	mknl_exe_tex();		/* �㳰�����μ¹� */
	
	mknl_unl_sys();		/* �����ƥ�Υ��å���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */