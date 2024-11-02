/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    プロセッサ抽象化コンポーネント(IA32用)                                */
/*    ディスクリプタ定義                                                    */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#ifndef __HOS_V4__IA32__descriptor_h__
#define __HOS_V4__IA32__descriptor_h__

/* セグメント属性  */
#define KERNEL_CS    0x8    /*  カーネルコードセグメント  */
#define KERNEL_DS   0x10    /*  カーネルユーザセグメント  */
#define SYS_PRIV       0    /*  システム権限  */
#define MAX_SELECTOR   3    /*  セグメント総数  */
#define MAX_INTR     256    /*  例外/割込み/トラップの総数  */

/* 
 * ディスクリプターテーブル
 * GDTR/IDTR
 */
typedef struct _descriptor_tbl{
  unsigned limit:16;
  unsigned base:32 __attribute__ ((packed));
}descriptor_tbl_t;
/*
 *  セグメント ディスクリプタ
 *  IA32システムプログラミングガイド 3-11ページ以降参照
 */
typedef struct _segment_desc{
  /* セグメント・リミット 15:00  */
  unsigned	limit_low:16;
  /*  ベース・アドレス  23:00(パックしないと切られることに注意)  */
  unsigned	base_low:24;
  /*  タイプ  */
  unsigned	type:4;
  /*  ディスクリプタ・タイプ 0=システムセグメント 1=コード・データ  */
  unsigned	s:1;
  /*  ディスクリプタ特権レベル  */
  unsigned	dpl:2;
  /*  セグメント存在ビット  */
  unsigned	p:1;
  /*  セグメント・リミット 19:16  */
  unsigned	limit_high:4;
  /*  OSで使用されるフィールド  */
  unsigned	avl:1;
  /*  予約ビット(常に0でなければならない)  */
  unsigned	reserved:1;
  /*  オペレーションサイズ 0=16ビット, 1=32ビット */
  unsigned	db:1;
  /*  粒度(グラニュティ)ビット  1=ページ単位, 0=バイト単位  */
  unsigned	g:1;
  /*  ベース・アドレス  31:24  */
  unsigned	base_high:8;
} __attribute__ ((packed)) segment_desc_t;
/*
 *  ゲート ディスクリプタ
 *  IA32システムプログラミングガイド 3-17ページ, 5-14ページ
 */
/*  gate descriptor  */
typedef struct _gate_desc{
  /*  オフセットの下位ワード(15:00) */
  unsigned	offset_low:16;
  /*  セグメント・セレクタ  */
  unsigned	selector:16;
  /*  コピーカウント  */
  unsigned	copy_count:8;
  /*  タイプ  */
  unsigned	type:4;
  /*  予約ビット  */
  unsigned	reserved:1;
  /*  権限  */
  unsigned	dpl:2;
  /*  セグメント存在ビット  */
  unsigned	p:1;
  /*  オフセットの上位ワード(31:16)  */
  unsigned	offset_high:16;
}gate_desc_t;
/*
 *  IA32セグメントタイプ  
 */
/*  読み取り専用, アクセス無し, エキスパンドアップ データセグメント  */
#define _RO_NOACS_XPDUP_DATA_TYPE  0x0  
/*  読み取り専用, アクセス, エキスパンドアップ データセグメント  */
#define _RO_ACSED_XPDUP_DATA_TYPE  0x1
/*  読み書き, アクセス無し, エキスパンドアップ データセグメント  */
#define _RW_NOACS_XPDUP_DATA_TYPE  0x2
/*  読み書き, アクセス, エキスパンドアップ データセグメント  */
#define _RW_ACSED_XPDUP_DATA_TYPE  0x3
/*  読み取り専用, アクセス無し, エキスパンドダウン データセグメント  */
#define _RO_NOACS_XPDDW_DATA_TYPE  0x4
/*  読み取り専用, アクセス, エキスパンドダウン データセグメント  */
#define _RO_ACSED_XPDDW_DATA_TYPE  0x5
/*  読み書き, アクセス無し, エキスパンドダウン データセグメント  */
#define _RW_NOACS_XPDDW_DATA_TYPE  0x6
/*  読み書き, アクセス, エキスパンドダウン データセグメント  */
#define _RW_ACSED_XPDDW_DATA_TYPE  0x7
/*  実行専用, アクセス無し, 非コンフォーミング コードセグメント  */
#define _RO_NOACS_NOCON_CODE_TYPE  0x8
/*  実行専用, アクセス, 非コンフォーミング コードセグメント  */
#define _RO_ACSED_NOCON_CODE_TYPE  0x9
/*  実行・読み取り, アクセス無し, 非コンフォーミング コードセグメント  */
#define _RW_NOACS_NOCON_CODE_TYPE  0xa
/*  実行・読み取り, アクセス, 非コンフォーミング コードセグメント  */
#define _RW_ACSED_NOCON_CODE_TYPE  0xb
/*  実行専用, アクセス無し, コンフォーミング コードセグメント  */
#define _RO_NOACS_CONFM_CODE_TYPE  0xc
/*  実行専用, アクセス, コンフォーミング コードセグメント  */
#define _RO_ACSED_CONFM_CODE_TYPE  0xd
/*  実行・読み取り, アクセス無し, コンフォーミング コードセグメント  */
#define _RW_NOACS_CONFM_CODE_TYPE  0xe
/*  実行・読み取り, アクセス, コンフォーミング コードセグメント  */
#define _RW_ACSED_CONFM_CODE_TYPE  0xf
/*
 *  HOS で利用するセグメント定義
 */
/*  コードセグメント  */
#define CODE_SEG_TYPE  _RW_NOACS_NOCON_CODE_TYPE
/*  データセグメント  */
#define DATA_SEG_TYPE  _RW_NOACS_XPDUP_DATA_TYPE
/*  スタックセグメント  */
#define STACK_SEG_TYPE _RW_NOACS_XPDDW_DATA_TYPE

/*
 *  権限
 */
#define KERNEL_PRIV  0x0
#define USER_PRIV    0x3

/*  ゲートタイプ  */
#define TASK_GATE_TYPE  0x5  /*  タスクゲート  */
#define CALL_GATE_TYPE  0xc  /*  コールゲート  */
#define INTR_GATE_TYPE  0xe  /*  割り込みゲート  */
#define TRAP_GATE_TYPE  0xf  /*  割り込みゲート  */

/*  セグメント設定マクロ  */
#define _cast_desc(d,item) (((segment_desc_t *)d)->item)
#define define_region(desc, _addr, _limit, _type, _dpl)  do{                  \
  _cast_desc(desc, base_low) = ( ( (unsigned long)_addr ) & (0xffffff) );     \
  _cast_desc(desc, base_high) = ( ( ( (unsigned long)_addr) >> 24) & (0xff) );\
  _cast_desc(desc, limit_low) = ( ((unsigned long)_limit) & (0xffff) );       \
 _cast_desc(desc, limit_high) = ((((unsigned long)_limit) >> (16) ) & (0xf) );\
  _cast_desc(desc, type) = ( ((unsigned char)_type) & (0xf));                 \
  _cast_desc(desc, s) = 1;  /*  コード・データセグメント  */                  \
  _cast_desc(desc, dpl)= ( ( (unsigned char)_dpl )&(0x3));                    \
  _cast_desc(desc, p) = 1;  /* 存在するものとする  */                         \
  _cast_desc(desc, avl)=0;  /*  とりあえず使う予定は無い  */                  \
  _cast_desc(desc, reserved)=0;  /*  予約ビット  */                           \
  _cast_desc(desc, db) = 1; /*  32ビットセグメント  */                        \
  _cast_desc(desc, g) = 1;  /*  32ビット全域をアクセスするのでページ単位  */  \
}while(0)

/*
 *  ゲート ディスクリプタ操作マクロ
 *  IA32システムプログラミングガイド 3-17ページ, 5-14ページ
 */
/* ゲート設定マクロ  */
#define _cast_gate(d, i) (((gate_desc_t *)d)->i)

#define __set_gate(desc, _sel, _offset, _dpl, gtype) do{                     \
  _cast_gate(desc, offset_low)= ((unsigned long)(_offset)) & 0xffff;         \
  _cast_gate(desc, offset_high)= (((unsigned long)(_offset)) >>16)&(0xffff); \
  _cast_gate(desc, selector) = _sel;                                         \
  _cast_gate(desc, copy_count) = 0;                                          \
  _cast_gate(desc, type) = (gtype);                                          \
  _cast_gate(desc, reserved) = 0;                                            \
  _cast_gate(desc, dpl) = _dpl;                                              \
  _cast_gate(desc, p) = 1;                                                   \
  }while(0)

/*  割り込みゲート設定  */
#define gate_set_intr_gate(desc, _sel, _offset, _dpl) do{                   \
    __set_gate(desc, _sel, _offset, _dpl, INTR_GATE_TYPE);                  \
}while(0)
/*  トラップゲート設定  */
#define gate_set_trap_gate(desc, _sel, _offset, _dpl) do{                   \
    __set_gate(desc, _sel, _offset, _dpl, TRAP_GATE_TYPE);                  \
}while(0)
/*  コールゲート設定  */
#define gate_set_call_gate(desc, _sel, _offset, _dpl) do{                   \
    __set_gate(desc, _sel, _offset, _dpl, CALL_GATE_TYPE);                  \
}while(0)

/*  ベクタテーブルロード  */
#define load_idtr(idtr)  __asm__ __volatile__( \
                      "movl %0, %%eax\n\t" \
                      "lidt (%%eax)\n\t"   \
                      :/* no output  */    \
                      :"g"(&idtr)          \
                      :"%eax")

/*  フラグの消去  */
#define init_eflags() do {                   \
   __asm__ __volatile__("pushl $2\n\t"       \
			"popf");             \
  } while(0)

/*  Global Description Tableの読み込み  */
#define load_gdtr(gdtr) do {                 \
   __asm__ __volatile__("movl %0, %%eax\n\t" \
      "lgdt (%%eax)\n\t"                     \
      "ljmp $0x8,$next\n\t"                  \
      "next:\n\t"                            \
      "movw $0x10,%%ax\n\t"                  \
      "movw %%ax, %%ds\n\t"                  \
      "movw %%ax, %%es\n\t"                  \
      "movw %%ax,%%fs\n\t"                   \
      "movw %%ax,%%gs\n\t"                   \
      "movw %%ax, %%ss\n\t"                  \
     :/* no output  */:"g"(&(gdtr)):"%eax"); \
  } while (0)

#endif  /*  __HOS_V4__IA32__descriptor_h__  */
/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
