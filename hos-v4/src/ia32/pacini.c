/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*   �ץ��å���ݲ�����ݡ��ͥ�� (IA32��)  �������Ϣ����                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#include "hosdenv.h"
#include "kernel.h"

/* GDT  */
static segment_desc_t gdt[MAX_SELECTOR];
/* IDT  */
static gate_desc_t idt[MAX_INTR];
static descriptor_tbl_t gdtr;
static descriptor_tbl_t idtr;

/*  IA32��32�ӥåȥ������ȤΥ��åȥ��å�  */
static void
setup_segments(void)
{
  /*  GDT �Υ��󥹥ȡ���  */
  int i;
  /*  ���㥷�塦�饤�󡦥ե�������¤ˤ��뤿���GDT/IDT�Υ�ߥåȤ�, 
   *  8n-1 (n��, ������)�Ǥ���ɬ�פ�����.
   *  ����ˤĤ��Ƥ�, IA32�����ƥ�ץ���ߥ󥰥����ɤ�
   *  3-17�ڡ����򻲾Ȥ��뤳��. 
   */
  gdtr.limit=sizeof(segment_desc_t)*MAX_SELECTOR-1;
  gdtr.base=(unsigned long)gdt;
  /*  ���쥯��0��, �������ȥ쥸������̵�������Ѥ�����  */
  define_region(&gdt[0], 0x0, 0x0, 0x0, 0x0);
  /*  �����ɥ�������  */
  define_region(&gdt[1], 0x0, 0xfffff, CODE_SEG_TYPE, KERNEL_PRIV);
  /*  �ǡ�����������  */
  define_region(&gdt[2], 0x0, 0xfffff, DATA_SEG_TYPE, KERNEL_PRIV);

  /*  �ե饰�ξõ�
   */
  asm("pushl $2\n\t"
      "popf");
  /*   Global Description Table���ɤ߹���  */
  asm("movl %0, %%eax\n\t"
      "lgdt (%%eax)\n\t"
      "ljmp $0x8,$next\n\t"
      "next:\n\t"
      "movw $0x10,%%ax\n\t"
      "movw %%ax, %%ds\n\t"
      "movw %%ax, %%es\n\t"
      "movw %%ax,%%fs\n\t"
      "movw %%ax,%%gs\n\t"
      "movw %%ax, %%ss\n\t"
      :/* no output  */:"g"(&gdtr):"%eax");
  /*
   *  �㳰�ѥ����������
   */
  gate_set_intr_gate(&idt[0], KERNEL_CS, exp_divfault, SYS_PRIV);
  gate_set_intr_gate(&idt[1], KERNEL_CS, exp_debug, SYS_PRIV);
  gate_set_intr_gate(&idt[2], KERNEL_CS, exp_nmi, SYS_PRIV);
  gate_set_intr_gate(&idt[3], KERNEL_CS, exp_int3, SYS_PRIV);
  gate_set_intr_gate(&idt[4], KERNEL_CS, exp_overflow, SYS_PRIV);
  gate_set_intr_gate(&idt[5], KERNEL_CS, exp_bound, SYS_PRIV);
  gate_set_intr_gate(&idt[6], KERNEL_CS, exp_opcode, SYS_PRIV);
  gate_set_intr_gate(&idt[7], KERNEL_CS, exp_device_not_available, SYS_PRIV);
  gate_set_intr_gate(&idt[8], KERNEL_CS, exp_double_fault, SYS_PRIV);
  gate_set_intr_gate(&idt[9], KERNEL_CS, exp_coprocessor_segment_overrun, SYS_PRIV);
  gate_set_intr_gate(&idt[10], KERNEL_CS, exp_invalid_TSS, SYS_PRIV);
  gate_set_intr_gate(&idt[11], KERNEL_CS, exp_segment_not_present, SYS_PRIV);
  gate_set_intr_gate(&idt[12], KERNEL_CS, exp_stack_segment, SYS_PRIV);
  gate_set_intr_gate(&idt[13], KERNEL_CS, exp_general_protection, SYS_PRIV);
  gate_set_intr_gate(&idt[14], KERNEL_CS, exp_page_fault, SYS_PRIV);
  gate_set_intr_gate(&idt[15], KERNEL_CS, exp_intel_reserved, SYS_PRIV);
  gate_set_intr_gate(&idt[16], KERNEL_CS, exp_coprocessor_error, SYS_PRIV);
  gate_set_intr_gate(&idt[17], KERNEL_CS, exp_alignment_check, SYS_PRIV);
  gate_set_intr_gate(&idt[18], KERNEL_CS, exp_machine_check, SYS_PRIV);
  gate_set_intr_gate(&idt[19], KERNEL_CS, exp_simd_coprocessor, SYS_PRIV);

  /*  ����ƥ�ͽ���㳰  */
  for(i=20;i<0x20;++i)
    gate_set_intr_gate(&idt[i], KERNEL_CS, exp_intel_reserved, SYS_PRIV);

  /*
   *  �������ѥ����������
   */
  gate_set_intr_gate(&idt[0x20], KERNEL_CS, intr0, SYS_PRIV);
  gate_set_intr_gate(&idt[0x21], KERNEL_CS, intr1, SYS_PRIV);
  gate_set_intr_gate(&idt[0x22], KERNEL_CS, intr2, SYS_PRIV);
  gate_set_intr_gate(&idt[0x23], KERNEL_CS, intr3, SYS_PRIV);
  gate_set_intr_gate(&idt[0x24], KERNEL_CS, intr4, SYS_PRIV);
  gate_set_intr_gate(&idt[0x25], KERNEL_CS, intr5, SYS_PRIV);
  gate_set_intr_gate(&idt[0x26], KERNEL_CS, intr6, SYS_PRIV);
  gate_set_intr_gate(&idt[0x27], KERNEL_CS, intr7, SYS_PRIV);
  gate_set_intr_gate(&idt[0x28], KERNEL_CS, intr8, SYS_PRIV);
  gate_set_intr_gate(&idt[0x29], KERNEL_CS, intr9, SYS_PRIV);
  gate_set_intr_gate(&idt[0x2a], KERNEL_CS, intr10, SYS_PRIV);
  gate_set_intr_gate(&idt[0x2b], KERNEL_CS, intr11, SYS_PRIV);
  gate_set_intr_gate(&idt[0x2c], KERNEL_CS, intr12, SYS_PRIV);
  gate_set_intr_gate(&idt[0x2d], KERNEL_CS, intr13, SYS_PRIV);
  gate_set_intr_gate(&idt[0x2e], KERNEL_CS, intr14, SYS_PRIV);
  gate_set_intr_gate(&idt[0x2f], KERNEL_CS, intr15, SYS_PRIV);

  for(i=0x30;i<=0xff;++i)
    gate_set_intr_gate(&idt[i], KERNEL_CS, unknown_intr, SYS_PRIV);

  /*  IDT �Υ��󥹥ȡ���  */

  /*  ���㥷�塦�饤�󡦥ե�������¤ˤ��뤿���GDT/IDT�Υ�ߥåȤ�, 
   *  8n-1 (n��, ������)�Ǥ���ɬ�פ�����.
   *  ����ˤĤ��Ƥ�, IA32�����ƥ�ץ���ߥ󥰥����ɤ�
   *  3-17�ڡ����򻲾Ȥ��뤳��. 
   */
  idtr.limit=sizeof(gate_desc_t)*MAX_INTR-1;
  idtr.base=(unsigned long)idt;
  load_idtr(idtr);

  return ;
}

/*  �����ߥ���ȥ���Υ��åȥ��å�  */
void
init_pic(void)
{

  /*  �����ߥ���ȥ���ν����  */
  /* PIC 1*/
  out_port_byte_with_wait(PIC1_BASE_ADDR1, PIC1_ICW1_CODE);
  out_port_byte_with_wait(PIC1_BASE_ADDR2, PIC1_ICW2_CODE);
  out_port_byte_with_wait(PIC1_BASE_ADDR2, PIC1_ICW3_CODE);
  out_port_byte_with_wait(PIC1_BASE_ADDR2, PIC1_ICW4_CODE);
  /* PIC2  */
  out_port_byte_with_wait(PIC2_BASE_ADDR1, PIC2_ICW1_CODE);
  out_port_byte_with_wait(PIC2_BASE_ADDR2, PIC2_ICW2_CODE);
  out_port_byte_with_wait(PIC2_BASE_ADDR2, PIC2_ICW3_CODE);
  out_port_byte_with_wait(PIC2_BASE_ADDR2, PIC2_ICW4_CODE);

  /* 
   *  ���Ƥγ����ߤ���Ĥ���
   */ 
  chg_imsk(0);

  return ;
}
/*  �������ƥ������ͭ�ν����  */
void 
hospac_ini_sys(void)
{
  setup_segments();
  init_pic();
}

/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
