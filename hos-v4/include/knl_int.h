/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �����ͥ��¸��������إå� �����ߴ���                               */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_int_h__
#define __HOS_V4__knl_int_h__



/* ------------------------------------------ */
/*                  ������                  */
/* ------------------------------------------ */

/* �������ֹ���ϰ� */
#define TMIN_INTNO		(kernel_min_intno)	/* �������ֹ�κǾ��� */
#define TMAX_INTNO		(TMIN_INTNO + kernel_intcb_cnt - 1)
											/* �������ֹ�κ����� */

/* ID���ϰ� */
#define TMIN_ISRID		1					/* �����ߥ����ӥ��롼����ID�κǾ��� */
#define TMAX_ISRID		(TMIN_ISRID - kernel_isrcb_cnt - 1)
											/* �����ߥ����ӥ��롼����ID�κ����� */



/* ------------------------------------------ */
/*                 �����                     */
/* ------------------------------------------ */

/* �����ߴ�������ȥ�����֥��å� */
typedef struct t_kernel_intcb
{
	VP_INT exinf;		/* �����ߥ����ӥ��롼����γ�ĥ���� */
	FP     isr;			/* �����ߥ����ӥ��롼����ε�ư���� */
} T_KERNEL_INTCB;


/* �����ߥϥ�ɥ������� */
typedef struct t_dinh
{
	ATR inhatr;			/* �����ߥϥ�ɥ�°�� */
	FP  inthdr;			/* �����ߥϥ�ɥ�ε�ư���� */
} T_DINH;


/* �����ߥ����ӥ��롼���󥳥�ȥ�����֥��å� */
typedef struct t_kernel_isrcb
{
	INTNO  intno;		/* �������ֹ� */
} T_KERNEL_ISRCB;



/* ---------------------------------- */
/*        �������Х��ѿ����          */
/* ---------------------------------- */

/* �����ߴ��� */
extern T_KERNEL_INTCB  kernel_intcb_tbl[];	/* �����ߴ�������ȥ�����֥��å��ơ��֥� */
extern const INT       kernel_intcb_cnt;	/* �������ֹ�� */
extern const INTNO     kernel_min_intno;	/* �������ֹ�Ǿ��� */

/* �����ߥ����ӥ��롼���� */
extern T_KERNEL_ISRCB* kernel_isrcb_tbl[];	/* �����ߥ����ӥ��롼���󥳥�ȥ�����֥��å��ơ��֥� */
extern const INT       kernel_isrcb_cnt;	/* �����ߥ����ӥ��롼���󥳥�ȥ�����֥��å��θĿ� */



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* ���������� */
void    kernel_sta_int(void);						/* �����ߥ���ƥ����ȳ��Ͻ��� */
void    kernel_end_int(void);						/* �����ߥ���ƥ����Ƚ�λ���� */

/* �����ߴ��� */
void    kernel_exe_int(INTNO intno);				/* �����߽����¹� */
ER      dis_int(INTNO intno);						/* �����ߤζػ� */
ER      ena_int(INTNO intno);						/* �����ߤε��� */


/* �����ߥϥ�ɥ� */
ER      def_inh(INTNO intno, T_DINH *pk_dinh);		/* �����ߥϥ�ɥ���� */


/* �����ߥ����ӥ��롼���� */
/*
ER      cre_isr();
ER      acre_isr();
*/

#ifdef __cplusplus
}
#endif



#endif	/*  __HOS_V4__knl_int_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */