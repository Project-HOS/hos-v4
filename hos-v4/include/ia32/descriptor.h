/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �ץ��å���ݲ�����ݡ��ͥ��(IA32��)                                */
/*    �ǥ�������ץ����                                                    */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#ifndef __HOS_V4__IA32__descriptor_h__
#define __HOS_V4__IA32__descriptor_h__

/* ��������°��  */
#define KERNEL_CS    0x8    /*  �����ͥ륳���ɥ�������  */
#define KERNEL_DS   0x10    /*  �����ͥ�桼����������  */
#define SYS_PRIV       0    /*  �����ƥย��  */
#define MAX_SELECTOR   3    /*  �����������  */
#define MAX_INTR     256    /*  �㳰/�����/�ȥ�åפ����  */

/* 
 * �ǥ�������ץ����ơ��֥�
 * GDTR/IDTR
 */
typedef struct _descriptor_tbl{
  unsigned limit:16;
  unsigned base:32 __attribute__ ((packed));
}descriptor_tbl_t;
/*
 *  �������� �ǥ�������ץ�
 *  IA32�����ƥ�ץ���ߥ󥰥����� 3-11�ڡ����ʹ߻���
 */
typedef struct _segment_desc{
  /* �������ȡ���ߥå� 15:00  */
  unsigned	limit_low:16;
  /*  �١��������ɥ쥹  23:00(�ѥå����ʤ����ڤ��뤳�Ȥ����)  */
  unsigned	base_low:24;
  /*  ������  */
  unsigned	type:4;
  /*  �ǥ�������ץ��������� 0=�����ƥॻ������ 1=�����ɡ��ǡ���  */
  unsigned	s:1;
  /*  �ǥ�������ץ��ø���٥�  */
  unsigned	dpl:2;
  /*  ��������¸�ߥӥå�  */
  unsigned	p:1;
  /*  �������ȡ���ߥå� 19:16  */
  unsigned	limit_high:4;
  /*  OS�ǻ��Ѥ����ե������  */
  unsigned	avl:1;
  /*  ͽ��ӥå�(���0�Ǥʤ���Фʤ�ʤ�)  */
  unsigned	reserved:1;
  /*  ���ڥ졼����󥵥��� 0=16�ӥå�, 1=32�ӥå� */
  unsigned	db:1;
  /*  γ��(����˥�ƥ�)�ӥå�  1=�ڡ���ñ��, 0=�Х���ñ��  */
  unsigned	g:1;
  /*  �١��������ɥ쥹  31:24  */
  unsigned	base_high:8;
} __attribute__ ((packed)) segment_desc_t;
/*
 *  ������ �ǥ�������ץ�
 *  IA32�����ƥ�ץ���ߥ󥰥����� 3-17�ڡ���, 5-14�ڡ���
 */
/*  gate descriptor  */
typedef struct _gate_desc{
  /*  ���ե��åȤβ��̥��(15:00) */
  unsigned	offset_low:16;
  /*  �������ȡ����쥯��  */
  unsigned	selector:16;
  /*  ���ԡ��������  */
  unsigned	copy_count:8;
  /*  ������  */
  unsigned	type:4;
  /*  ͽ��ӥå�  */
  unsigned	reserved:1;
  /*  ����  */
  unsigned	dpl:2;
  /*  ��������¸�ߥӥå�  */
  unsigned	p:1;
  /*  ���ե��åȤξ�̥��(31:16)  */
  unsigned	offset_high:16;
}gate_desc_t;
/*
 *  IA32�������ȥ�����  
 */
/*  �ɤ߼������, ��������̵��, �������ѥ�ɥ��å� �ǡ�����������  */
#define _RO_NOACS_XPDUP_DATA_TYPE  0x0  
/*  �ɤ߼������, ��������, �������ѥ�ɥ��å� �ǡ�����������  */
#define _RO_ACSED_XPDUP_DATA_TYPE  0x1
/*  �ɤ߽�, ��������̵��, �������ѥ�ɥ��å� �ǡ�����������  */
#define _RW_NOACS_XPDUP_DATA_TYPE  0x2
/*  �ɤ߽�, ��������, �������ѥ�ɥ��å� �ǡ�����������  */
#define _RW_ACSED_XPDUP_DATA_TYPE  0x3
/*  �ɤ߼������, ��������̵��, �������ѥ�ɥ����� �ǡ�����������  */
#define _RO_NOACS_XPDDW_DATA_TYPE  0x4
/*  �ɤ߼������, ��������, �������ѥ�ɥ����� �ǡ�����������  */
#define _RO_ACSED_XPDDW_DATA_TYPE  0x5
/*  �ɤ߽�, ��������̵��, �������ѥ�ɥ����� �ǡ�����������  */
#define _RW_NOACS_XPDDW_DATA_TYPE  0x6
/*  �ɤ߽�, ��������, �������ѥ�ɥ����� �ǡ�����������  */
#define _RW_ACSED_XPDDW_DATA_TYPE  0x7
/*  �¹�����, ��������̵��, �󥳥�ե����ߥ� �����ɥ�������  */
#define _RO_NOACS_NOCON_CODE_TYPE  0x8
/*  �¹�����, ��������, �󥳥�ե����ߥ� �����ɥ�������  */
#define _RO_ACSED_NOCON_CODE_TYPE  0x9
/*  �¹ԡ��ɤ߼��, ��������̵��, �󥳥�ե����ߥ� �����ɥ�������  */
#define _RW_NOACS_NOCON_CODE_TYPE  0xa
/*  �¹ԡ��ɤ߼��, ��������, �󥳥�ե����ߥ� �����ɥ�������  */
#define _RW_ACSED_NOCON_CODE_TYPE  0xb
/*  �¹�����, ��������̵��, ����ե����ߥ� �����ɥ�������  */
#define _RO_NOACS_CONFM_CODE_TYPE  0xc
/*  �¹�����, ��������, ����ե����ߥ� �����ɥ�������  */
#define _RO_ACSED_CONFM_CODE_TYPE  0xd
/*  �¹ԡ��ɤ߼��, ��������̵��, ����ե����ߥ� �����ɥ�������  */
#define _RW_NOACS_CONFM_CODE_TYPE  0xe
/*  �¹ԡ��ɤ߼��, ��������, ����ե����ߥ� �����ɥ�������  */
#define _RW_ACSED_CONFM_CODE_TYPE  0xf
/*
 *  HOS �����Ѥ��륻���������
 */
/*  �����ɥ�������  */
#define CODE_SEG_TYPE  _RW_NOACS_NOCON_CODE_TYPE
/*  �ǡ�����������  */
#define DATA_SEG_TYPE  _RW_NOACS_XPDUP_DATA_TYPE
/*  �����å���������  */
#define STACK_SEG_TYPE _RW_NOACS_XPDDW_DATA_TYPE

/*
 *  ����
 */
#define KERNEL_PRIV  0x0
#define USER_PRIV    0x3

/*  �����ȥ�����  */
#define TASK_GATE_TYPE  0x5  /*  ������������  */
#define CALL_GATE_TYPE  0xc  /*  �����륲����  */
#define INTR_GATE_TYPE  0xe  /*  �����ߥ�����  */
#define TRAP_GATE_TYPE  0xf  /*  �����ߥ�����  */

/*  ������������ޥ���  */
#define _cast_desc(d,item) (((segment_desc_t *)d)->item)
#define define_region(desc, _addr, _limit, _type, _dpl)  do{                  \
  _cast_desc(desc, base_low) = ( ( (unsigned long)_addr ) & (0xffffff) );     \
  _cast_desc(desc, base_high) = ( ( ( (unsigned long)_addr) >> 24) & (0xff) );\
  _cast_desc(desc, limit_low) = ( ((unsigned long)_limit) & (0xffff) );       \
 _cast_desc(desc, limit_high) = ((((unsigned long)_limit) >> (16) ) & (0xf) );\
  _cast_desc(desc, type) = ( ((unsigned char)_type) & (0xf));                 \
  _cast_desc(desc, s) = 1;  /*  �����ɡ��ǡ�����������  */                  \
  _cast_desc(desc, dpl)= ( ( (unsigned char)_dpl )&(0x3));                    \
  _cast_desc(desc, p) = 1;  /* ¸�ߤ����ΤȤ���  */                         \
  _cast_desc(desc, avl)=0;  /*  �Ȥꤢ�����Ȥ�ͽ���̵��  */                  \
  _cast_desc(desc, reserved)=0;  /*  ͽ��ӥå�  */                           \
  _cast_desc(desc, db) = 1; /*  32�ӥåȥ�������  */                        \
  _cast_desc(desc, g) = 1;  /*  32�ӥå�����򥢥���������Τǥڡ���ñ��  */  \
}while(0)

/*
 *  ������ �ǥ�������ץ����ޥ���
 *  IA32�����ƥ�ץ���ߥ󥰥����� 3-17�ڡ���, 5-14�ڡ���
 */
/* ����������ޥ���  */
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

/*  �����ߥ���������  */
#define gate_set_intr_gate(desc, _sel, _offset, _dpl) do{                   \
    __set_gate(desc, _sel, _offset, _dpl, INTR_GATE_TYPE);                  \
}while(0)
/*  �ȥ�åץ���������  */
#define gate_set_trap_gate(desc, _sel, _offset, _dpl) do{                   \
    __set_gate(desc, _sel, _offset, _dpl, TRAP_GATE_TYPE);                  \
}while(0)
/*  �����륲��������  */
#define gate_set_call_gate(desc, _sel, _offset, _dpl) do{                   \
    __set_gate(desc, _sel, _offset, _dpl, CALL_GATE_TYPE);                  \
}while(0)

/*  �٥����ơ��֥����  */
#define load_idtr(idtr)  __asm__ __volatile__( \
                      "movl %0, %%eax\n\t" \
                      "lidt (%%eax)\n\t"   \
                      :/* no output  */    \
                      :"g"(&idtr)          \
                      :"%eax")

#endif  /*  __HOS_V4__IA32__descriptor_h__  */
/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
