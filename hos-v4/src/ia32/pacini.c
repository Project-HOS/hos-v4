/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*   プロセッサ抽象化コンポーネント (IA32用)  初期化関連処理                      */
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

/*  IA32の32ビットセグメントのセットアップ  */
static void
setup_segments(void)
{
  /*  GDT のインストール  */
  int i;
  /*  キャシュ・ライン・フィルを最大限にするためにGDT/IDTのリミットは, 
   *  8n-1 (nは, 自然数)である必要がある.
   *  これについては, IA32システムプログラミングガイドの
   *  3-17ページを参照すること. 
   */
  gdtr.limit=sizeof(segment_desc_t)*MAX_SELECTOR-1;
  gdtr.base=(unsigned long)gdt;
  /*  セレクタ0は, セグメントレジスタの無効化に用いられる  */
  define_region(&gdt[0], 0x0, 0x0, 0x0, 0x0);
  /*  コードセグメント  */
  define_region(&gdt[1], 0x0, 0xfffff, CODE_SEG_TYPE, KERNEL_PRIV);
  /*  データセグメント  */
  define_region(&gdt[2], 0x0, 0xfffff, DATA_SEG_TYPE, KERNEL_PRIV);

  /*  フラグの消去
   */
  asm("pushl $2\n\t"
      "popf");
  /*   Global Description Tableの読み込み  */
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
   *  例外用セグメント定義
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

  /*  インテル予約例外  */
  for(i=20;i<0x20;++i)
    gate_set_intr_gate(&idt[i], KERNEL_CS, exp_intel_reserved, SYS_PRIV);

  /*
   *  割り込み用セグメント定義
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

  /*  IDT のインストール  */

  /*  キャシュ・ライン・フィルを最大限にするためにGDT/IDTのリミットは, 
   *  8n-1 (nは, 自然数)である必要がある.
   *  これについては, IA32システムプログラミングガイドの
   *  3-17ページを参照すること. 
   */
  idtr.limit=sizeof(gate_desc_t)*MAX_INTR-1;
  idtr.base=(unsigned long)idt;
  load_idtr(idtr);

  return ;
}

/*  割り込みコントローラのセットアップ  */
void
init_pic(void)
{

  /*  割り込みコントローラの初期化  */
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
   *  全ての割り込みを許可する
   */ 
  chg_imsk(0);

  return ;
}
/*  アーキテクチャ固有の初期化  */
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
