/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*   ����ץ�ץ����                                                     */
/*   �桼���������ؿ� StrongARM��                                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* �����ߥ���ȥ��顼�쥸�������ɥ쥹 */
#define ICIP		(*(volatile UW *)0x9005000)
#define ICMR		(*(volatile UW *)0x9005004)
#define ICLR		(*(volatile UW *)0x9005008)
#define ICFP		(*(volatile UW *)0x9005010)
#define ICPR		(*(volatile UW *)0x9005020)
#define ICCR		(*(volatile UW *)0x900500c)



/* �������ѿ� */
static UW fiq_save_imask;		/* FIQ�������ߥޥ�������¸�� */



/* IRQ�ν���� */
void hos_arm_ini_int(void)
{
	/* �����ߥ���ȥ��顼����� */
	ICMR = 0x00000000;		/* �������ߤ�ޥ��� */
}


/* IRQ�����߽������ϡʥ桼���������ؿ��� */
INTNO hos_arm_sta_irq(void)
{
	UW    status;
	UW    mask;
	INTNO intno;
	
	/* �������ֹ渡�� */
	status = SA_ICIP;
	mask   = 0x00000001;
	for ( intno = TMIN_INTNO; intno <= TMAX_INTNO ; intno++ )
	{
		if ( status & mask )
		{
			break;
		}
		mask <<= 1;
	}
	
	/* �����ߥޥ������� */
	hospac_arm_imask |= (ARM_IMASK_IRQ | ARM_IMASK_USR_MODE);	/* IRQ��ޥ���(FIQ�Τߵ���) */
	
	mknl_ena_int();		/* ¿�ų����ߵ��� */
	
	return intno;
}


/* IRQ�����߽�����λ�ʥ桼���������ؿ��� */
void  hos_arm_end_irq(void)
{
	mknl_dis_int();		/* ¿�ų����߶ػ� */
	
	hospac_arm_imask = ARM_IMASK_USR_MODE;	/* IRQ�ޥ������� */
}


/* FIQ�����߽������ϡʥ桼���������ؿ��� */
INTNO hos_arm_sta_fiq(void)
{
	UW    status;
	UW    mask;
	INTNO intno;
	
	/* �������ֹ渡�� */
	status = SA_ICFP;
	mask   = 0x00000001;
	for ( intno = TMIN_INTNO; intno <= TMAX_INTNO ; intno++ )
	{
		if ( status & mask )
		{
			break;
		}
		mask <<= 1;
	}
	
	fiq_save_imask   = hospac_arm_imask;	/* �����ߥޥ���������¸ */
	hospac_arm_imask = (ARM_IMASK_IRQ | ARM_IMASK_FIQ | ARM_IMASK_USR_MODE)
											/* �����ߤ����ޥ��� */
	
	return intno;	/* �������ֹ���֤� */
}


/* FIQ�����߽�����λ�ʥ桼���������ؿ��� */
void  hos_arm_end_fiq(void)
{
	fiq_save_imask   = hospac_arm_imask;	/* �����ߥޥ����������� */
}


/* �����ߤε��� */
ER ena_int(INTNO intno)
{
	mknl_loc_sys();		/* �����ƥ��å� */
	
	ICMR |= 0x00000001 << (intno - TMIN_INTNO);
	
	mknl_unl_sys();		/* �����ƥ��å���� */
	
	return E_OK;
}


/* �����ߤζػ� */
ER dis_int(INTNO intno)
{
	mknl_loc_sys();		/* �����ƥ��å� */
	
	ICMR &= ~(0x00000001 << (intno - TMIN_INTNO));
	
	mknl_unl_sys();		/* �����ƥ��å���� */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
