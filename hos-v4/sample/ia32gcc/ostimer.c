/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ����ץ�ץ����                             */
/*  IA32 OS ������                                                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#include "kernel.h"
#include "ia32/ioport.h"
#include "ostimer.h"
/* OS�ѥ����޽���� */
void ostim_init(VP_INT exinf)
{
  unsigned short divisor;

  /* ���������ޤ�����  */
#if PERIOD<1000
    divisor=PIT_I8254_INPFREQ / (1000 * 1000) * PERIOD + 1;
#else
    divisor=PIT_I8254_INPFREQ / (1000 / (PERIOD/1000)) + 1;
#endif

  /*  Set timer Channel2 as rate Genarator  */
  out_port_byte(PIT_PORT_MODECNTL, 0x34);
  /*
   *  Set interval as period_us  
   */
  out_port_byte(PIT_PORT_CHANNEL0, (divisor&(0xff)));      /*  write LSB  */
  out_port_byte(PIT_PORT_CHANNEL0, ((divisor>>8)&(0xff))); /*  write MSB  */
  
  return ;
}


/* �����ߥϥ�ɥ饵��ץ� */
void ostim_hdr(VP_INT exinf)	/* OS�������ѥϥ�ɥ� */
{
  isig_tim();		/* ������ƥ��å��ζ��� */
}
/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
