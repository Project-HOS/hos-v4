/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ����ץ�ץ����                           */
/*   ������ƥ��å���                                                     */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"
#include "ostimer.h"
#include "wintimer.h"



/* ����� */
void OsTimer_Initialize(VP_INT exinf)
{
	WinTimer_Initialize(0);
}


/* �����޳����ߥϥ�ɥ� */
void OsTimer_Handler(VP_INT exinf)
{
	isig_tim();
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
