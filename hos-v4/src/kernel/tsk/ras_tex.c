/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� �������㳰������ǽ                                      */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"
#include "knl_sys.h"


/* �������㳰�������׵� */
ER ras_tex(
		ID     tskid,		/* �׵��оݤΥ�������ID�ֹ� */
		TEXPTN rasptn)		/* �׵᤹�륿�����㳰�����Υ������㳰�װ� */
{
	T_KERNEL_TCB_RAM   *tcb_ram;
	T_KERNEL_TEXCB_RAM *texcb;

	/* ID �ϰϥ����å� */
	if ( tskid == TSK_SELF )
	{
		/* ����ƥ����ȥ����å� */
#ifdef HOS_ERCHK_E_ID
		if ( sns_ctx() )
		{
			return E_ID;	/* ����ID�ֹ� */
		}
#endif
		tcb_ram = kernel_get_run_tsk();
		texcb = tcb_ram->texcb;
		
		mknl_loc_sys();	/* �����ƥ�Υ�å� */
	}
	else
	{
		/* ID �ϰϥ����å� */
#ifdef HOS_ERCHK_E_ID
		if ( tskid < TMIN_TSKID || tskid > TMAX_TSKID )
		{
			return  E_ID;	/* ����ID�ֹ� */
		}
#endif
		tcb_ram = KERNEL_TSKID_TO_TCB_RAM(tskid);

		mknl_loc_sys();	/* �����ƥ�Υ�å� */
	
		/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
		if ( tcb_ram == NULL )
		{
			mknl_unl_sys();		/* �����ƥ�Υ�å���� */
			return E_NOEXS;		/* ���֥�������̤���� */
		}
#endif
		
		texcb = tcb_ram->texcb;
		
		/* ���֥������Ⱦ��֥����å� */
#ifdef HOS_ERCHK_E_OBJ
		if ( texcb == NULL || mknl_get_tskstat(&tcb_ram->mtcb) == TTS_DMT )
		{
			mknl_unl_sys();		/* �����ƥ�Υ�å���� */
			return E_OBJ;		/* ���֥������Ⱦ������� */
		}
#endif
	}

	/* �㳰�������׵� */
	texcb->rasptn = (TEXPTN)(texcb->rasptn | rasptn);
	mknl_ras_tex(&tcb_ram->mtcb);

	mknl_unl_sys();		/* �����ƥ�Υ�å���� */

	return E_OK;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
