/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ��¸��������إå� ����Ĺ����ס���                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_mpf_h__
#define __HOS_V4__knl_mpf_h__


#include "knl_hos.h"



/* ------------------------------------------ */
/*                  ������                  */
/* ------------------------------------------ */

/* ID���ϰ� */
#define TMIN_MPFID		1					/* ����Ĺ����ס���ID�κǾ��� */
#define TMAX_MPFID		(TMIN_MPFID + kernel_mpfcb_cnt - 1)
											/* ����Ĺ����ס���ID�κ����� */



/* ------------------------------------------ */
/*                 �����                     */
/* ------------------------------------------ */

/* ����Ĺ����ס����������� */
typedef struct t_cmpf
{
	ATR  mpfatr;		/* ����Ĺ����ס���°�� */
	UINT blkcnt;		/* �����Ǥ������֥�å���(�Ŀ�) */
	UINT blksz;			/* ����֥�å��Υ�����(�Х��ȿ�) */
	VP   mpf;			/* ����Ĺ����ס����ΰ����Ƭ���� */
} T_CMPF;

/* ����Ĺ����ס������ */
typedef struct t_rmpf
{
	ID   wtskid;		/* ����Ĺ����ס�����Ԥ��������Ƭ�Υ�������ID�ֹ� */
	UINT fblkcnt;		/* ����Ĺ����ס���ζ�������֥�å���(�Ŀ�) */
} T_RMPF;


/* ����Ĺ����ס��륳��ȥ���֥�å�(ROM��) */
typedef struct t_kernel_mpfcb_rom
{
	ATR  mpfatr;		/* ����Ĺ����ס���°�� */
	UINT blkcnt;		/* �����Ǥ������֥�å���(�Ŀ�) */
	UINT blksz;			/* ����֥�å��Υ�����(�Х��ȿ�) */
	VP   mpf;			/* ����Ĺ����ס����ΰ����Ƭ���� */
} T_KERNEL_MPFCB_ROM;


/* ����Ĺ����ס��륳��ȥ���֥�å�(RAM��) */
typedef struct t_kernel_mpfcb_ram
{
	T_MKNL_QUE que;		/* ����Ĺ����ס����Ԥ����������塼 */
	VP         free;	/* �����֥�å��ؤΥݥ��� */
	const T_KERNEL_MPFCB_ROM *mpfcb_rom;	/* ����Ĺ����ס��륳��ȥ���֥�å�ROM���ؤΥݥ��� */
} T_KERNEL_MPFCB_RAM;



/* ---------------------------------- */
/*        �����Х��ѿ����          */
/* ---------------------------------- */

/* ����Ĺ����ס������ */
extern       T_KERNEL_MPFCB_RAM *kernel_mpfcb_ram_tbl[];	/* ����Ĺ����ס��륳��ȥ���֥�å��ơ��֥�(RAM��) */
extern const INT kernel_mpfcb_cnt;							/* ����Ĺ����ס��륳��ȥ���֥�å��Ŀ� */

/* ����Ĺ����ס��륳��ȥ���֥�å��Ѵ��ޥ��� */
#define KERNEL_MPFID_TO_MPFCB_RAM(mpfid)	(kernel_mpfcb_ram_tbl[(mpfid) - TMIN_MPFID])
															/* ����Ĺ����ס���ID����MPFCB RAM���ɥ쥹����� */



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* ����Ĺ����ס��� */
void    kernel_ini_mpf(void);								/* ����Ĺ����ס���ν���� */
ER      cre_mpf(ID mpfid, const T_CMPF *pk_cmpf);			/* ����Ĺ����ס�������� */
ER_ID   acre_mpf(const T_CMPF *pk_cmpf);					/* ����Ĺ����ס��������(ID�ֹ漫ư���դ�) */
ER      kernel_cre_mpf(ID mpfid, const T_CMPF *pk_cmpf);	/* ����Ĺ����ס��������(�����ͥ������ؿ�) */
ER      del_mpf(ID mpfid);									/* ����Ĺ����ס���κ�� */
ER      get_mpf(ID mpfid, VP *p_blk);						/* ����Ĺ����֥�å��γ��� */
ER      pget_mpf(ID mpfid, VP *p_blk);						/* ����Ĺ����֥�å��γ���(�ݡ����) */
ER      tget_mpf(ID mpfid, VP *p_blk, TMO tmout);			/* ����Ĺ����֥�å��γ���(�����ॢ���Ȥ���) */
ER      rel_mpf(ID mpfid, VP blk);							/* ����Ĺ����֥�å����ֵ� */
ER      ref_mpf(ID mpfid, T_RMPF *pk_rmpf);					/* ����Ĺ����֥�å��ξ��ֻ��� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_mpf_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
