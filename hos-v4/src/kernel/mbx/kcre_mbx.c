/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� �᡼��ܥå���                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2003 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbx.h"
#include "knl_mem.h"



/* �᡼��ܥå�������ȥ���֥�å�(ưŪ������) */
typedef struct t_kernel_mbxcb
{
	T_KERNEL_MBXCB_RAM mbxcb_ram;	/* �᡼��ܥå�������ȥ���֥�å�(RAM��) */
	T_KERNEL_MBXCB_ROM mbxcb_rom;	/* �᡼��ܥå�������ȥ���֥�å�(ROM��) */
} T_KERNEL_MBXCB;

/* ͥ�����̥��塼�إå��򥫡��ͥ�ǳ��ݤ����� */
typedef struct t_kernel_mbxcb_ph
{
	T_KERNEL_MBXCB	mbxcb;
	T_MSG		*mprihd[1];
} T_KERNEL_MBXCB_PH;


/* �᡼��ܥå���������(�����ͥ������ؿ�) */
ER kernel_cre_mbx(
		ID           mbxid,		/* �����оݤΥ᡼��ܥå�����ID�ֹ� */
		const T_CMBX *pk_cmbx)	/* �᡼��ܥå���������������줿�ѥ��åȤؤΥݥ��� */
{
	T_KERNEL_MBXCB     *mbxcb;
	T_KERNEL_MBXCB_RAM *mbxcb_ram;
	T_KERNEL_MBXCB_ROM *mbxcb_rom;
	T_MSG **mprihd;
	PRI   maxmpri;
	PRI   msgpri;

	/* �ѥ�᡼���������å� */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_cmbx->mbxatr & ~(TA_TFIFO | TA_TPRI | TA_MFIFO | TA_MPRI) )
	{
		return E_RSATR;
	}
#endif

	/* ��å�����ͥ�����դ���Ƚ�� */
	if ( pk_cmbx->mbxatr & TA_MPRI )
	{
		maxmpri = pk_cmbx->maxmpri;
		mprihd  = (T_MSG **)pk_cmbx->mprihd;
	}
	else
	{
		maxmpri = TMIN_MPRI;
		mprihd  = NULL;
	}

	/* �᡼��ܥå����ѥ���γ��� */
	mbxcb = (T_KERNEL_MBXCB *)kernel_alc_mem(
			mprihd == NULL ?
			sizeof(T_KERNEL_MBXCB_PH)+TSZ_MPRIHD(maxmpri-1) :
			sizeof(T_KERNEL_MBXCB));
	if ( mbxcb == NULL )
	{
		return E_NOMEM;		/* ������­ */
	}

	/* ��å��������塼�إå��򥫡��ͥ�ǳ��ݤ�����Υݥ��󥿥��å� */
	if ( mprihd == NULL )
	{
		mprihd = ((T_KERNEL_MBXCB_PH *)mbxcb)->mprihd;
	}

	/* �᡼��ܥå��������� */
	mbxcb_ram = &mbxcb->mbxcb_ram;
	mbxcb_rom = &mbxcb->mbxcb_rom;
	mknl_ini_que(&mbxcb_ram->que);
	mbxcb_ram->mbxcb_rom = mbxcb_rom;
	mbxcb_rom->mbxatr    = pk_cmbx->mbxatr;
	mbxcb_rom->maxmpri   = maxmpri;
	mbxcb_rom->mprihd    = mprihd;

	/* ͥ�����̤Υ�å��������塼�ν���� */
	for ( msgpri = 0; msgpri <= maxmpri - TMIN_MPRI; msgpri++ )
	{
		mprihd[msgpri] = NULL;
	}

	/* �����ơ��֥���ɲ� */
	KERNEL_MBXID_TO_MBXCB_RAM(mbxid) = mbxcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2003 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
