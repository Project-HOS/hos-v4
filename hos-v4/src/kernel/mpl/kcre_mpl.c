/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ����Ĺ����ס���                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2003 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpl.h"
#include "knl_mem.h"


/* ����Ĺ����ס��� ����ȥ���֥�å�(ưŪ������) */
typedef struct t_kernel_mplcb
{
	T_KERNEL_MPLCB_RAM mplcb_ram;	/* ����Ĺ����ס��� ����ȥ���֥�å�(RAM��) */
	T_KERNEL_MPLCB_ROM mplcb_rom;	/* ����Ĺ����ס��� ����ȥ���֥�å�(ROM��) */
} T_KERNEL_MPLCB;

/* ����Ĺ����ס��� ����ȥ���֥�å�(ưŪ�����������ͥ������) */
typedef struct t_kernel_mplcb_with_blk
{
	T_KERNEL_MPLCB_RAM mplcb_ram;	/* ����Ĺ����ס��� ����ȥ���֥�å�(RAM��) */
	T_KERNEL_MPLCB_ROM mplcb_rom;	/* ����Ĺ����ס��� ����ȥ���֥�å�(ROM��) */
	VP	blk[1];			/* ����֥�å����ߡ� */
} T_KERNEL_MPLCB_WBLK;



/* ����Ĺ����ס��������(�����ͥ������ؿ�) */
ER kernel_cre_mpl(
		ID           mplid,		/* �����оݤβ���Ĺ����ס����ID�ֹ� */
		const T_CMPL *pk_cmpl)	/* ����Ĺ����ס���������������줿�ѥ��åȤؤΥݥ��� */
{
	T_KERNEL_MPLCB     *mplcb;
	T_KERNEL_MPLCB_RAM *mplcb_ram;
	T_KERNEL_MPLCB_ROM *mplcb_rom;
	VP   mpl;

	/* �ѥ�᡼���������å� */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_cmpl->mplatr & ~(TA_TFIFO | TA_TPRI) )
	{
		return E_RSATR;
	}
#endif

	/* �ѥ�᡼�������å� */
#ifdef HOS_ERCHK_E_PAR
	if ( pk_cmpl->mplsz == 0 )
	{
		return E_PAR;   /* �ѥ�᡼������ */
	}
#endif

	/* ����Ĺ����ס����ѥ���γ��� */
	mplcb = (T_KERNEL_MPLCB *)kernel_alc_mem(
		pk_cmpl->mpl != NULL ? 	sizeof(T_KERNEL_MPLCB) :
		sizeof(T_KERNEL_MPLCB_WBLK) - sizeof(VP)
		+ pk_cmpl->mplsz 
		);
	if ( mplcb == NULL )
	{
		return E_NOMEM;		/* ������­ */
	}
	
	/* ����ס�����Ƭ���ϥ��å� */
	if ( pk_cmpl->mpl == NULL )
	{
		mpl = ((T_KERNEL_MPLCB_WBLK *)mplcb)->blk;
	}
	else
	{
		mpl = pk_cmpl->mpl;
	}

	/* ����Ĺ����ס�������� */
	mplcb_ram = &mplcb->mplcb_ram;
	mplcb_rom = &mplcb->mplcb_rom;
	mknl_ini_que(&mplcb_ram->que);
	mplcb_ram->mplcb_rom = mplcb_rom;
	mplcb_rom->mplatr    = pk_cmpl->mplatr;
	mplcb_rom->mplsz     = pk_cmpl->mplsz;
	mplcb_rom->mpl       = mpl;

	/* �ҡ������� */
	kernel_cre_hep(&mplcb_ram->hep, mplcb_rom->mpl, mplcb_rom->mplsz);

	/* �����ơ��֥���ɲ� */
	KERNEL_MPLID_TO_MPLCB_RAM(mplid) = mplcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2003 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
