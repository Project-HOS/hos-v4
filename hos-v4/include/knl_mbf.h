/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ��¸��������إå� ��å������Хåե�                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_mbf_h__
#define __HOS_V4__knl_mbf_h__


#include "knl_hos.h"



/* ------------------------------------------ */
/*                  ������                  */
/* ------------------------------------------ */

/* ID���ϰ� */
#define TMIN_MBFID		1					/* ��å������Хåե�ID�κǾ��� */
#define TMAX_MBFID		(TMIN_MBFID + kernel_mbfcb_cnt - 1)
											/* ��å������Хåե�ID�κ����� */



/* ------------------------------------------ */
/*                 �����                     */
/* ------------------------------------------ */

/* ��å������Хåե��������� */
typedef struct t_cmbf
{
	ATR  mbfatr;		/* ��å������Хåե�°�� */
	UINT maxmsz;		/* ��å������κ��祵����(�Х��ȿ�) */
	SIZE mbfsz;			/* ��å������Хåե��ΰ�Υ�����(�Х��ȿ�) */
    VP   mbf;			/* ��å������Хåե��ΰ����Ƭ���� */
} T_CMBF;

/* ��å������Хåե����־��� */
typedef struct t_rmbf
{
	ID   stskid;		/* ��å������Хåե��������Ԥ��������Ƭ�Υ�������ID�ֹ� */
	ID   rtskid;		/* ��å������Хåե��μ����Ԥ��������Ƭ�Υ�������ID�ֹ� */
	UINT smsgcnt;		/* ��å������Хåե������äƤ����å������ο� */
	SIZE fmbfsz;		/* ��å������Хåե��ΰ�ζ����ΰ�Υ�����(�Х��ȿ�������¤δ����ΰ�����) */
} T_RMBF;


/* ��å������Хåե�����ȥ���֥�å�(ROM��) */
typedef struct t_kernel_mbfcb_rom
{
	ATR  mbfatr;		/* ��å������Хåե�°�� */
	UINT maxmsz;		/* ��å������κ��祵����(�Х��ȿ�) */
	SIZE mbfsz;			/* ��å������Хåե��ΰ�Υ�����(�Х��ȿ�) */
    VP   mbf;			/* ��å������Хåե��ΰ����Ƭ���� */
} T_KERNEL_MBFCB_ROM;

/* ��å������Хåե�����ȥ���֥�å�(RAM��) */
typedef struct t_kernel_mbfcb_ram
{
	T_MKNL_QUE sndque;	/* ��å������Хåե������Ԥ����������塼 */
	T_MKNL_QUE rcvque;	/* ��å������Хåե������Ԥ����������塼 */
	UINT       head;	/* ��Ƭ��å������ΰ��� */
	UINT       tail;	/* ������å������ΰ��� */
	const T_KERNEL_MBFCB_ROM *mbfcb_rom;	/* ��å������Хåե�����ȥ���֥�å�ROM���ؤΥݥ��� */
} T_KERNEL_MBFCB_RAM;

/* ������å������ǡ������� */
typedef struct t_kernel_mbfdat
{
	UINT msgsz;			/* ��å����������� */
	VP   msg;			/* ��å���������Ƭ���� */
} T_KERNEL_MBFDAT;



#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------- */
/*        �����Х��ѿ����          */
/* ---------------------------------- */

/* ��å������Хåե����� */
extern       T_KERNEL_MBFCB_RAM *kernel_mbfcb_ram_tbl[];	/* ��å������Хåե�����ȥ���֥�å��ơ��֥�(RAM��) */
extern const INT kernel_mbfcb_cnt;							/* ��å������Хåե�����ȥ���֥�å��Ŀ� */

/* ��å������Хåե�����ȥ���֥�å��Ѵ��ޥ��� */
#define KERNEL_MBFID_TO_MBFCB_RAM(mbfid)	(kernel_mbfcb_ram_tbl[(mbfid) - TMIN_MBFID])
															/* ��å������Хåե�ID����MBFCB RAM���ɥ쥹����� */



/* ------------------------------------------ */
/*                 �ޥ������                 */
/* ------------------------------------------ */

/* �����ΰ�Υ����� */
#define TSZ_MBF(msgcnt, msgsz)		((SIZE)((UINT)(msgcnt) * ((UINT)(msgsz) + 2) + 1))



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

/* ��å������Хåե� */
#define kernel_ini_mbf()									/* ��å������Хåե��ν���� */
ER      cre_mbf(ID mbfid, const T_CMBF *pk_cmbf);			/* ��å������Хåե������� */
ER_ID   acre_mbf(const T_CMBF *pk_cmbf);					/* ��å������Хåե�������(ID�ֹ漫ư���դ�) */
ER      kernel_cre_mbf(ID mbfid, const T_CMBF *pk_cmbf);	/* ��å������Хåե�������(�����ͥ������ؿ�) */
ER      del_mbf(ID mbfid);									/* ��å������Хåե��κ�� */
ER      snd_mbf(ID mbfid, VP msg, UINT msgsz);				/* ��å������Хåե��ؤ����� */
ER      psnd_mbf(ID mbfid, VP msg, UINT msgsz);				/* ��å������Хåե��ؤ�����(�ݡ����) */
ER      tsnd_mbf(ID mbfid, VP msg, UINT msgsz, TMO tmout);	/* ��å������Хåե��ؤ�����(�����ॢ���Ȥ���) */
ER      kernel_snd_mbf(const T_KERNEL_MBFCB_ROM *mbfcb_rom,
			T_KERNEL_MBFCB_RAM *mbfcb_ram, VP msg, UINT msgsz);	/* ��å������Хåե��ؤ�����(�����ͥ������ؿ�) */
ER_UINT rcv_mbf(ID mbfid, VP msg);							/* ��å������Хåե�����μ��� */
ER_UINT prcv_mbf(ID mbfid, VP msg);							/* ��å������Хåե�����μ���(�ݡ����) */
ER_UINT trcv_mbf(ID mbfid, VP msg,  TMO tmout);				/* ��å������Хåե�����μ���(�����ॢ���Ȥ���) */
ER_UINT kernel_rcv_mbf(const T_KERNEL_MBFCB_ROM *mbfcb_rom,
			T_KERNEL_MBFCB_RAM *mbfcb_ram, VP msg);			/* ��å������Хåե�����μ���(�����ͥ������ؿ�) */
ER      ref_mbf(ID mbfid, T_RMBF *pk_rmbf);					/* ��å������Хåե��ξ��ֻ��� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_mbf_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
