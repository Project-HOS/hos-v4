/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ��¸��������إå� �����ƥ���ִ���                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */

#ifndef __HOS_V4__knl_sys_h__
#define __HOS_V4__knl_sys_h__


#include "knl_hos.h"
#include "knl_tsk.h"


/* ------------------------------------------ */
/*                  ������                  */
/* ------------------------------------------ */

/* �С��������� */
#define TKERNEL_MAKER	0x0008				/* �᡼����������(�Ŀ�) */
#define TKERNEL_PRID	0x0000				/* �����ͥ�μ����ֹ�(̤��) */
#define TKERNEL_SPVER	0x5401				/* ITRON���ͤΥС������(��ITRON Ver 4.01) */
#define TKERNEL_PRVER	0x0001				/* �����ͥ�ΥС�������ֹ� (HOS-V4 Ver 0.01) */



/* ------------------------------------------ */
/*                 �����                     */
/* ------------------------------------------ */

/* �С��������� */
typedef struct t_rver
{
	UH    maker;		/* �����ͥ�Υ᡼���������� */
	UH    prid;			/* �����ͥ�μ����ֹ� */
	UH    spver;		/* ITRON���ͤΥС��������� */
	UH    prver;		/* �����ͥ�ΥС�������ֹ� */
	UH    prno[4];		/* �����ͥ����ʤδ������� */
} T_RVER;



#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

/* �����ƥ���ִ�����ǽ */
ER      rot_rdq(PRI tskpri);						/* ������ͥ���̤β�ž */
#define irot_rdq	rot_rdq							/* ������ͥ���̤β�ž(�󥿥�������ƥ������ѥޥ���) */
ER      get_tid(ID *p_tskid);						/* �¹Ծ��֥�����ID�λ��� */
ID      kernel_get_tid(T_KERNEL_TCB_RAM *tcb_ram);	/* ������ID�μ���(�����ͥ������ؿ�) */
ER      loc_cpu(void);								/* CPU��å����֤ؤΰܹ� */
#define iloc_cpu	loc_cpu							/* CPU��å����֤ؤΰܹ�(�󥿥�������ƥ������ѥޥ���) */
ER      unl_cpu(void);								/* CPU��å����֤β�� */
#define iunl_cpu	unl_cpu							/* CPU��å����֤β��(�󥿥�������ƥ������ѥޥ���)  */
ER      dis_dsp(void);								/* �ǥ����ѥå��ζػ� */
ER      ena_dsp(void);								/* �ǥ����ѥå��ε��� */
BOOL    sns_ctx(void);								/* ����ƥ����Ȥλ��� */
BOOL    sns_loc(void);								/* CPU��å����֤λ��� */
BOOL    sns_dsp(void);								/* �ǥ����ѥå��ػ߾��֤λ��� */
BOOL    sns_dpn(void);								/* �ǥ����ѥå���α���֤λ��� */

/* �����ƥ๽��������ǽ */
ER      ref_ver(T_RVER *pk_rver);					/* �С�������ֹ�λ��� */


#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_sys_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
