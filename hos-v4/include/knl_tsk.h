/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �����ͥ��¸��������إå� ����������                                 */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_tsk_h__
#define __HOS_V4__knl_tsk_h__


#include "knl_hos.h"



/* ------------------------------------------ */
/*                  ������                  */
/* ------------------------------------------ */

/* ID���ϰ� */
#define TMIN_TSKID		1					/* ������ID�κǾ��� */
#define TMAX_TSKID		(TMIN_TSKID + kernel_tcb_cnt - 1)

/* �ӥåȥѥ�����Υӥåȿ� */
#define TBIT_TEXPTN		16					/* �������㳰�װ��Υӥåȿ� */
											/* ������ID�κ����� */


/* ���塼���󥰡��ͥ��Ȳ���κ����� */
#define TMAX_ACTCNT		255					/* ��������ư�׵ᥭ�塼���󥰿��κ����� */
#define TMAX_WUPCNT		65535				/* �����������׵ᥭ�塼���󥰿��κ����� */
#define TMAX_SUSCNT		255					/* �����������Ԥ��׵�ͥ��ȿ��κ����� */



/* ------------------------------------------ */
/*                 �����                     */
/* ------------------------------------------ */

/* �������������� */
typedef struct t_ctsk
{
	ATR     tskatr;			/* ������°�� */
	VP_INT  exinf;			/* �������γ�ĥ���� */
	FP      task;			/* �������ε�ư���� */
	PRI     itskpri;		/* �������ε�ư��ͥ���� */
	SIZE    stksz;			/* �����å��ΰ�Υ�����(�Х��ȿ�) */
	VP      stk;			/* �����å��ΰ����Ƭ���� */
} T_CTSK;

/* ���������� */
typedef struct t_rtsk
{
	STAT   tskstat;			/* ���������� */
	PRI    tskpri;			/* �������θ���ͥ���� */
	PRI	   tskbpri;			/* �������Υ١���ͥ���� */
	STAT   tskwait;			/* �Ԥ��װ� */
	ID     wobjid;			/* �Ԥ��оݤΥ��֥������Ȥ�ID�ֹ� */
	TMO    lefttmo;			/* �����ॢ���Ȥ���ޤǤλ��� */
	UINT   actcnt;			/* ��ư�׵ᥭ�塼���󥰲�� */
	UINT   wupcnt;			/* �����׵ᥭ�塼���󥰲�� */
	UINT   suscnt;			/* �����Ԥ��׵�ͥ��Ȳ�� */
	VP_INT exinf;			/* �������γ�ĥ���� */
} T_RTSK;

/* ����������(�ʰ���) */
typedef struct t_rtst
{
	STAT   tskstat;			/* ���������� */
	STAT   tskwait;			/* �Ԥ��װ� */
	VP_INT exinf;			/* �������γ�ĥ���� */
} T_RTST;


/* �������㳰��������ȥ���֥�å�(RAM��) */
typedef struct t_kernel_texcb_ram
{
	TEXPTN rasptn;			/* �������㳰�����Υ������㳰�װ� */
	FP     texrtn;			/* �������㳰�����ε�ư���� */
} T_KERNEL_TEXCB_RAM;


/* ����������ȥ���֥�å�(ROM��) */
typedef struct t_kernel_tcb_rom
{
	ATR    tskatr;			/* ������°�� */
	VP_INT exinf;			/* �������γ�ĥ���� */
	FP     task;			/* �������ε�ư���� */
	PRI    itskpri;			/* �������ε�ư��ͥ���� */
	SIZE   stksz;			/* �������Υ����å��Υ������ʥХ��ȿ��� */
	VP	   stk;				/* �������Υ����å��ΰ����Ƭ���� */
} T_KERNEL_TCB_ROM;


/* ����������ȥ���֥�å�(RAM��) */
typedef struct t_kernel_tcb_ram
{
	T_MKNL_TCB mtcb;		/* �̥����ͥ� ����������ȥ���֥�å� */	
	UB         actcnt;		/* ��ư�׵ᥭ�塼���󥰿� */
	UB         suscnt;		/* SUSPEND�׵�ͥ��ȿ� */
	UH         wupcnt;		/* �����׵ᥭ�塼���󥰿� */
	T_KERNEL_TEXCB_RAM     *texcb;		/* �������㳰��������ȥ���֥�å��ؤΥݥ��� */
	const T_KERNEL_TCB_ROM *tcb_rom;	/* ����������ȥ���֥�å�ROM���ؤΥݥ��� */
} T_KERNEL_TCB_RAM;



#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------- */
/*        �����Х��ѿ����          */
/* ---------------------------------- */

/* ���������� */
extern       T_KERNEL_TCB_RAM* kernel_tcb_ram_tbl[];		/* ����������ȥ���֥�å��ơ��֥�(RAM��) */
extern const INT kernel_tcb_cnt;							/* ����������ȥ���֥�å��Ŀ� */

/* �Ѵ��ޥ��� */
#define KERNEL_TSKID_TO_TCB_RAM(tskid)	(kernel_tcb_ram_tbl[(tskid) - TMIN_TSKID])
															/* ������ID����TCB RAM���ɥ쥹����� */



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

/* ������������ǽ */
void    kernel_ini_tsk(void);								/* �������ν���� */
ER      cre_tsk(ID tskid, const T_CTSK *pk_ctsk);			/* ������������ */
ER_ID   acre_tsk(const T_CTSK *pk_ctsk);					/* ������������(ID�ֹ漫ư���դ�) */
ER      kernel_cre_tsk(ID tskid, const T_CTSK *pk_ctsk);	/* ����������(�����ͥ�����) */
ER      del_tsk(ID tskid);									/* �������κ�� */
ER      act_tsk(ID tskid);									/* �������ε�ư */
#define	iact_tsk	act_tsk									/* �������ε�ư(�󥿥�������ƥ������ѥޥ���) */
ER_UINT can_act(ID tskid);									/* ��������ư�׵�Υ���󥻥� */
ER      sta_tsk(ID tskid, VP_INT stacd);					/* �������ε�ư(��ư�����ɻ���) */
void    ext_tsk(void);										/* ���������ν�λ */
void    exd_tsk(void);										/* ���������ν�λ�Ⱥ�� */
ER      ter_tsk(ID tskid);									/* �������ζ�����λ */
ER      chg_pri(ID tskid, PRI tskpri);						/* ������ͥ���٤��ѹ� */
ER      get_pri(ID tskid, PRI *p_tskpri);					/* ������ͥ���٤λ��� */
ER      ref_tsk(ID tskid, T_RTSK *p_rtsk);					/* �������ξ��ֻ��� */
ER      ref_tst(ID tskid, T_RTST *p_rtst);					/* �������ξ��ֻ���(�ʰ���) */

/* ��������°Ʊ����ǽ */
ER      slp_tsk(void);										/* �������ε����Ԥ� */
ER      tslp_tsk(TMO tmout);								/* �������ε����Ԥ�(�����ॢ���Ȥ���) */
ER      wup_tsk(ID tskid);									/* �������ε��� */
#define	iwup_tsk	wup_tsk									/* �������ε���(�󥿥�������ƥ������ѥޥ���) */
ER_UINT can_wup(ID tskid);									/* �����������׵�Υ���󥻥� */
ER      rel_wai(ID tskid);									/* �Ԥ����֤ζ������ */
#define	irel_wai	rel_wai									/* �Ԥ����֤ζ������(�󥿥�������ƥ������ѥޥ���) */
ER      sus_tsk(ID tskid);									/* �����Ԥ����֤ؤΰܹ� */
ER      rsm_tsk(ID tskid);									/* �����Ԥ����֤���κƳ� */
ER      frsm_tsk(ID tskid);									/* �����Ԥ����֤���ζ����Ƴ� */
ER      dly_tsk(RELTIM dlytim);								/* �����������ٱ� */

/* �������㳰������ǽ */
ER      ras_tex(ID tskid, TEXPTN rasptn);					/* �������㳰�������׵� */
#define iras_tex	ras_tex									/* �������㳰�������׵�(�󥿥�������ƥ������ѥޥ���) */
ER      dis_tex(void);										/* �������㳰�����ζػ� */
ER      ena_tex(void);										/* �������㳰�����ζػ� */
BOOL    sns_tex(void);										/* �������㳰�����ػ߾��֤λ��� */



#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_tsk_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
