/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �����ͥ��¸��������إå� ���٥�ȥե饰                             */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_flg_h__
#define __HOS_V4__knl_flg_h__



/* ------------------------------------------ */
/*                  ������                  */
/* ------------------------------------------ */

/* ID���ϰ� */
#define TMIN_FLGID		1					/* ���٥�ȥե饰ID�κǾ��� */
#define TMAX_FLGID		(TMIN_FLGID + kernel_flgcb_cnt - 1)
											/* ���٥�ȥե饰ID�κ����� */

/* �ӥåȥѥ�����Υӥåȿ� */
#define TBIT_FLGPTN		16					/* ���٥�ȥե饰�Υӥåȿ� */



/* ------------------------------------------ */
/*                 �����                     */
/* ------------------------------------------ */

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
	T_MKNL_TCB *mtcb;		/* ���٥�ȥե饰�Ԥ������� */
	FLGPTN     flgptn;		/* ���٥�ȥե饰�Υӥåȥѥ����� */
	const T_KERNEL_FLGCB_ROM* flgcbrom;	/* ���٥�ȥե饰����ȥ���֥�å�ROM���ؤΥݥ��� */
} T_KERNEL_FLGCB_RAM;

/* �Ԥ��ե饰����¤�� */
typedef struct t_kernel_flginf
{
	MODE   wfmode;		/* �Ԥ��⡼�� */
	FLGPTN waiptn;		/* �Ԥ��ӥåȥѥ�����ʲ�����ѥ�����ȷ���) */
} T_KERNEL_FLGINF;


#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------- */
/*        �����Х��ѿ����          */
/* ---------------------------------- */

/* ���٥�ȥե饰���� */
extern       T_KERNEL_FLGCB_RAM *kernel_flgcb_ram_tbl[];	/* ���٥�ȥե饰����ȥ���֥�å��ơ��֥�(RAM��) */
extern const INT kernel_flgcb_cnt;							/* ���٥�ȥե饰����ȥ���֥�å��Ŀ� */

#define KERNEL_FLGID_TO_FLGCB_RAM(flgid)	(kernel_flgcb_ram_tbl[(flgid) - TMIN_FLGID])
															/* ���٥�ȥե饰ID����FLGCB RAM���ɥ쥹����� */



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

/* ���٥�ȥե饰 */
void    kernel_ini_flg(void);						/* ���٥�ȥե饰�ν���� */
ER      set_flg(ID flgid, FLGPTN setptn);			/* ���٥�ȥե饰�Υ��å� */
#define iset_flg	set_flg							/* ���٥�ȥե饰�Υ��å�(�󥿥�������ƥ������ѥޥ���) */
ER      clr_flg(ID flgid, FLGPTN clrptn);			/* ���٥�ȥե饰�Υ��ꥢ */
ER      wai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn);
													/* ���٥�ȥե饰�Ԥ� */
ER      pol_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn);
													/* ���٥�ȥե饰�Ԥ�(�ݡ����) */
ER      twai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn, TMO tmout);
													/* ���٥�ȥե饰�Ԥ�(�����ॢ���Ȥ���) */
BOOL    kernel_chk_flg(T_KERNEL_FLGCB_RAM *flgcb_ram, T_KERNEL_FLGINF *pk_flginf);
													/* �ե饰�����������������Ƥ��뤫�����å� */



#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_flg_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
