/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� ���ޥե�                                                */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"
#include "knl_mem.h"


/* ���ޥե�����ȥ���֥�å�(ưŪ������) */
typedef struct t_kernel_semcb
{
	T_KERNEL_SEMCB_RAM semcb_ram;	/* ���ޥե�����ȥ���֥�å�(RAM��) */
	T_KERNEL_SEMCB_ROM semcb_rom;	/* ���ޥե�����ȥ���֥�å�(ROM��) */
} T_KERNEL_SEMCB;



/* ���ޥե�������(�����ͥ������ؿ�) */
ER kernel_cre_sem(
		ID           semid,		/* �����оݤΥ��ޥե���ID�ֹ� */
		const T_CSEM *pk_csem)	/* ���ޥե�������������줿�ѥ��åȤؤΥݥ��� */
{
	T_KERNEL_SEMCB     *semcb;
	T_KERNEL_SEMCB_RAM *semcb_ram;
	T_KERNEL_SEMCB_ROM *semcb_rom;

	/* �ѥ�᡼���������å� */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_csem->sematr & ~(TA_TFIFO | TA_TPRI) )
	{
		return E_RSATR;
	}
#endif

	/* ���ޥե��ѥ���γ��� */
	semcb = (T_KERNEL_SEMCB *)kernel_alc_mem(sizeof(T_KERNEL_SEMCB));
#ifdef HOS_ERCHK_E_NOMEM
	if ( semcb == NULL )
	{
		return E_NOMEM;		/* ������­ */
	}
#endif

	/* ���ޥե������� */
	semcb_ram = &semcb->semcb_ram;
	semcb_rom = &semcb->semcb_rom;
	mknl_ini_que(&semcb_ram->que);
	semcb_ram->semcnt    = pk_csem->isemcnt;
	semcb_ram->semcb_rom = semcb_rom;
	semcb_rom->sematr    = pk_csem->sematr;
	semcb_rom->isemcnt   = pk_csem->isemcnt;
	semcb_rom->maxsem    = pk_csem->maxsem;

	/* �����ơ��֥���ɲ� */
	kernel_semcb_ram_tbl[semid - TMIN_SEMID] = semcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
