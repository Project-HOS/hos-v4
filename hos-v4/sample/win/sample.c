/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ����ץ�ץ����                           */
/*   ������ů�ؼԤο���������                                             */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



#include <stdio.h>
#include "kernel.h"
#include "kernel_id.h"
#include "sample.h"



#define LEFT_FORK(id)	((id) % 5 + 1)
#define RIGHT_FORK(id)	(id)


static char status[] = "TTTTT\n";



/* �ᥤ��ؿ� */
int main()
{
	/* HOS-V4 �γ��� */
	sta_hos();
	
	return 0;
}


/* ATT_INI ��Ͽ�δؿ� */
void SampleInitialize(VP_INT exinf)
{
	/* ��������ư */
	act_tsk(TSKID_PHILOSOPHER1);
	act_tsk(TSKID_PHILOSOPHER2);
	act_tsk(TSKID_PHILOSOPHER3);
	act_tsk(TSKID_PHILOSOPHER4);
	act_tsk(TSKID_PHILOSOPHER5);
}


/* ů�ؼԥ����� */
void PhilosopherTask(VP_INT exinf)
{
	INT id;

	id = (INT)exinf;

	/* Ķ�Ф����르�ꥺ�� */
	for ( ; ; )
	{
		/* Ŭ���ʻ���Ǻ��Ǥߤ� */
		status[id -1] = 'T';
		printf(status);
		dly_tsk((rand() % 100) * 10 + 500);

		/* �����Υե���������ޤ�Ǵ�� */
		status[id -1] = 'W';
		printf(status);
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
		status[id -1] = 'E';
		printf(status);
		dly_tsk(1000);

		/* �ե����������� */
		sig_sem(LEFT_FORK(id));
		sig_sem(RIGHT_FORK(id));
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
