/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    ITRON�����ͥ� ���٥�ȥե饰                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"
#include "knl_sys.h"



/* ���٥�ȥե饰�ξ��ֻ��� */
ER ref_flg(					
		ID     flgid,		/* ���ֻ����оݤΥ��٥�ȥե饰��ID�ֹ� */
		T_RFLG *pk_rflg)	/* ���٥�ȥե饰���֤��֤��ѥ��åȤؤΥݥ��� */
{
	T_KERNEL_FLGCB_RAM       *flgcb_ram;
	T_MKNL_TCB *mtcb;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( flgid < TMIN_FLGID || flgid > KERNEL_TMAX_FLGID )
	{
		return E_ID;	/* ����ID�ֹ� */
	}
#endif

	/* �ѥ�᡼���Υ����å� */
#ifdef HOS_ERCHK_E_PAR
	if ( pk_rflg == NULL )
	{
		return E_PAR;	/* �ѥ�᡼�����顼 */
	}
#endif

	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	flgcb_ram = KERNEL_FLGID_TO_FLGCB_RAM(flgid);

	/* ���֥������Ȥ�¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( flgcb_ram == NULL )
	{
		mknl_unl_sys();	/* �����ƥ�Υ�å���� */
		return E_NOEXS;	/* ���֥�������̤���� */
	}
#endif

	/* ���٥�ȥե饰���Ԥ��������Ƭ�Υ�������ID�ֹ���� */
	mtcb = mknl_ref_qhd(&flgcb_ram->que);	/* �Ԥ�������Ƭ���饿�������Ф� */
	if ( mtcb == NULL )
	{
		pk_rflg->wtskid = TSK_NONE;		/* �Ԥ��������ʤ� */
	}
	else
	{
		/* ������ID�򸡺� */
		pk_rflg->wtskid = kernel_get_tid(KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb));
	}

	/* �ե饰�ӥåȥѥ�����μ��� */
	pk_rflg->flgptn = flgcb_ram->flgptn;

	mknl_unl_sys();	/* �����ƥ�Υ�å���� */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
