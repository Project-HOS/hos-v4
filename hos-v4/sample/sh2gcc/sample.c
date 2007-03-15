/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ����ץ�ץ����                           */
/*   ������ů�ؼԤο���������                                             */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include <stdio.h>
#include <stdlib.h>
#include "kernel.h"
#include "kernel_id.h"
#include "user_id.h"
#include "sh7045.h"
#include "sci.h"
#include "sample.h"


#define SCIID			ID_SCI1


#define LEFT_FORK(id)	((id) % 5 + 1)
#define RIGHT_FORK(id)	(id)



void SetLed(INT id);		/* �б���LED���� */
void ResetLed(INT id);		/* �б�LDE�ξ��� */

int led = 0;

/* �ᥤ��ؿ� */
int main()
{
	/* I/O �ν���� */
	*SH_PEIOR   = 0x00ff;
	*SH_PEDR    = 0;
	*SH_PACRL2 |= 0x0100;
	*SH_PEDR    = 0xff;
	
	/* HOS-V4 �γ��� */
	sta_hos();
	
	return 0;
}


/* ATT_INI ��Ͽ�δؿ� */
void SampleInitialize(VP_INT exinf)
{
	/* ��������ư */
	act_tsk(TSKID_PHILOSOPHER1);
	act_tsk(TSKID_PHILOSOPHER1);
	act_tsk(TSKID_PHILOSOPHER1);
	act_tsk(TSKID_PHILOSOPHER1);
//	act_tsk(TSKID_PHILOSOPHER1);
}


/* ů�ؼԥ����� */
void PhilosopherTask(VP_INT exinf)
{
	INT id;
	INT i;
	
	*SH_PEDR = ~led;
	led++;
	ext_tsk();
	
	*SH_PEDR = 0xaaaa;
	for ( ; ; )
		;
	
	id = (INT)exinf;
	
	/* Ķ���ϼ����르�ꥺ�� */
	for ( ; ; )
	{
		/* Ŭ���ʻ���Ǻ��Ǥߤ� */
		for ( i = rand() % 10 + 5; i > 0; i-- )
		{
			/* ���Ǥ����� */
			SetLed(id);
			dly_tsk(100);
			ResetLed(id);
			dly_tsk(100);
		}
		
		/* �����Υե��������� */
		for ( ; ; )
		{
			wai_sem(LEFT_FORK(id));
			if ( pol_sem(RIGHT_FORK(id)) == E_OK )
			{
				break;
			}
			sig_sem(LEFT_FORK(id));
			dly_tsk((rand() % 10 + 1) * 10);	/* Ŭ�����Ԥ� */
		}
		
		/* �������� */
		SetLed(id);			/* ���������� */
		dly_tsk(1000);
		ResetLed(id);
		
		/* �ե����������� */
		sig_sem(LEFT_FORK(id));
		sig_sem(RIGHT_FORK(id));
	}
}


/* �б���LED���� */
void SetLed(INT id)
{
	wai_sem(SEMID_SYSCS);
	*SH_PEDR &= ~(0x01 << (id - 1));
	sig_sem(SEMID_SYSCS);
}


/* �б�LDE�ξ��� */
void ResetLed(INT id)
{
	wai_sem(SEMID_SYSCS);
	*SH_PEDR |= (0x01 << (id - 1));
	sig_sem(SEMID_SYSCS);
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
