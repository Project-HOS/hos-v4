/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ��¸��������إå� �᡼��ܥå���                             */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_mbx_h__
#define __HOS_V4__knl_mbx_h__


#include "knl_hos.h"



/* ------------------------------------------ */
/*                  ������                  */
/* ------------------------------------------ */

/* ID���ϰ� */
#define TMIN_MBXID		1					/* �᡼��ܥå���ID�κǾ��� */
#define KERNEL_TMAX_MBXID		(TMIN_MBXID + kernel_mbxcb_cnt - 1)
											/* �᡼��ܥå���ID�κ����� */


/* ͥ���٤��ϰ� */
#define TMIN_MPRI		1					/* ��å�����ͥ���٤κǾ��� */
#define TMAX_MPRI		32767				/* ��å�����ͥ���٤κ����� */

/* ɬ�פʥ����ΰ�Υ����� */
#define TSZ_MPRIHD(maxmpri)		(sizeof(T_MSG *) * ((maxmpri) - TMIN_MPRI + 1))
											/* ͥ�����̥��塼�إå��Υ����ΰ�Υ����� */



/* ------------------------------------------ */
/*                 �����                     */
/* ------------------------------------------ */

/* �᡼��ܥå����Υ�å������إå� */
typedef struct t_msg
{
	struct t_msg *next;		/* ���Υ�å������ؤΥݥ��� */
} T_MSG;

/* �᡼��ܥå�����ͥ�����դ���å������إå� */
typedef struct t_msg_pri
{
	T_MSG msg;				/* ��å������إå� */
	PRI   msgpri;			/* ��å�����ͥ���� */
} T_MSG_PRI;


/* �᡼��ܥå����������� */
typedef struct t_cmbx
{
	ATR   mbxatr;		/* �᡼��ܥå���°�� */
	PRI   maxmpri;		/* ����������å�������ͥ���٤κ����� */
	VP    mprihd;		/* ͥ�����̤Υ�å��������塼�إå��ΰ����Ƭ���� */
} T_CMBX;

/* �᡼��ܥå������� */
typedef struct t_rmbx
{
	ID    wtskid;		/* �᡼��ܥå������Ԥ��������Ƭ�Υ�������ID�ֹ� */
	T_MSG *pk_msg;		/* ��å��������塼����Ƭ�Υ�å������ѥ��åȤ���Ƭ���� */
} T_RMBX;


/* �᡼��ܥå�������ȥ���֥�å�(ROM��) */
typedef struct t_kernel_mbxcb_rom
{
	ATR   mbxatr;		/* �᡼��ܥå���°�� */
	PRI   maxmpri;		/* ����������å�������ͥ���٤κ����� */
	T_MSG **mprihd;		/* ͥ�����̤Υ�å��������塼�إå��ΰ����Ƭ���� */
} T_KERNEL_MBXCB_ROM;

/* �᡼��ܥå�������ȥ���֥�å�(RAM��) */
typedef struct t_kernel_mbxcb_ram
{
	T_MKNL_QUE que;							/* �᡼��ܥå����Ԥ����������塼 */
	const T_KERNEL_MBXCB_ROM *mbxcb_rom;	/* �᡼��ܥå�������ȥ���֥�å�ROM���ؤΥݥ��� */
} T_KERNEL_MBXCB_RAM;



/* ---------------------------------- */
/*        �����Х��ѿ����          */
/* ---------------------------------- */

/* �᡼��ܥå������� */
extern       T_KERNEL_MBXCB_RAM *kernel_mbxcb_ram_tbl[];	/* �᡼��ܥå�������ȥ���֥�å��ơ��֥�(RAM��) */
extern const INT kernel_mbxcb_cnt;							/* �᡼��ܥå�������ȥ���֥�å��Ŀ� */

#define KERNEL_MBXID_TO_MBXCB_RAM(mbxid)	(kernel_mbxcb_ram_tbl[(mbxid) - TMIN_MBXID])
															/* �᡼��ܥå���ID����MBXCB RAM���ɥ쥹����� */



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* �᡼��ܥå��� */
#define kernel_ini_mbx()									/* �᡼��ܥå����ν���� */
ER      cre_mbx(ID semid, const T_CMBX *pk_cmbx);			/* ���ޥե������� */
ER_ID   acre_mbx(const T_CMBX *pk_cmbx);					/* ���ޥե�������(ID�ֹ漫ư���դ�) */
ER      kernel_cre_mbx(ID mbxid, const T_CMBX *pk_cmbx);	/* ���ޥե�������(�����ͥ������ؿ�) */
ER      del_mbx(ID semid);									/* ���ޥե��κ�� */
ER      snd_mbx(ID mbxid, T_MSG *pk_msg);					/* �᡼��ܥå����ؤ����� */
ER      rcv_mbx(ID mbxid, T_MSG **ppk_msg);					/* �᡼��ܥå�������μ��� */
ER      prcv_mbx(ID mbxid, T_MSG **ppk_msg);				/* �᡼��ܥå�������μ���(�ݡ����) */
ER      trcv_mbx(ID mbxid, T_MSG **ppk_msg, TMO tmout);		/* �᡼��ܥå�������μ���(�����ॢ���Ȥ���) */
ER      ref_mbx(ID mbxid, T_RMBX *pk_rmbx);					/* �᡼��ܥå����ξ��ֻ��� */

#ifdef __cplusplus
}
#endif



#endif	/*__HOS_V4__knl_mbx_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
