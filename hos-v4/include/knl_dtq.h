/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �����ͥ��¸��������إå� �ǡ������塼                               */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_dtq_h__
#define __HOS_V4__knl_dtq_h__


#include "knl_hos.h"



/* ------------------------------------------ */
/*                  ������                  */
/* ------------------------------------------ */

/* ID���ϰ� */
#define TMIN_DTQID		1					/* �ǡ������塼ID�κǾ��� */
#define TMAX_DTQID		(TMIN_DTQID + kernel_dtqcb_cnt - 1)
											/* �ǡ������塼ID�κ����� */



/* ------------------------------------------ */
/*                 �ޥ������                 */
/* ------------------------------------------ */

/* �����ΰ�Υ����� */
#define TSZ_DTQ(dtqcnt)		((SIZE)((UINT)(dtqcnt) * sizeof(VP_INT)))



/* ------------------------------------------ */
/*                 �����                     */
/* ------------------------------------------ */

/* �ǡ������塼�������� */
typedef struct t_cdtq
{
	ATR    dtqatr;		/* �ǡ������塼°�� */
	UINT   dtqcnt;		/* �ǡ������塼�ΰ������(�ǡ����θĿ�) */
	VP     dtq;			/* �ǡ������塼�ΰ����Ƭ���� */
} T_CDTQ;


/* �ǡ������塼����ȥ���֥�å�(ROM��) */
typedef struct t_kernel_dtqcb_rom
{
	ATR    dtqatr;		/* �ǡ������塼°�� */
	UINT   dtqcnt;		/* �ǡ������塼�ΰ������(�ǡ����θĿ�) */
	VP_INT *dtq;		/* �ǡ������塼�ΰ����Ƭ���� */
} T_KERNEL_DTQCB_ROM;

/* �ǡ������塼����ȥ���֥�å�(RAM��) */
typedef struct t_kernel_dtqcb_ram
{
	T_MKNL_QUE sndque;	/* �ǡ������塼�����Ԥ����������塼 */
	T_MKNL_QUE rcvque;	/* �ǡ������塼�����Ԥ����������塼 */
	UINT       head;	/* �ǡ�������Ƭ */
	UINT       datacnt;	/* �ǡ����θĿ� */
	const T_KERNEL_DTQCB_ROM *dtqcb_rom;	/* �ǡ������塼����ȥ���֥�å�ROM���ؤΥݥ��� */
} T_KERNEL_DTQCB_RAM;



#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------- */
/*        �����Х��ѿ����          */
/* ---------------------------------- */

/* �ǡ������塼���� */
extern       T_KERNEL_DTQCB_RAM *kernel_dtqcb_ram_tbl[];	/* �ǡ������塼����ȥ���֥�å��ơ��֥�(RAM��) */
extern const INT kernel_dtqcb_cnt;							/* �ǡ������塼����ȥ���֥�å��Ŀ� */

/* �ǡ������塼����ȥ���֥�å��Ѵ��ޥ��� */
#define KERNEL_DTQID_TO_DTQCB_RAM(dtqid)	(kernel_dtqcb_ram_tbl[(dtqid) - TMIN_DTQID])
															/* �ǡ������塼ID����DTQCB RAM���ɥ쥹����� */



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

/* �ǡ������塼 */
#define kernel_ini_dtq()									/* �ǡ������塼�ν���� */
ER      cre_dtq(ID dtqid, const T_CDTQ *pk_cdtq);			/* �ǡ������塼������ */
ER_ID   acre_dtq(const T_CDTQ *pk_cdtq);					/* �ǡ������塼������(ID�ֹ漫ư���դ�) */
ER      kernel_cre_dtq(ID dtqid, const T_CDTQ *pk_cdtq);	/* �ǡ������塼������(�����ͥ������ؿ�) */
ER      del_dtq(ID dtqid);									/* �ǡ������塼�κ�� */
ER      snd_dtq(ID dtqid, VP_INT data);						/* �ǡ������塼�ؤ����� */
ER      psnd_dtq(ID dtqid, VP_INT data);					/* �ǡ������塼�ؤ�����(�ݡ����) */
#define ipsnd_dtq	psnd_dtq								/* �ǡ������塼�ؤ�����(�ݡ���� �󥿥�������ƥ������ѥޥ���) */
ER      tsnd_dtq(ID dtqid, VP_INT data, TMO tmout);			/* �ǡ������塼�ؤ�����(�����ॢ���Ȥ���) */
ER      fsnd_dtq(ID dtqid, VP_INT data);					/* �ǡ������塼�ؤζ������� */
#define ifsnd_dtq	fsnd_dtq								/* �ǡ������塼�ؤζ�������(�󥿥�������ƥ������ѥޥ���) */
ER      rcv_dtq(ID dtqid, VP_INT *p_data);					/* �ǡ������塼����μ��� */
ER      prcv_dtq(ID dtqid, VP_INT *p_data);					/* �ǡ������塼����μ���(�ݡ����) */
ER      trcv_dtq(ID dtqid, VP_INT *p_data, TMO tmout);		/* �ǡ������塼����μ���(�����ॢ���Ȥ���) */



#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_dtq_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
