/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ��¸��������إå� CPU�㳰�ϥ�ɥ����                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_exc_h__
#define __HOS_V4__knl_exc_h__


#include "knl_hos.h"



/* ------------------------------------------ */
/*                  ������                  */
/* ------------------------------------------ */

/* �������ֹ���ϰ� */
#define TMIN_EXCNO		(kernel_min_excno)	/* CPU�㳰�ϥ�ɥ��ֹ�κǾ��� */
#define TMAX_EXCNO		(TMIN_EXCNO + kernel_exccb_cnt - 1)
											/* CPU�㳰�ϥ�ɥ��ֹ�κ����� */



/* ------------------------------------------ */
/*                 �����                     */
/* ------------------------------------------ */

/* CPU�㳰�ϥ�ɥ饳��ȥ���֥�å� */
typedef struct t_kernel_exccb
{
	FP exchdr;			/* CPU�㳰�ϥ�ɥ�ε�ư���� */
} T_KERNEL_EXCCB;



/* ---------------------------------- */
/*        �����Х��ѿ����          */
/* ---------------------------------- */

/*  CPU�㳰�ϥ�ɥ���� */
extern T_KERNEL_EXCCB  kernel_exccb_tbl[];	/* CPU�㳰�ϥ�ɥ饳��ȥ���֥�å��ơ��֥� */
extern const INT       kernel_exccb_cnt;	/* CPU�㳰�ϥ�ɥ��ֹ�� */
extern const EXCNO     kernel_min_excno;	/* CPU�㳰�ϥ�ɥ��ֹ�Ǿ��� */



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* CPU�㳰�ϥ�ɥ���� */
void    kernel_sta_exc(void);			/* CPU�㳰�ϥ�ɥ�γ��� */
void    kernel_end_exc(void);			/* CPU�㳰�ϥ�ɥ�ν�λ */
void    kernel_exe_exc(INTNO excno);	/* CPU�㳰�ϥ�ɥ�����¹� */



#ifdef __cplusplus
}
#endif



#endif	/*  __HOS_V4__knl_exc_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
