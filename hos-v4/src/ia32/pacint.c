/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*   プロセッサ抽象化コンポーネント (IA32用)  割込み関連処理                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#include "hosdenv.h"
#include "kernel.h"

ER   
chg_imsk(IMSK imsk)		/* 割り込みマスク指定 */
{
  out_port_byte (PIC1_BASE_ADDR2, ((UB)(imsk>>8)));
  out_port_byte (PIC2_BASE_ADDR2, ((UB)(imsk&0xff)));

  return E_OK;
}

/* 割り込みマスクの参照 */
ER   
get_imsk(IMSK *p_imsk)
{
  if (!p_imsk)
    return E_PAR;

  *p_imsk = in_port_byte (PIC1_BASE_ADDR2)<<8|in_port_byte (PIC2_BASE_ADDR2);
  
  return E_OK;
}

int
send_eoi(unsigned char exp)
{
  volatile unsigned char isr=0;
  unsigned char irq=0;
  
  if (PIC1_VBASE_ADDR > exp)
    return E_PAR;
  irq = exp - PIC1_VBASE_ADDR;
  if (MAX_IRQ_NR <= irq)
    return E_PAR;

  if ( irq < 8 )
    out_port_byte(PIC1_OCW2_ADDR, pic_mk_spec_eoi(irq));
  else {
    out_port_byte(PIC2_OCW2_ADDR, pic_mk_spec_eoi(irq));
    out_port_byte(PIC2_OCW3_ADDR, pic_mk_ocw3code(PIC_OCW3_NEXT_ISR));
    isr =in_port_byte(PIC2_OCW3_ADDR);
    if (!isr)
      out_port_byte(PIC1_OCW2_ADDR, pic_mk_spec_eoi(0x2));
  }

  return E_OK;
}

/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
