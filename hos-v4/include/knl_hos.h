/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �����ͥ� HOS�ȼ���ǽ                                                  */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_knl_h__
#define __HOS_V4__knl_knl_h__



/* ------------------------------------------ */
/*                  ������                  */
/* ------------------------------------------ */

/* �����ͥ���������� */
#define MEMBLK_ALIGN	4			/* ���ꥢ�饤���� */

#define MEMBLK_USING	0x1234		/* ������ */
#define MEMBLK_FREE		0xabcd		/* ̤���� */



/* ------------------------------------------ */
/*                 �����                     */
/* ------------------------------------------ */

/* �����ͥ��������֥�å� */
typedef struct t_kernel_mem_blk
{
	struct t_kernel_mem_blk* prev;		/* ���Υ֥�å� */
	SIZE   size;						/* �֥�å��Υ����� */
	INT    flag;						/* ������ե饰 */
} T_KERNEL_MEM_BLK;

/* �����ͥ��������֥�å������� */
#define MEMBLKSIZE	((sizeof(T_KERNEL_MEM_BLK) + MEMBLK_ALIGN - 1) & ~(MEMBLK_ALIGN - 1))



#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------- */
/*        �����Х��ѿ����          */
/* ---------------------------------- */

/* �����ͥ륷���ƥ���� */
extern STAT kernel_ctx_stat;				/* �����ƥ�Υ���ƥ����Ⱦ��� */


/* �����ͥ������� */
extern T_KERNEL_MEM_BLK *kernel_mem_base;	/* �����ͥ��ѥ�����Ƭ�֥�å��Υ��ɥ쥹 */



/* ------------------------------------------ */
/*                �ؿ����                    */
/* ------------------------------------------ */

/* �����ͥ륷���ƥ���� */
ER      sta_hos(void);								/* �����ͥ�ư��� */


/* �����ͥ������ؿ� */
#define kernel_get_run_tsk()	\
			(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mknl_get_run_tsk()))
													/* �¹��楿��������(�ޥ���ؿ�) */


/* ����ե�����졼���������ؿ� */
void    kernel_cfg_init(void);						/* �ѿ��ν���� */
void    kernel_cfg_start(void);						/* ������ؿ��ƤӽФ� */


/* �����ƥ������� */
void    kernel_ini_mem(void *p_base, SIZE size);	/* ������������� */
VP      kernel_alc_mem(SIZE size);					/* ����γ������ */
void    kernel_fre_mem(VP ptr);						/* ����β��� */



#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_knl_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
