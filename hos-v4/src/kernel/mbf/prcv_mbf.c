/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ��¸��������إå� ��å������Хåե�                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"



/* ��å������Хåե�����μ���(�ݡ����) */
ER_UINT prcv_mbf(
		ID   mbfid,		/* �����оݤΥ�å������Хåե���ID�ֹ� */
		VP   msg)		/* ������å��������Ǽ������Ƭ���� */
{
	const T_KERNEL_MBFCB_ROM *mbfcb_rom;
	T_KERNEL_MBFCB_RAM       *mbfcb_ram;
	ER_UINT                  ercd;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( mbfid < KERNEL_TMIN_MBFID || mbfid > KERNEL_TMAX_MBFID )
	{
		return E_ID;	/* ID���� */
	}
#endif

	/* �ѥ�᡼���������å� */
#ifdef HOS_ERCHK_E_PAR
	if ( msg == NULL )
	{
		return E_PAR;	/* �ѥ�᡼�������� */		
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	mbfcb_ram = KERNEL_MBFID_TO_MBFCB_RAM(mbfid);

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mbfcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif

	mbfcb_rom = mbfcb_ram->mbfcb_rom;

	/* �Хåե����� */
	ercd = kernel_rcv_mbf(mbfcb_rom, mbfcb_ram, msg);
	
	mknl_unl_sys();		/* �����ƥ�Υ�å���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
