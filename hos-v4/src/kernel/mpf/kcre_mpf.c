/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ����Ĺ����ס���                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2003 by Project HOS  */
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

/* ����Ĺ����ס��� ����ȥ���֥�å�(ưŪ�����������ͥ������) */
typedef struct t_kernel_mpfcb_with_blk
{
	T_KERNEL_MPFCB_RAM mpfcb_ram;	/* ����Ĺ����ס��� ����ȥ���֥�å�(RAM��) */
	T_KERNEL_MPFCB_ROM mpfcb_rom;	/* ����Ĺ����ס��� ����ȥ���֥�å�(ROM��) */
	VP	blk[1];			/* ����֥�å����ߡ� */
} T_KERNEL_MPFCB_WBLK;



/* ����Ĺ����ס��������(�����ͥ������ؿ�) */
ER kernel_cre_mpf(
		ID           mpfid,		/* �����оݤθ���Ĺ����ס����ID�ֹ� */
		const T_CMPF *pk_cmpf)	/* ����Ĺ����ס���������������줿�ѥ��åȤؤΥݥ��� */
{
	T_KERNEL_MPFCB     *mpfcb;
	T_KERNEL_MPFCB_RAM *mpfcb_ram;
	T_KERNEL_MPFCB_ROM *mpfcb_rom;
	VP   mpf;
	UINT i;

	/* �ѥ�᡼���������å� */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_cmpf->mpfatr & ~(TA_TFIFO | TA_TPRI) )
	{
		return E_RSATR;
	}
#endif

        /* �ѥ�᡼�������å� */
#ifdef HOS_ERCHK_E_PAR
        if ( pk_cmpf->blkcnt == 0 || pk_cmpf->blksz == 0 )
	{
                return E_PAR;   /* �ѥ�᡼������ */
	}
#endif

	/* ����Ĺ����ס����ѥ���γ��� */
	mpfcb = (T_KERNEL_MPFCB *)kernel_alc_mem(
		pk_cmpf->mpf != NULL ? 	sizeof(T_KERNEL_MPFCB) :
		sizeof(T_KERNEL_MPFCB_WBLK) - sizeof(VP)
		+ TSZ_MPF( pk_cmpf->blkcnt, pk_cmpf->blksz ) 
		);
	if ( mpfcb == NULL )
	{
		return E_NOMEM;		/* ������­ */
	}
	
	/* ����ס�����Ƭ���ϥ��å� */
	if ( pk_cmpf->mpf == NULL )
	{
		mpf = ((T_KERNEL_MPFCB_WBLK *)mpfcb)->blk;
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
	mpfcb_rom->blksz     = TSZ_ALIGNED(pk_cmpf->blksz);

	/* �֥�å��ν���� */
	for ( i = 0; i < mpfcb_rom->blkcnt - 1; i++ )
	{
		*(VP *)mpf = (VP)((UB *)mpf + mpfcb_rom->blksz);
		mpf        = (VP)((UB *)mpf + mpfcb_rom->blksz);
	}
	*(VP *)mpf = NULL;	/* �ǽ��֥�å� */

	/* �����ơ��֥���ɲ� */
	KERNEL_MPFID_TO_MPFCB_RAM(mpfid) = mpfcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2003 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
