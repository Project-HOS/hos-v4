/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �����ͥ��¸��������إå� ���ִ���                                   */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_tim_h__
#define __HOS_V4__knl_tim_h__



/* ------------------------------------------ */
/*                  ������                  */
/* ------------------------------------------ */

/* ID���ϰ� */
#define TMIN_CYCID		1					/* �����ϥ�ɥ�ID�κǾ��� */
#define TMAX_CYCID		(TMIN_CYCID + kernel_cyccb_cnt - 1)
											/* �����ϥ�ɥ�ID�κ����� */



/* ------------------------------------------ */
/*                 �����                     */
/* ------------------------------------------ */

/* �����ϥ�ɥ饳��ȥ���֥�å�(ROM��) */
typedef struct t_kernel_cyccb_rom
{
	ATR    cycatr;		/* �����ϥ�ɥ�°�� */
	VP_INT exinf;		/* �����ϥ�ɥ�γ�ĥ���� */
	FP     cychdr;		/* �����ϥ�ɥ�ε�ư���� */
	RELTIM cyctim;		/* �����ϥ�ɥ�ε�ư���� */
} T_KERNEL_CYCCB_ROM;

/* �����ϥ�ɥ饳��ȥ���֥�å�(RAM��) */
typedef struct t_kernel_cyccb_ram
{
	RELTIM lefttim;		/* �����ϥ�ɥ�Τ򼡤˵�ư�������ޤǤλ��� */
	STAT   cycstat;		/* �����ϥ�ɥ��ư����� */
	const T_KERNEL_CYCCB_ROM  *cyccbrom;	/* �����ϥ�ɥ饳��ȥ���֥�å�ROM���ؤΥݥ��� */
} T_KERNEL_CYCCB_RAM;



#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------- */
/*        �����Х��ѿ����          */
/* ---------------------------------- */

/* �����ƥ������� */
extern const UW     kernel_tic_deno;	/* ����ե�����졼������ TIC_DENO ������ */
extern const UW     kernel_tic_div;		/* ����ե�����졼������ TIC_NUME / TIC_DENO ������ */
extern const UW     kernel_tic_mod;		/* ����ե�����졼������ TIC_NUME % TIC_DENO ������ */
extern       UW     kernel_tic_cnt;		/* ������ƥ��å��ѥ����� */
extern       SYSTIM kernel_systim;		/* �����ƥ���� */


/* �����ϥ�ɥ� */
extern       T_KERNEL_CYCCB_RAM *kernel_cyccb_ram_tbl[];	/* �����ϥ�ɥ饳��ȥ���֥�å��ơ��֥� */
extern const INT kernel_cyccb_cnt;							/* �����ϥ�ɥ饳��ȥ���֥�å��Ŀ� */

#define KERNEL_CYCID_TO_CYCCB_RAM(cycid)	(kernel_cyccb_ram_tbl[(cycid) - TMIN_CYCID])
															/* �����ϥ�ɥ�ID����CYCCB RAM���ɥ쥹����� */



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

/* �����ƥ������� */
void    kernel_ini_tim(void);						/* ���ִ�����ǽ�ν���� */
ER      set_tim(const SYSTIM *p_systim);			/* �����ƥ��������� */
ER      get_tim(SYSTIM *p_systim);					/* �����ƥ����μ��� */
ER      isig_tim(void);								/* ������ƥ��å��ζ��� */


/* �����ϥ�ɥ� */
void    kernel_ini_cyc(void);						/* �����ϥ�ɥ�ν���� */
ER      sta_cyc(ID cycid);							/* �����ϥ�ɥ��ư��� */
ER      stp_cyc(ID cycid);							/* �����ϥ�ɥ��ư����� */



#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_tim_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
