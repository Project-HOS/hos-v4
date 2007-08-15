/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ����ץ�ץ����                           */
/*  OS ������                                                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2007 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#include "semb1200a/ux_signal.h"
#include "kernel.h"
#include "kernel_id.h"
#include "ostimer.h"

// CPU����å���1/2�ǥ������
// 300000 / (600000000 / 2) = 0.001
// 600MHz�ξ�硢1ms = 300000
#define COMPARE  (300000)

/* OS�ѥ����޽���� */
void ostim_init(VP_INT exinf)
{
	SET_CP0_COUNT (0);
	SET_CP0_COMPARE (COMPARE);
	SET_CP0_STATUS (IE_IRQ5);
}

/* OS�������ѥϥ�ɥ� */
void ostim_hdr(VP_INT exinf)
{
    /* �����󥿥쥸�����Υ��ꥢ */
	SET_CP0_COUNT (0);
	SET_CP0_COMPARE (COMPARE);
    /* ������ƥ��å��ζ��� */
    isig_tim();
}

/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2007 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
