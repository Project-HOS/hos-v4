/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� �ǡ������塼                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_dtq.h"
#include "knl_mem.h"




/* �ǡ������塼����ȥ���֥�å�(ưŪ������) */
typedef struct t_kernel_dtqcb
{
	T_KERNEL_DTQCB_RAM dtqcb_ram;	/* �ǡ������塼����ȥ���֥�å�(RAM��) */
	T_KERNEL_DTQCB_ROM dtqcb_rom;	/* �ǡ������塼����ȥ���֥�å�(ROM��) */
} T_KERNEL_DTQCB;



/* �ǡ������塼������(�����ͥ������ؿ�) */
ER kernel_cre_dtq(
		ID           dtqid,		/* �����оݤΥǡ������塼��ID�ֹ� */
		const T_CDTQ *pk_cdtq)	/* �ǡ������塼������������줿�ѥ��åȤؤΥݥ��� */
{
	T_KERNEL_DTQCB     *dtqcb;
	T_KERNEL_DTQCB_RAM *dtqcb_ram;
	T_KERNEL_DTQCB_ROM *dtqcb_rom;
	VP_INT *dtq;

	/* �ѥ�᡼���������å� */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_cdtq->dtqatr & ~(TA_TFIFO | TA_TPRI) )
	{
		return E_RSATR;
	}
#endif

	/* �ǡ������塼�ѥ���γ��� */
	dtqcb = (T_KERNEL_DTQCB *)kernel_alc_mem(sizeof(T_KERNEL_DTQCB));
	if ( dtqcb == NULL )
	{
		return E_NOMEM;		/* ������­ */
	}
	
	/* ���塼������� */
	if ( pk_cdtq->dtq == NULL )
	{
		dtq = (VP_INT *)kernel_alc_mem((SIZE)(sizeof(VP_INT *) * pk_cdtq->dtqcnt));
		if ( dtq == NULL )
		{
			kernel_fre_mem(dtqcb);
			return E_NOMEM;			/* ������­ */
		}
	}
	else
	{
		dtq = (VP_INT *)pk_cdtq->dtq;
	}

	/* �ǡ������塼������ */
	dtqcb_ram = &dtqcb->dtqcb_ram;
	dtqcb_rom = &dtqcb->dtqcb_rom;
	dtqcb_rom->dtqatr = pk_cdtq->dtqatr;
	dtqcb_rom->dtqcnt = pk_cdtq->dtqcnt;
	dtqcb_rom->dtq    = dtq;
	mknl_ini_que(&dtqcb_ram->sndque);
	mknl_ini_que(&dtqcb_ram->rcvque);
	dtqcb_ram->head      = 0;
	dtqcb_ram->datacnt   = 0;
	dtqcb_ram->dtqcb_rom = dtqcb_rom;

	/* �����ơ��֥���ɲ� */
	kernel_dtqcb_ram_tbl[dtqid - TMIN_DTQID] = dtqcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
