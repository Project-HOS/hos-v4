/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ����Ĺ����ס���                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"
#include "knl_mem.h"


/* ����Ĺ����ס��� ����ȥ���֥�å�(ưŪ������) */
typedef struct t_kernel_mpfcb
{
	T_KERNEL_MPFCB_RAM mpfcb_ram;	/* ����Ĺ����ס��� ����ȥ���֥�å�(RAM��) */
	T_KERNEL_MPFCB_ROM mpfcb_rom;	/* ����Ĺ����ס��� ����ȥ���֥�å�(ROM��) */
} T_KERNEL_MPFCB;



/* ����Ĺ����ס��������(�����ͥ������ؿ�) */
ER kernel_cre_mpf(
		ID           mpfid,		/* �����оݤθ���Ĺ����ס����ID�ֹ� */
		const T_CMPF *pk_cmpf)	/* ����Ĺ����ס���������������줿�ѥ��åȤؤΥݥ��� */
{
	T_KERNEL_MPFCB     *mpfcb;
	T_KERNEL_MPFCB_RAM *mpfcb_ram;
	T_KERNEL_MPFCB_ROM *mpfcb_rom;
	VP   mpf;
	UB   *ptr;
	UINT i;

	/* �ѥ�᡼���������å� */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_cmpf->mpfatr & ~(TA_TFIFO | TA_TPRI) )
	{
		return E_RSATR;
	}
#endif

	/* ����Ĺ����ס����ѥ���γ��� */
	mpfcb = (T_KERNEL_MPFCB *)kernel_alc_mem(sizeof(T_KERNEL_MPFCB));
	if ( mpfcb == NULL )
	{
		return E_NOMEM;		/* ������­ */
	}
	
	/* ����ס����ѥ������ */
	if ( pk_cmpf->mpf == NULL )
	{
		mpf = kernel_alc_mem((SIZE)(pk_cmpf->blksz * pk_cmpf->blkcnt));
		if ( mpf == NULL )
		{
			kernel_fre_mem(mpfcb);
			return E_NOMEM;		/* ������­ */
		}
	}
	else
	{
		mpf = pk_cmpf->mpf;
	}

	/* ����Ĺ����ס�������� */
	mpfcb_ram = &mpfcb->mpfcb_ram;
	mpfcb_rom = &mpfcb->mpfcb_rom;
	mknl_ini_que(&mpfcb_ram->que);
	mpfcb_ram->free      = mpf;
	mpfcb_ram->mpfcb_rom = mpfcb_rom;
	mpfcb_rom->mpfatr    = pk_cmpf->mpfatr;
	mpfcb_rom->blkcnt    = pk_cmpf->blkcnt;
	mpfcb_rom->blksz     = pk_cmpf->blksz;
	mpfcb_rom->mpf       = pk_cmpf->mpf;

	/* �֥�å��ν���� */
	ptr = (UB *)mpfcb_rom->mpf;
	for ( i = 0; i < mpfcb_rom->blkcnt - 1; i++ )
	{
		*(VP *)ptr = (VP)(ptr + mpfcb_rom->blksz);
		ptr += mpfcb_rom->blksz;
	}
	*(VP *)ptr = NULL;	/* �ǽ��֥�å� */

	/* �����ơ��֥���ɲ� */
	KERNEL_MPFID_TO_MPFCB_RAM(mpfid) = mpfcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
