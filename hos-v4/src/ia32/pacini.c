/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*   プロセッサ抽象化コンポーネント (IA32用)  初期化関連処理                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#include "hosdenv.h"
#include "itron.h"
#include "kernel.h"

/* GDT  */
static segment_desc_t gdt[MAX_SELECTOR];
/* IDT  */
static gate_desc_t idt[MAX_INTR];
static descriptor_tbl_t gdtr;
static descriptor_tbl_t idtr;
/*  ユーザトラップベクタ  */
static VP _user_trap_entries[]={
  _kernel_ia32__user_trap_30,_kernel_ia32__user_trap_31,
  _kernel_ia32__user_trap_32,_kernel_ia32__user_trap_33,
  _kernel_ia32__user_trap_34,_kernel_ia32__user_trap_35,
  _kernel_ia32__user_trap_36,_kernel_ia32__user_trap_37,
  _kernel_ia32__user_trap_38,_kernel_ia32__user_trap_39,
  _kernel_ia32__user_trap_3a,_kernel_ia32__user_trap_3b,
  _kernel_ia32__user_trap_3c,_kernel_ia32__user_trap_3d,
  _kernel_ia32__user_trap_3e,_kernel_ia32__user_trap_3f,
  _kernel_ia32__user_trap_40,_kernel_ia32__user_trap_41,
  _kernel_ia32__user_trap_42,_kernel_ia32__user_trap_43,
  _kernel_ia32__user_trap_44,_kernel_ia32__user_trap_45,
  _kernel_ia32__user_trap_46,_kernel_ia32__user_trap_47,
  _kernel_ia32__user_trap_48,_kernel_ia32__user_trap_49,
  _kernel_ia32__user_trap_4a,_kernel_ia32__user_trap_4b,
  _kernel_ia32__user_trap_4c,_kernel_ia32__user_trap_4d,
  _kernel_ia32__user_trap_4e,_kernel_ia32__user_trap_4f,
  _kernel_ia32__user_trap_50,_kernel_ia32__user_trap_51,
  _kernel_ia32__user_trap_52,_kernel_ia32__user_trap_53,
  _kernel_ia32__user_trap_54,_kernel_ia32__user_trap_55,
  _kernel_ia32__user_trap_56,_kernel_ia32__user_trap_57,
  _kernel_ia32__user_trap_58,_kernel_ia32__user_trap_59,
  _kernel_ia32__user_trap_5a,_kernel_ia32__user_trap_5b,
  _kernel_ia32__user_trap_5c,_kernel_ia32__user_trap_5d,
  _kernel_ia32__user_trap_5e,_kernel_ia32__user_trap_5f,
  _kernel_ia32__user_trap_60,_kernel_ia32__user_trap_61,
  _kernel_ia32__user_trap_62,_kernel_ia32__user_trap_63,
  _kernel_ia32__user_trap_64,_kernel_ia32__user_trap_65,
  _kernel_ia32__user_trap_66,_kernel_ia32__user_trap_67,
  _kernel_ia32__user_trap_68,_kernel_ia32__user_trap_69,
  _kernel_ia32__user_trap_6a,_kernel_ia32__user_trap_6b,
  _kernel_ia32__user_trap_6c,_kernel_ia32__user_trap_6d,
  _kernel_ia32__user_trap_6e,_kernel_ia32__user_trap_6f,
  _kernel_ia32__user_trap_70,_kernel_ia32__user_trap_71,
  _kernel_ia32__user_trap_72,_kernel_ia32__user_trap_73,
  _kernel_ia32__user_trap_74,_kernel_ia32__user_trap_75,
  _kernel_ia32__user_trap_76,_kernel_ia32__user_trap_77,
  _kernel_ia32__user_trap_78,_kernel_ia32__user_trap_79,
  _kernel_ia32__user_trap_7a,_kernel_ia32__user_trap_7b,
  _kernel_ia32__user_trap_7c,_kernel_ia32__user_trap_7d,
  _kernel_ia32__user_trap_7e,_kernel_ia32__user_trap_7f,
  _kernel_ia32__user_trap_80,_kernel_ia32__user_trap_81,
  _kernel_ia32__user_trap_82,_kernel_ia32__user_trap_83,
  _kernel_ia32__user_trap_84,_kernel_ia32__user_trap_85,
  _kernel_ia32__user_trap_86,_kernel_ia32__user_trap_87,
  _kernel_ia32__user_trap_88,_kernel_ia32__user_trap_89,
  _kernel_ia32__user_trap_8a,_kernel_ia32__user_trap_8b,
  _kernel_ia32__user_trap_8c,_kernel_ia32__user_trap_8d,
  _kernel_ia32__user_trap_8e,_kernel_ia32__user_trap_8f,
  _kernel_ia32__user_trap_90,_kernel_ia32__user_trap_91,
  _kernel_ia32__user_trap_92,_kernel_ia32__user_trap_93,
  _kernel_ia32__user_trap_94,_kernel_ia32__user_trap_95,
  _kernel_ia32__user_trap_96,_kernel_ia32__user_trap_97,
  _kernel_ia32__user_trap_98,_kernel_ia32__user_trap_99,
  _kernel_ia32__user_trap_9a,_kernel_ia32__user_trap_9b,
  _kernel_ia32__user_trap_9c,_kernel_ia32__user_trap_9d,
  _kernel_ia32__user_trap_9e,_kernel_ia32__user_trap_9f,
  _kernel_ia32__user_trap_a0,_kernel_ia32__user_trap_a1,
  _kernel_ia32__user_trap_a2,_kernel_ia32__user_trap_a3,
  _kernel_ia32__user_trap_a4,_kernel_ia32__user_trap_a5,
  _kernel_ia32__user_trap_a6,_kernel_ia32__user_trap_a7,
  _kernel_ia32__user_trap_a8,_kernel_ia32__user_trap_a9,
  _kernel_ia32__user_trap_aa,_kernel_ia32__user_trap_ab,
  _kernel_ia32__user_trap_ac,_kernel_ia32__user_trap_ad,
  _kernel_ia32__user_trap_ae,_kernel_ia32__user_trap_af,
  _kernel_ia32__user_trap_b0,_kernel_ia32__user_trap_b1,
  _kernel_ia32__user_trap_b2,_kernel_ia32__user_trap_b3,
  _kernel_ia32__user_trap_b4,_kernel_ia32__user_trap_b5,
  _kernel_ia32__user_trap_b6,_kernel_ia32__user_trap_b7,
  _kernel_ia32__user_trap_b8,_kernel_ia32__user_trap_b9,
  _kernel_ia32__user_trap_ba,_kernel_ia32__user_trap_bb,
  _kernel_ia32__user_trap_bc,_kernel_ia32__user_trap_bd,
  _kernel_ia32__user_trap_be,_kernel_ia32__user_trap_bf,
  _kernel_ia32__user_trap_c0,_kernel_ia32__user_trap_c1,
  _kernel_ia32__user_trap_c2,_kernel_ia32__user_trap_c3,
  _kernel_ia32__user_trap_c4,_kernel_ia32__user_trap_c5,
  _kernel_ia32__user_trap_c6,_kernel_ia32__user_trap_c7,
  _kernel_ia32__user_trap_c8,_kernel_ia32__user_trap_c9,
  _kernel_ia32__user_trap_ca,_kernel_ia32__user_trap_cb,
  _kernel_ia32__user_trap_cc,_kernel_ia32__user_trap_cd,
  _kernel_ia32__user_trap_ce,_kernel_ia32__user_trap_cf,
  _kernel_ia32__user_trap_d0,_kernel_ia32__user_trap_d1,
  _kernel_ia32__user_trap_d2,_kernel_ia32__user_trap_d3,
  _kernel_ia32__user_trap_d4,_kernel_ia32__user_trap_d5,
  _kernel_ia32__user_trap_d6,_kernel_ia32__user_trap_d7,
  _kernel_ia32__user_trap_d8,_kernel_ia32__user_trap_d9,
  _kernel_ia32__user_trap_da,_kernel_ia32__user_trap_db,
  _kernel_ia32__user_trap_dc,_kernel_ia32__user_trap_dd,
  _kernel_ia32__user_trap_de,_kernel_ia32__user_trap_df,
  _kernel_ia32__user_trap_e0,_kernel_ia32__user_trap_e1,
  _kernel_ia32__user_trap_e2,_kernel_ia32__user_trap_e3,
  _kernel_ia32__user_trap_e4,_kernel_ia32__user_trap_e5,
  _kernel_ia32__user_trap_e6,_kernel_ia32__user_trap_e7,
  _kernel_ia32__user_trap_e8,_kernel_ia32__user_trap_e9,
  _kernel_ia32__user_trap_ea,_kernel_ia32__user_trap_eb,
  _kernel_ia32__user_trap_ec,_kernel_ia32__user_trap_ed,
  _kernel_ia32__user_trap_ee,_kernel_ia32__user_trap_ef,
  _kernel_ia32__user_trap_f0,_kernel_ia32__user_trap_f1,
  _kernel_ia32__user_trap_f2,_kernel_ia32__user_trap_f3,
  _kernel_ia32__user_trap_f4,_kernel_ia32__user_trap_f5,
  _kernel_ia32__user_trap_f6,_kernel_ia32__user_trap_f7,
  _kernel_ia32__user_trap_f8,_kernel_ia32__user_trap_f9,
  _kernel_ia32__user_trap_fa,_kernel_ia32__user_trap_fb,
  _kernel_ia32__user_trap_fc,_kernel_ia32__user_trap_fd,
  _kernel_ia32__user_trap_fe,_kernel_ia32__user_trap_ff};

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
  gate_set_trap_gate(&idt[0], KERNEL_CS, _kernel_ia32__exc_divfault, SYS_PRIV);
  gate_set_intr_gate(&idt[1], KERNEL_CS, _kernel_ia32__exc_debug, SYS_PRIV);
  gate_set_trap_gate(&idt[2], KERNEL_CS, _kernel_ia32__exc_nmi, SYS_PRIV);
  gate_set_intr_gate(&idt[3], KERNEL_CS, _kernel_ia32__exc_int3, SYS_PRIV);
  gate_set_intr_gate(&idt[4], KERNEL_CS, _kernel_ia32__exc_overflow, SYS_PRIV);
  gate_set_intr_gate(&idt[5], KERNEL_CS, _kernel_ia32__exc_bound, SYS_PRIV);
  gate_set_trap_gate(&idt[6], KERNEL_CS, _kernel_ia32__exc_opcode, SYS_PRIV);
  gate_set_trap_gate(&idt[7], KERNEL_CS, _kernel_ia32__exc_device_not_available, SYS_PRIV);
  gate_set_trap_gate(&idt[8], KERNEL_CS, _kernel_ia32__exc_double_fault, SYS_PRIV);
  gate_set_trap_gate(&idt[9], KERNEL_CS, _kernel_ia32__exc_coprocessor_segment_overrun, SYS_PRIV);
  gate_set_trap_gate(&idt[10], KERNEL_CS, _kernel_ia32__exc_invalid_TSS, SYS_PRIV);
  gate_set_trap_gate(&idt[11], KERNEL_CS, _kernel_ia32__exc_segment_not_present, SYS_PRIV);
  gate_set_trap_gate(&idt[12], KERNEL_CS, _kernel_ia32__exc_stack_segment, SYS_PRIV);
  gate_set_trap_gate(&idt[13], KERNEL_CS, _kernel_ia32__exc_general_protection, SYS_PRIV);
  gate_set_intr_gate(&idt[14], KERNEL_CS, _kernel_ia32__exc_page_fault, SYS_PRIV);
  gate_set_trap_gate(&idt[15], KERNEL_CS, _kernel_ia32__exc_intel_reserved, SYS_PRIV);
  gate_set_trap_gate(&idt[16], KERNEL_CS, _kernel_ia32__exc_coprocessor_error, SYS_PRIV);
  gate_set_trap_gate(&idt[17], KERNEL_CS, _kernel_ia32__exc_alignment_check, SYS_PRIV);
  gate_set_trap_gate(&idt[18], KERNEL_CS, _kernel_ia32__exc_machine_check, SYS_PRIV);
  gate_set_trap_gate(&idt[19], KERNEL_CS, _kernel_ia32__exc_simd_coprocessor, SYS_PRIV);

  /*  インテル予約例外  */
  for(i=20;i<0x20;++i)
    gate_set_trap_gate(&idt[i], KERNEL_CS, _kernel_ia32__exc_intel_reserved, SYS_PRIV);

  /*
   *  割り込み用セグメント定義
   */
  gate_set_intr_gate(&idt[0x20], KERNEL_CS, _kernel_ia32__intr0, SYS_PRIV);
  gate_set_intr_gate(&idt[0x21], KERNEL_CS, _kernel_ia32__intr1, SYS_PRIV);
  gate_set_intr_gate(&idt[0x22], KERNEL_CS, _kernel_ia32__intr2, SYS_PRIV);
  gate_set_intr_gate(&idt[0x23], KERNEL_CS, _kernel_ia32__intr3, SYS_PRIV);
  gate_set_intr_gate(&idt[0x24], KERNEL_CS, _kernel_ia32__intr4, SYS_PRIV);
  gate_set_intr_gate(&idt[0x25], KERNEL_CS, _kernel_ia32__intr5, SYS_PRIV);
  gate_set_intr_gate(&idt[0x26], KERNEL_CS, _kernel_ia32__intr6, SYS_PRIV);
  gate_set_intr_gate(&idt[0x27], KERNEL_CS, _kernel_ia32__intr7, SYS_PRIV);
  gate_set_intr_gate(&idt[0x28], KERNEL_CS, _kernel_ia32__intr8, SYS_PRIV);
  gate_set_intr_gate(&idt[0x29], KERNEL_CS, _kernel_ia32__intr9, SYS_PRIV);
  gate_set_intr_gate(&idt[0x2a], KERNEL_CS, _kernel_ia32__intr10, SYS_PRIV);
  gate_set_intr_gate(&idt[0x2b], KERNEL_CS, _kernel_ia32__intr11, SYS_PRIV);
  gate_set_intr_gate(&idt[0x2c], KERNEL_CS, _kernel_ia32__intr12, SYS_PRIV);
  gate_set_intr_gate(&idt[0x2d], KERNEL_CS, _kernel_ia32__intr13, SYS_PRIV);
  gate_set_intr_gate(&idt[0x2e], KERNEL_CS, _kernel_ia32__intr14, SYS_PRIV);
  gate_set_intr_gate(&idt[0x2f], KERNEL_CS, _kernel_ia32__intr15, SYS_PRIV);

  for(i=0x30;i<=0xff;++i)
    gate_set_trap_gate(&idt[i], KERNEL_CS, _user_trap_entries[i]-0x30, SYS_PRIV);

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
static void
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
