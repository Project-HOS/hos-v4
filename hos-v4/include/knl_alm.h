/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ��¸��������إå� ���顼��ϥ�ɥ�                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_alm_h__
#define __HOS_V4__knl_alm_h__



#include "knl_hos.h"
#include "knl_tim.h"



/* ------------------------------------------ */
/*                  ������                  */
/* ------------------------------------------ */

/* ID���ϰ� */
#define TMIN_ALMID		1					/* ���顼��ϥ�ɥ�ID�κǾ��� */
#define KERNEL_TMAX_ALMID		(TMIN_ALMID + kernel_almcb_cnt - 1)
											/* ���顼��ϥ�ɥ�ID�κ����� */



/* ------------------------------------------ */
/*                 �����                     */
/* ------------------------------------------ */

/* ���顼��ϥ�ɥ饳��ȥ���֥�å�(ROM��) */
typedef struct t_kernel_almcb_rom
{
	ATR    almatr;		/* ���顼��ϥ�ɥ�°�� */
	VP_INT exinf;		/* ���顼��ϥ�ɥ�γ�ĥ���� */
	FP     almhdr;		/* ���顼��ϥ�ɥ�ε�ư���� */
} T_KERNEL_ALMCB_ROM;

/* ���顼��ϥ�ɥ饳��ȥ���֥�å�(RAM��) */
typedef struct t_kernel_almcb_ram
{
	T_KERNEL_TIM timobj;		/* �����ޥ��֥������Ȥ�Ѿ� */
	RELTIM       lefttim;		/* ���顼��ϥ�ɥ�Τ򼡤˵�ư�������ޤǤλ��� */
	const T_KERNEL_ALMCB_ROM *almcb_rom;	/* ���顼��ϥ�ɥ饳��ȥ���֥�å�ROM���ؤΥݥ��� */
} T_KERNEL_ALMCB_RAM;



/* ---------------------------------- */
/*        �����Х��ѿ����          */
/* ---------------------------------- */

/* ���顼��ϥ�ɥ� */
extern       T_KERNEL_ALMCB_RAM *kernel_almcb_ram_tbl[];	/* ���顼��ϥ�ɥ饳��ȥ���֥�å��ơ��֥� */
extern const INT kernel_almcb_cnt;							/* ���顼��ϥ�ɥ饳��ȥ���֥�å��Ŀ� */

#define KERNEL_ALMID_TO_ALMCB_RAM(almid)	(kernel_almcb_ram_tbl[(almid) - TMIN_ALMID])
															/* ���顼��ϥ�ɥ�ID����ALMCB RAM���ɥ쥹����� */



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* ���顼��ϥ�ɥ� */
void    kernel_ini_alm(void);								/* ���顼��ϥ�ɥ�ν���� */
void    kernel_alm_hdr(T_KERNEL_TIM *timobj, RELTIM tic);	/* ���顼��ϥ�ɥ�Υ����ޥϥ�ɥ� */
ER      sta_alm(ID almid, RELTIM almtim);					/* ���顼��ϥ�ɥ��ư��� */
ER      stp_alm(ID almid);									/* ���顼��ϥ�ɥ��ư����� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_alm_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
