/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ��å������Хåե�                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"
#include "knl_mem.h"


/* ��å������Хåե�����ȥ���֥�å�(ưŪ������) */
typedef struct t_kernel_mbfcb
{
	T_KERNEL_MBFCB_RAM mbfcb_ram;	/* ��å������Хåե�����ȥ���֥�å�(RAM��) */
	T_KERNEL_MBFCB_ROM mbfcb_rom;	/* ��å������Хåե�����ȥ���֥�å�(ROM��) */
} T_KERNEL_MBFCB;



/* ��å������Хåե�������(�����ͥ������ؿ�) */
ER kernel_cre_mbf(
		ID           mbfid,		/* �����оݤΥ�å������Хåե���ID�ֹ� */
		const T_CMBF *pk_cmbf)	/* ��å������Хåե�������������줿�ѥ��åȤؤΥݥ��� */
{
	T_KERNEL_MBFCB     *mbfcb;
	T_KERNEL_MBFCB_RAM *mbfcb_ram;
	T_KERNEL_MBFCB_ROM *mbfcb_rom;
	VP                 mbf;
	
	/* �ѥ�᡼���������å� */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_cmbf->mbfatr & ~(TA_TFIFO | TA_TPRI) )
	{
		return E_RSATR;
	}
#endif
	
	/* ��å������Хåե��ѥ���γ��� */
	if ( pk_cmbf->mbf == NULL )
	{
		mbfcb = (T_KERNEL_MBFCB *)kernel_alc_mem(sizeof(T_KERNEL_MBFCB) + pk_cmbf->mbfsz);
		if ( mbfcb == NULL )
		{
			return E_NOMEM;		/* ������­ */
		}
		mbf = (VP)((VB *)mbfcb + pk_cmbf->mbfsz);
	}
	else
	{
		mbfcb = (T_KERNEL_MBFCB *)kernel_alc_mem(sizeof(T_KERNEL_MBFCB));
		if ( mbfcb == NULL )
		{
			return E_NOMEM;		/* ������­ */
		}
		mbf = pk_cmbf->mbf;
	}

	
	/* ��å������Хåե������� */
	mbfcb_ram = &mbfcb->mbfcb_ram;
	mbfcb_rom = &mbfcb->mbfcb_rom;
	mknl_ini_que(&mbfcb_ram->sndque);
	mknl_ini_que(&mbfcb_ram->rcvque);
	mbfcb_ram->head      = 0;
	mbfcb_ram->fmbfsz    = pk_cmbf->mbfsz;
	mbfcb_ram->smsgcnt   = 0;
	mbfcb_ram->mbfcb_rom = mbfcb_rom;
	mbfcb_rom->mbfatr    = pk_cmbf->mbfatr;
	mbfcb_rom->maxmsz    = pk_cmbf->maxmsz;
	mbfcb_rom->mbfsz     = pk_cmbf->mbfsz;
	mbfcb_rom->mbf       = mbf;
	
	/* �����ơ��֥���ɲ� */
	KERNEL_MBFID_TO_MBFCB_RAM(mbfid) = mbfcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
