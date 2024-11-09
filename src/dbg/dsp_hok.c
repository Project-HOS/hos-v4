/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    デバッグ支援  ディスパッチフック                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"
#include "dsp_hok.h"


/* ディスパッチフック制御 */
struct {
	T_DBG_DSPINF *inf;
	INT          mask;
	INT          infcnt;
	INT          read;
	INT          tail;
} _hosdbg_dsphok;


/* フック処理初期化 */
void _hosdbg_ini_dsphok(
		T_DBG_DSPINF dspinf[],
		INT          infcnt)
{
	_hosdbg_dsphok.inf    = dspinf;
	_hosdbg_dsphok.mask   = 0;
	_hosdbg_dsphok.infcnt = infcnt;
}


/* フック処理開始 */
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


/* フック処理停止 */
void _hosdbg_stp_dsphok(void)
{
	mknl_loc_sys();

	_hosdbg_dsphok.mask = 0;

	mknl_unl_sys();
}


/* 読み出し開始 */
T_DBG_DSPINF *_hosdbg_red_fst(void)
{
	/* 読み出し開始位置設定 */
	_hosdbg_dsphok.read = _hosdbg_dsphok.tail;

	do
	{
		_hosdbg_dsphok.read++;
		if ( _hosdbg_dsphok.read >= _hosdbg_dsphok.infcnt )
		{
			_hosdbg_dsphok.read = 0;
		}
		
		/* 空なら終了 */
		if ( _hosdbg_dsphok.read == _hosdbg_dsphok.tail )
		{
			return NULL;
		}
	} while ( _hosdbg_dsphok.inf[_hosdbg_dsphok.read].type == 0 );
	
	return &_hosdbg_dsphok.inf[_hosdbg_dsphok.read];
}


/* 次を読み出し */
T_DBG_DSPINF *_hosdbg_red_nxt(void)
{
	/* 次の位置に移動 */
	_hosdbg_dsphok.read++;
	if ( _hosdbg_dsphok.read >= _hosdbg_dsphok.infcnt )
	{
		_hosdbg_dsphok.read = 0;
	}
		
	/* 空なら終了 */
	if ( _hosdbg_dsphok.read == _hosdbg_dsphok.tail )
	{
		return NULL;
	}
	
	return &_hosdbg_dsphok.inf[_hosdbg_dsphok.read];
}


/* タスクディスパッチフック */
void _hos_tsw_hok(void)
{
	T_KERNEL_TCB_RAM*  tcb_ram;
	T_DBG_DSPINF *inf;

	/* 有効フラグチェック */
	if ( !(_hosdbg_dsphok.mask & _HOS_HOKMSK_TSW) )
	{
		return;
	}

	tcb_ram = kernel_get_run_tsk();

	/* 情報取得 */
	inf = &_hosdbg_dsphok.inf[_hosdbg_dsphok.tail];
	inf->time = _hosdbg_get_tim();
	inf->type = _HOS_DSPTYPE_TSKSWC;
	if ( tcb_ram != NULL )
	{
		inf->id = kernel_get_tid(tcb_ram);
	}
	else
	{
		inf->id = 0;
	}
	
	/* ログバッファ更新 */
	if ( _hosdbg_dsphok.tail + 1 < _hosdbg_dsphok.infcnt )
	{
		_hosdbg_dsphok.tail++;
	}
	else
	{
		_hosdbg_dsphok.tail = 0;
	}
}


/* 割り込み開始 フック */
void _hos_intsta_hok(INTNO intno)
{
}


/* 割り込み終了 フック */
void _hos_intext_hok(INTNO intno)
{
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
