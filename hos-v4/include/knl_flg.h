/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �����ͥ��¸��������إå� ���٥�ȥե饰                             */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_flg_h__
#define __HOS_V4__knl_flg_h__


#include "knl_hos.h"



/* ------------------------------------------ */
/*                  ������                  */
/* ------------------------------------------ */

/* ID���ϰ� */
#define KERNEL_TMIN_FLGID	TMIN_FLGID			/* ���٥�ȥե饰ID�κǾ��� */
#define KERNEL_TMAX_FLGID	(KERNEL_TMIN_FLGID + kernel_flgcb_cnt - 1)
												/* ���٥�ȥե饰ID�κ����� */

/* �ӥåȥѥ�����Υӥåȿ� */
#define TBIT_FLGPTN			16					/* ���٥�ȥե饰�Υӥåȿ� */



/* ------------------------------------------ */
/*                 �����                     */
/* ------------------------------------------ */

/* ���٥�ȥե饰�������� */
typedef struct t_cflg
{
	ATR    flgatr;		/* ���٥�ȥե饰°�� */
	FLGPTN iflgptn;		/* ���٥�ȥե饰�Υӥåȥѥ�����ν���� */
} T_CFLG;

/* ���٥�ȥե饰���� */
typedef struct t_rflg
{
	ID     wtskid;		/* ���٥�ȥե饰���Ԥ��������Ƭ�Υ�������ID�ֹ� */
	FLGPTN flgptn;		/* ���٥�ȥե饰�θ��ߤΥӥåȥѥ����� */
} T_RFLG;


/* ���٥�ȥե饰����ȥ���֥�å�(ROM��) */
typedef struct t_kernel_flgcb_rom
{
	ATR    flgatr;		/* ���٥�ȥե饰°�� */
	FLGPTN iflgptn;		/* ���٥�ȥե饰�Υӥåȥѥ�����ν���� */
} T_KERNEL_FLGCB_ROM;

/* ���٥�ȥե饰����ȥ���֥�å�(RAM��) */
typedef struct t_kernel_flgcb_ram
{
	T_MKNL_QUE que;			/* ���٥�ȥե饰�Ԥ����� */
	FLGPTN     flgptn;		/* ���٥�ȥե饰�Υӥåȥѥ����� */
	const T_KERNEL_FLGCB_ROM* flgcb_rom;	/* ���٥�ȥե饰����ȥ���֥�å�ROM���ؤΥݥ��� */
} T_KERNEL_FLGCB_RAM;


/* �Ԥ��ե饰����¤�� */
typedef struct t_kernel_flginf
{
	MODE   wfmode;		/* �Ԥ��⡼�� */
	FLGPTN waiptn;		/* �Ԥ��ӥåȥѥ�����ʲ�����ѥ�����ȷ���) */
} T_KERNEL_FLGINF;



/* ---------------------------------- */
/*        �����Х��ѿ����          */
/* ---------------------------------- */

/* ���٥�ȥե饰���� */
extern       T_KERNEL_FLGCB_RAM *kernel_flgcb_ram_tbl[];	/* ���٥�ȥե饰����ȥ���֥�å��ơ��֥�(RAM��) */
extern const INT kernel_flgcb_cnt;							/* ���٥�ȥե饰����ȥ���֥�å��Ŀ� */

#define KERNEL_FLGID_TO_FLGCB_RAM(flgid)	(kernel_flgcb_ram_tbl[(flgid) - KERNEL_TMIN_FLGID])
															/* ���٥�ȥե饰ID����FLGCB RAM���ɥ쥹����� */



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* ���٥�ȥե饰 */
void    kernel_ini_flg(void);								/* ���٥�ȥե饰�ν���� */
ER      cre_flg(ID flgid, const T_CFLG *pk_cflg);			/* ���٥�ȥե饰������ */
ER_ID   acre_flg(const T_CFLG *pk_cflg);					/* ���٥�ȥե饰������(ID�ֹ漫ư���դ�) */
ER      kernel_cre_flg(ID flgid, const T_CFLG *pk_cflg);	/* ���٥�ȥե饰������(�����ͥ������ؿ�) */
ER      del_flg(ID flgid);									/* ���٥�ȥե饰�κ�� */
ER      set_flg(ID flgid, FLGPTN setptn);					/* ���٥�ȥե饰�Υ��å� */
#define iset_flg	set_flg									/* ���٥�ȥե饰�Υ��å�(�󥿥�������ƥ������ѥޥ���) */
ER      clr_flg(ID flgid, FLGPTN clrptn);					/* ���٥�ȥե饰�Υ��ꥢ */
ER      wai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn);
															/* ���٥�ȥե饰�Ԥ� */
ER      pol_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn);
															/* ���٥�ȥե饰�Ԥ�(�ݡ����) */
ER      twai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn, TMO tmout);
															/* ���٥�ȥե饰�Ԥ�(�����ॢ���Ȥ���) */
ER      ref_flg(ID flgid, T_RFLG *pk_rflg);					/* ���٥�ȥե饰�ξ��ֻ��� */
BOOL    kernel_chk_flg(T_KERNEL_FLGCB_RAM *flgcb_ram, T_KERNEL_FLGINF *pk_flginf);
															/* �ե饰�����������������Ƥ��뤫�����å� */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_flg_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
