/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� �����ϥ�ɥ�                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_cyc.h"
#include "knl_mem.h"



/* �����ϥ�ɥ������(�����ͥ�����) */
ER kernel_cre_cyc(
		ID           cycid,		/* �����оݤμ����ϥ�ɥ�ID�ֹ� */
		const T_CCYC *pk_ccyc)	/* �����ϥ�ɥ�������������줿�ѥ��åȤؤΥݥ��� */
{
	T_KERNEL_CYCCB_RAM *cyccb_ram;
	T_KERNEL_CYCCB_ROM *cyccb_rom;
	SIZE memsize;
	UB   *memptr;
	
	/* ɬ�פʥ��ꥵ������׻� */
	memsize = sizeof(T_KERNEL_CYCCB_RAM) + sizeof(T_KERNEL_CYCCB_ROM);
	
	/* ������� */
	memptr = (UB *)kernel_alc_mem(memsize);
#ifdef HOS_ERCHK_E_NOMEM
	if ( memptr == NULL )
	{
		return E_NOMEM;		/* ������­ */
	}
#endif

	/* �ݥ������� */	
	cyccb_ram  = (T_KERNEL_CYCCB_RAM *)memptr;
	memptr  += sizeof(T_KERNEL_CYCCB_RAM);
	cyccb_rom  = (T_KERNEL_CYCCB_ROM *)memptr;

	/* ������ */
	cyccb_ram->timobj.timhdr = kernel_cyc_hdr; /* �����ϥ�ɥ���Ͽ */
	cyccb_ram->timobj.next   = NULL;            /* �����ޥꥹ��̤��³ */
	cyccb_ram->cyccb_rom     = cyccb_rom;	/* �����ϥ�ɥ饳��ȥ���֥�å�ROM���ؤΥݥ��� */
	cyccb_rom->cycatr  = pk_ccyc->cycatr;	/* �����ϥ�ɥ�°�� */
	cyccb_rom->exinf   = pk_ccyc->exinf;	/* �����ϥ�ɥ�γ�ĥ���� */
	cyccb_rom->cychdr  = pk_ccyc->cychdr;	/* �����ϥ�ɥ�ε�ư���� */
	cyccb_rom->cyctim  = pk_ccyc->cyctim;	/* �����ϥ�ɥ�ε�ư���� */
/*	cyccb_rom->cycphs  = pk_ccyc->cycphs;*/	/* �����ϥ�ɥ�ε�ư���� */

	/* �����ϥ�ɥ饳��ȥ���֥�å��ơ��֥����Ͽ */
	KERNEL_CYCID_TO_CYCCB_RAM(cycid) = cyccb_ram;

	/* �¹�°���ʤ�г��� */
	if ( pk_ccyc->cycatr & TA_STA )
	{
		/* �����ޥꥹ�Ȥ��ɲ� */
		cyccb_ram->lefttim = pk_ccyc->cyctim;
		kernel_add_tml((T_KERNEL_TIM *)cyccb_ram);
	}

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
