/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ��¸��������إå� �����ϥ�ɥ�                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_cyc_h__
#define __HOS_V4__knl_cyc_h__



#include "knl_hos.h"
#include "knl_tim.h"



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
	T_KERNEL_TIM timobj;		/* �����ޥ��֥������Ȥ�Ѿ� */
	RELTIM       lefttim;		/* �����ϥ�ɥ�Τ򼡤˵�ư�������ޤǤλ��� */
	const T_KERNEL_CYCCB_ROM *cyccb_rom;	/* �����ϥ�ɥ饳��ȥ���֥�å�ROM���ؤΥݥ��� */
} T_KERNEL_CYCCB_RAM;



/* ---------------------------------- */
/*        �����Х��ѿ����          */
/* ---------------------------------- */

/* �����ϥ�ɥ� */
extern       T_KERNEL_CYCCB_RAM *kernel_cyccb_ram_tbl[];	/* �����ϥ�ɥ饳��ȥ���֥�å��ơ��֥� */
extern const INT kernel_cyccb_cnt;							/* �����ϥ�ɥ饳��ȥ���֥�å��Ŀ� */

#define KERNEL_CYCID_TO_CYCCB_RAM(cycid)	(kernel_cyccb_ram_tbl[(cycid) - TMIN_CYCID])
															/* �����ϥ�ɥ�ID����CYCCB RAM���ɥ쥹����� */



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* �����ϥ�ɥ� */
void    kernel_ini_cyc(void);								/* �����ϥ�ɥ�ν���� */
void    kernel_cyc_hdr(T_KERNEL_TIM *timobj, RELTIM tic);	/* �����ϥ�ɥ�Υ����ޥϥ�ɥ� */
ER      sta_cyc(ID cycid);									/* �����ϥ�ɥ��ư��� */
ER      stp_cyc(ID cycid);									/* �����ϥ�ɥ��ư����� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_cyc_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
