/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ���٥�ȥե饰                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"
#include "knl_mem.h"



/* ���٥�ȥե饰����ȥ���֥�å�(ưŪ������) */
typedef struct t_kernel_flgcb
{
	T_KERNEL_FLGCB_RAM flgcb_ram;	/* ���٥�ȥե饰����ȥ���֥�å�(RAM��) */
	T_KERNEL_FLGCB_ROM flgcb_rom;	/* ���٥�ȥե饰����ȥ���֥�å�(ROM��) */
} T_KERNEL_FLGCB;



/* ���٥�ȥե饰������(�����ͥ������ؿ�) */
ER kernel_cre_flg(
		ID           flgid,		/* �����оݤΥ��٥�ȥե饰��ID�ֹ� */
		const T_CFLG *pk_cflg)	/* ���٥�ȥե饰������������줿�ѥ��åȤؤΥݥ��� */
{
	T_KERNEL_FLGCB     *flgcb;
	T_KERNEL_FLGCB_RAM *flgcb_ram;
	T_KERNEL_FLGCB_ROM *flgcb_rom;

	/* �ѥ�᡼���������å� */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_cflg->flgatr & ~(TA_TFIFO | TA_TPRI | TA_WSGL | TA_WMUL | TA_CLR) )
	{
		return E_RSATR;
	}
#endif

	/* ���٥�ȥե饰�ѥ���γ��� */
	flgcb = (T_KERNEL_FLGCB *)kernel_alc_mem(sizeof(T_KERNEL_FLGCB));
	if ( flgcb == NULL )
	{
		return E_NOMEM;		/* ������­ */
	}

	/* ���٥�ȥե饰������ */
	flgcb_ram = &flgcb->flgcb_ram;
	flgcb_rom = &flgcb->flgcb_rom;
	flgcb_rom->flgatr  = pk_cflg->flgatr;
	flgcb_rom->iflgptn = pk_cflg->iflgptn;
	mknl_ini_que(&flgcb_ram->que);
	flgcb_ram->flgptn    = flgcb_rom->iflgptn;
	flgcb_ram->flgcb_rom = flgcb_rom;

	/* �����ơ��֥���ɲ� */
	kernel_flgcb_ram_tbl[flgid - TMIN_FLGID] = flgcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
