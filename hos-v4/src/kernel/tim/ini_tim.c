/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �����ƥ���ִ���                                                      */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* �����ƥ���ִ������ѿ� */
SYSTIM kernel_systim;			/* �����ƥ���� */
UW     kernel_tic_cnt = 0;		/* ������ƥ��å��ѥ����� */



/* ���ִ�����ǽ�ν���� */
void kernel_ini_tim(void)
{
	kernel_tic_cnt = kernel_tic_deno;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */