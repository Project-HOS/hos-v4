/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRON�����ͥ� �᡼��ܥå���                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_mbx.h"



/* �᡼��ܥå����ؤ����� */
ER snd_mbx(
		ID    mbxid,		/* �����оݤΥ᡼��ܥå�����ID�ֹ� */
		T_MSG *pk_msg)		/* �᡼��ܥå��������������å������ѥ��åȤ���Ƭ���� */
{
	T_KERNEL_MBXCB_RAM *mbxcb_ram;
	T_MKNL_TCB *mtcb;
	T_MSG      *msg;
	T_MSG      *msg_next;

	/* ID �Υ����å� */
#ifdef HOS_ERCHK_E_ID
	if ( mbxid < TMIN_MBXID || mbxid > TMAX_MBXID )
	{
		return E_ID;
	}
#endif
	
	mknl_loc_sys();	/* �����ƥ�Υ�å� */

	mbxcb_ram = KERNEL_MBXID_TO_MBXCB_RAM(mbxid);

	/* ���֥�������¸�ߥ����å� */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mbxcb_ram == NULL )
	{
		mknl_unl_sys();		/* �����ƥ�Υ�å���� */
		return E_NOEXS;
	}
#endif

	mtcb = mknl_ref_qhd(&mbxcb_ram->que);		/* �Ԥ�������Ƭ����������� */
	if ( mtcb != NULL )
	{
		/* �Ԥ�������������г��� */
		mtcb->data = (VP_INT)pk_msg;			/* ��å��������Ϥ� */
		mtcb = mknl_ref_qhd(&mbxcb_ram->que);	/* �Ԥ�������Ƭ���饿�������Ф� */
		mknl_rmv_que(mtcb);						/* �᡼��ܥå������Ԥ����󤫤��� */
		mknl_rmv_tmout(mtcb);					/* �����ॢ�����Ԥ����󤫤��� */
		mknl_wup_tsk(mtcb, E_OK);				/* ���������Ԥ���� */
		
		mknl_exe_dsp();		/* �������ǥ����ѥå��μ¹� */
		mknl_exe_tex();		/* �㳰�����μ¹� */
	}
	else
	{
		/* �Ԥ����������ʤ���Х᡼��ܥå�������³ */
		if ( mbxcb_ram->msg == NULL )
		{
			/* ��å����������ʤ���Ƭ����³ */
			mbxcb_ram->msg = pk_msg;
			pk_msg->next   = NULL;
		}
		else
		{
			msg = mbxcb_ram->msg;
			if ( mbxcb_ram->mbxcb_rom->mbxatr & TA_MPRI )
			{
				/* ͥ���ٰ��֤򸡺� */
				for ( ; ; )
				{
					msg_next = msg->next;
					if ( msg_next == NULL
						|| ((T_MSG_PRI*)msg_next)->msgpri > ((T_MSG_PRI*)pk_msg)->msgpri )
					{
						/* ͥ���ٰ��֤����� */
						msg->next    = pk_msg;
						pk_msg->next = msg_next;
						break;
					}
					msg = msg_next;
				}
			}
			else
			{
				/* �����򸡺� */
				while ( msg->next != NULL )
				{
					msg = msg->next;
				}
				/* �������ɲ� */
				msg->next    = pk_msg;
				pk_msg->next = NULL;
			}
		}
	}

	mknl_unl_sys();	/* �����ƥ�Υ�å���� */

	return E_OK;	/* ���� */
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
