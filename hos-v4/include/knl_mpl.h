/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ��¸��������إå� ����Ĺ����ס���                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_mpl_h__
#define __HOS_V4__knl_mpl_h__


#include "knl_hos.h"
#include "knl_hep.h"



/* ------------------------------------------ */
/*                  ������                  */
/* ------------------------------------------ */

/* ID���ϰ� */
#define KERNEL_TMIN_MPLID	TMIN_MPLID			/* ����Ĺ����ס���ID�κǾ��� */
#define KERNEL_TMAX_MPLID	(KERNEL_TMIN_MPLID + kernel_mplcb_cnt - 1)
												/* ����Ĺ����ס���ID�κ����� */



/* ------------------------------------------ */
/*                 �����                     */
/* ------------------------------------------ */

/* ����Ĺ����ס����������� */
typedef struct t_cmpl
{
	ATR  mplatr;		/* ����Ĺ����ס���°�� */
	UINT mplsz;			/* ����Ĺ����ס����ΰ�Υ�����(�Х��ȿ�) */
	VP   mpl;			/* ����Ĺ����ס����ΰ����Ƭ���� */
} T_CMPL;

/* ����Ĺ����ס������ */
typedef struct t_rmpl
{
	ID   wtskid;		/* ����Ĺ����ס�����Ԥ��������Ƭ�Υ�������ID�ֹ� */
	SIZE fmplsz;		/* ����Ĺ����ס���ζ����ΰ�ι�ץ�����(�Х��ȿ�) */
	UINT fblksz;		/* �����˳�����ǽ�ʺ������֥�å�������(�Х��ȿ�) */
} T_RMPL;


/* ����Ĺ����ס��륳��ȥ���֥�å�(ROM��) */
typedef struct t_kernel_mplcb_rom
{
	ATR  mplatr;		/* ����Ĺ����ס���°�� */
	UINT mplsz;			/* ����Ĺ����ס����ΰ�Υ�����(�Х��ȿ�) */
	VP   mpl;			/* ����Ĺ����ס����ΰ����Ƭ���� */
} T_KERNEL_MPLCB_ROM;


/* ����Ĺ����ס��륳��ȥ���֥�å�(RAM��) */
typedef struct t_kernel_mplcb_ram
{
	T_MKNL_QUE     que;	/* ����Ĺ����ס����Ԥ����������塼 */
	T_KERNEL_HEPCB hep;	/* ����ҡ��� */
	const T_KERNEL_MPLCB_ROM *mplcb_rom;	/* ����Ĺ����ס��륳��ȥ���֥�å�ROM���ؤΥݥ��� */
} T_KERNEL_MPLCB_RAM;


/* �����Ԥ�����¤�� */
typedef struct t_kernel_mplinf
{
	UINT blksz;			/* �����������֥�å��Υ�����(�Х��ȿ�) */
	VP   *p_blk;		/* ������������֥�å�����Ƭ���� */
} T_KERNEL_MPLINF;



/* ---------------------------------- */
/*        �����Х��ѿ����          */
/* ---------------------------------- */

/* ����Ĺ����ס������ */
extern       T_KERNEL_MPLCB_RAM *kernel_mplcb_ram_tbl[];	/* ����Ĺ����ס��륳��ȥ���֥�å��ơ��֥�(RAM��) */
extern const INT kernel_mplcb_cnt;							/* ����Ĺ����ס��륳��ȥ���֥�å��Ŀ� */


/* ---------------------------------- */
/*            �ޥ������              */
/* ---------------------------------- */

/* ����Ĺ����ס��륳��ȥ���֥�å��Ѵ��ޥ��� */
#define KERNEL_MPLID_TO_MPLCB_RAM(mplid)	(kernel_mplcb_ram_tbl[(mplid) - KERNEL_TMIN_MPLID])
															/* ����Ĺ����ס���ID����MPLCB RAM���ɥ쥹����� */


/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* ����Ĺ����ס��� */
void    kernel_ini_mpl(void);								/* ����Ĺ����ס���ν���� */
ER      cre_mpl(ID mplid, const T_CMPL *pk_cmpl);			/* ����Ĺ����ס�������� */
ER_ID   acre_mpl(const T_CMPL *pk_cmpl);					/* ����Ĺ����ס��������(ID�ֹ漫ư���դ�) */
ER      kernel_cre_mpl(ID mplid, const T_CMPL *pk_cmpl);	/* ����Ĺ����ס��������(�����ͥ������ؿ�) */
ER      del_mpl(ID mplid);									/* ����Ĺ����ס���κ�� */
ER      get_mpl(ID mplid, UINT blksz, VP *p_blk);			/* ����Ĺ����֥�å��γ��� */
ER      pget_mpl(ID mplid, UINT blksz, VP *p_blk);			/* ����Ĺ����֥�å��γ���(�ݡ����) */
ER      tget_mpl(ID mplid, UINT blksz, VP *p_blk, TMO tmout);
															/* ����Ĺ����֥�å��γ���(�����ॢ���Ȥ���) */
ER      rel_mpl(ID mplid, VP blk);							/* ����Ĺ����֥�å����ֵ� */
ER      ref_mpl(ID mplid, T_RMPL *pk_rmpl);					/* ����Ĺ����֥�å��ξ��ֻ��� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_mpl_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
