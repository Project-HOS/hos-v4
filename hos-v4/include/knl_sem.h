/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �����ͥ��¸��������إå� ���ޥե�                                   */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_sem_h__
#define __HOS_V4__knl_sem_h__


#include "knl_hos.h"



/* ------------------------------------------ */
/*                  ������                  */
/* ------------------------------------------ */

/* ID���ϰ� */
#define TMIN_SEMID		1					/* ���ޥե�ID�κǾ��� */
#define TMAX_SEMID		(TMIN_SEMID + kernel_semcb_cnt - 1)
											/* ���ޥե�ID�κ����� */



/* ------------------------------------------ */
/*                 �����                     */
/* ------------------------------------------ */

/* ���ޥե��������� */
typedef struct t_csem
{
	ATR  sematr;		/* ���ޥե�°�� */
	UINT isemcnt;		/* ���ޥե��񸻿��ν���� */
	UINT maxsem;		/* ���ޥե��κ���񸻿� */
} T_CSEM;

/* ���ޥե����־��� */
typedef struct t_rsem
{
	ID   wtskid;		/* ���ޥե����Ԥ��������Ƭ�Υ�������ID�ֹ� */
	UINT semcnt;		/* ���ޥե��θ��ߤλ񸻿� */
} T_RSEM;


/* ���ޥե�����ȥ���֥�å�(ROM��) */
typedef struct t_kernel_semcb_rom
{
	ATR  sematr;		/* ���ޥե�°�� */
	UINT isemcnt;		/* ���ޥե��񸻿��ν���� */
	UINT maxsem;		/* ���ޥե��κ���񸻿� */
} T_KERNEL_SEMCB_ROM;

/* ���ޥե�����ȥ���֥�å�(RAM��) */
typedef struct t_kernel_semcb_ram
{
	T_MKNL_QUE que;		/* ���ޥե��Ԥ����������塼 */
	UINT       semcnt;	/* ���ޥե��λ񸻿� */
	const T_KERNEL_SEMCB_ROM *semcb_rom;	/* ���ޥե�����ȥ���֥�å�ROM���ؤΥݥ��� */
} T_KERNEL_SEMCB_RAM;



#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------- */
/*        �����Х��ѿ����          */
/* ---------------------------------- */

/* ���ޥե����� */
extern       T_KERNEL_SEMCB_RAM *kernel_semcb_ram_tbl[];	/* ���ޥե�����ȥ���֥�å��ơ��֥�(RAM��) */
extern const INT kernel_semcb_cnt;							/* ���ޥե�����ȥ���֥�å��Ŀ� */

/* ���ޥե�����ȥ���֥�å��Ѵ��ޥ��� */
#define KERNEL_SEMID_TO_SEMCB_RAM(semid)	(kernel_semcb_ram_tbl[(semid) - TMIN_SEMID])
															/* ���ޥե�ID����SEMCB RAM���ɥ쥹����� */



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

/* ���ޥե� */
void    kernel_ini_sem(void);								/* ���ޥե��ν���� */
ER      cre_sem(ID semid, const T_CSEM *pk_csem);			/* ���ޥե������� */
ER_ID   acre_sem(const T_CSEM *pk_csem);					/* ���ޥե�������(ID�ֹ漫ư���դ�) */
ER      kernel_cre_sem(ID semid, const T_CSEM *pk_csem);	/* ���ޥե�������(�����ͥ������ؿ�) */
ER      del_sem(ID semid);									/* ���ޥե��κ�� */
ER      sig_sem(ID semid);									/* ���ޥե��񸻤��ֵ� */
#define isig_sem sig_sem									/* ���ޥե��񸻤��ֵ�(�󥿥�������ƥ������ѥޥ���) */
ER      wai_sem(ID semid);									/* ���ޥե��񸻤γ��� */
ER      pol_sem(ID semid);									/* ���ޥե��񸻤γ���(�ݡ����) */
ER      twai_sem(ID semid, TMO tmout);						/* ���ޥե��񸻤γ���(�����ॢ���Ȥ���) */
ER      ref_sem(ID semid, T_RSEM *pk_rsem);					/* ���ޥե��ξ��ֻ��� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_sem_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
