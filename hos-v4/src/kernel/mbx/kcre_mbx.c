/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� �᡼��ܥå���                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_mbx.h"
#include "knl_mem.h"



/* �᡼��ܥå�������ȥ���֥�å�(ưŪ������) */
typedef struct t_kernel_mbxcb
{
	T_KERNEL_MBXCB_RAM mbxcb_ram;	/* �᡼��ܥå�������ȥ���֥�å�(RAM��) */
	T_KERNEL_MBXCB_ROM mbxcb_rom;	/* �᡼��ܥå�������ȥ���֥�å�(ROM��) */
} T_KERNEL_MBXCB;



/* �᡼��ܥå���������(�����ͥ������ؿ�) */
ER kernel_cre_mbx(
		ID           mbxid,		/* �����оݤΥ᡼��ܥå�����ID�ֹ� */
		const T_CMBX *pk_cmbx)	/* �᡼��ܥå���������������줿�ѥ��åȤؤΥݥ��� */
{
	T_KERNEL_MBXCB     *mbxcb;
	T_KERNEL_MBXCB_RAM *mbxcb_ram;
	T_KERNEL_MBXCB_ROM *mbxcb_rom;

	/* �ѥ�᡼���������å� */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_cmbx->mbxatr & ~(TA_TFIFO | TA_TPRI | TA_MFIFO | TA_MPRI) )
	{
		return E_RSATR;
	}
#endif

	/* �᡼��ܥå����ѥ���γ��� */
	mbxcb = (T_KERNEL_MBXCB *)kernel_alc_mem(sizeof(T_KERNEL_MBXCB));
	if ( mbxcb == NULL )
	{
		return E_NOMEM;		/* ������­ */
	}

	/* �᡼��ܥå��������� */
	mbxcb_ram = &mbxcb->mbxcb_ram;
	mbxcb_rom = &mbxcb->mbxcb_rom;
	mknl_ini_que(&mbxcb_ram->que);
	mbxcb_ram->msg       = NULL;
	mbxcb_ram->mbxcb_rom = mbxcb_rom;
	mbxcb_rom->mbxatr    = pk_cmbx->mbxatr;

	/* �����ơ��֥���ɲ� */
	kernel_mbxcb_ram_tbl[mbxid - TMIN_MBXID] = mbxcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
