/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �ǥХå��ٱ�  �ǥ����ѥå��եå�                                      */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"
#include "dsp_hok.h"


/* �ǥ����ѥå��եå����� */
struct {
	T_DBG_DSPINF *inf;
	INT          mask;
	INT          infcnt;
	INT          read;
	INT          tail;
} _hosdbg_dsphok;


/* �եå���������� */
void _hosdbg_ini_dsphok(
		T_DBG_DSPINF dspinf[],
		INT          infcnt)
{
	_hosdbg_dsphok.inf    = dspinf;
	_hosdbg_dsphok.mask   = 0;
	_hosdbg_dsphok.infcnt = infcnt;
}


/* �եå��������� */
void _hosdbg_sta_dsphok(INT mask)
{
	INT i;

	mknl_loc_sys();

	for ( i = 0; i < _hosdbg_dsphok.infcnt; i++ )
	{
		_hosdbg_dsphok.inf[i].type = 0;
	}

	_hosdbg_dsphok.tail = 0;
	_hosdbg_dsphok.mask = mask;

	mknl_unl_sys();
}


/* �եå�������� */
void _hosdbg_stp_dsphok(void)
{
	mknl_loc_sys();

	_hosdbg_dsphok.mask = 0;

	mknl_unl_sys();
}


/* �ɤ߽Ф����� */
T_DBG_DSPINF *_hosdbg_red_fst(void)
{
	/* �ɤ߽Ф����ϰ���
	_hosdbg_dsphok.read = _hosdbg_dsphok.tail + 1;
	if ( _hosdbg_dsphok.read >= _hosdbg_dsphok.infcnt )
	{
		_hosdbg_dsphok.read = 0;
	}
	
}


/* �����ɤ߽Ф� */
void _hosdbg_red_fxt(T_DBG_DSPINF *pk_dspinf)
{
}


/* �������ǥ����ѥå��եå� */
void _hos_tsw_hok(void)
{
	T_DBG_DSPINF *inf;

	/* ͭ���ե饰�����å� */
	if ( !(_hosdbg_dsphok.mask & _HOS_HOKMSK_TSW) )
	{
		return;
	}

	/* ������� */
	inf = &_hosdbg_dsphok.inf[_hosdbg_dsphok.tail];
	inf->time = _hosdbg_get_tim();
	inf->type = _HOS_DSPTYPE_TSKSWC;
	inf->id   = kernel_get_tid(kernel_get_run_tsk());
	
	/* ���Хåե����� */
	if ( _hosdbg_dsphok.tail + 1 < _hosdbg_dsphok.infcnt )
	{
		_hosdbg_dsphok.tail++;
	}
	else
	{
		_hosdbg_dsphok.tail = 0;
	}
}


/* �����߳��� �եå� */
void _hos_intsta_hok(INTNO intno)
{
}


/* �����߽�λ �եå� */
void _hos_intext_hok(INTNO intno)
{
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
