/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �����ͥ��¸��������إå� �᡼��ܥå���                             */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_mbx_h__
#define __HOS_V4__knl_mbx_h__



/* ------------------------------------------ */
/*                  ������                  */
/* ------------------------------------------ */

/* ID���ϰ� */
#define TMIN_MBXID		1					/* �᡼��ܥå���ID�κǾ��� */
#define TMAX_MBXID		(TMIN_MBXID + kernel_mbxcb_cnt - 1)
											/* �᡼��ܥå���ID�κ����� */


/* ͥ���٤��ϰ� */
#define TMIN_MPRI		1					/* ��å�����ͥ���٤κǾ��� */
#define TMAX_MPRI		65535				/* ��å�����ͥ���٤κ����� */



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


/* �᡼��ܥå�������ȥ���֥�å�(ROM��) */
typedef struct t_kernel_mbxcb_rom
{
	ATR       mbxatr;		/* �᡼��ܥå���°�� */
} T_KERNEL_MBXCB_ROM;

/* �᡼��ܥå�������ȥ���֥�å�(RAM��) */
typedef struct t_kernel_mbxcb_ram
{
	T_MKNL_QUE que;			/* �᡼��ܥå����Ԥ����������塼 */
	T_MSG      *msg;		/* ��å���������Ƭ���� */
	const T_KERNEL_MBXCB_ROM *mbxrom;
} T_KERNEL_MBXCB_RAM;



#ifdef __cplusplus
extern "C" {
#endif

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

/* �᡼��ܥå��� */
ER      snd_mbx(ID mbxid, T_MSG *pk_msg);			/* �᡼��ܥå����ؤ����� */
ER      rcv_mbx(ID mbxid, T_MSG **ppk_msg);			/* �᡼��ܥå�������μ��� */
ER      prcv_mbx(ID mbxid, T_MSG **ppk_msg);		/* �᡼��ܥå�������μ���(�ݡ����) */
ER      trcv_mbx(ID mbxid, T_MSG **ppk_msg, TMO tmout);
													/* �᡼��ܥå�������μ���(�����ॢ���Ȥ���) */



#ifdef __cplusplus
}
#endif



#endif	/*__HOS_V4__knl_mbx_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
