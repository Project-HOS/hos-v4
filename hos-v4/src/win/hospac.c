/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �ץ��å���ݲ�����ݡ��ͥ�� (Windows��)                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include <stdlib.h>
#include "kernel.h"
#include "hospac.h"



/* ���������� */
typedef struct t_TaskInfo
{
	VP_INT exinf;			/* �������μ¹Ի��ѥ�᡼�� */
	FP     task;			/* �������ε�ư���� */
} T_TaskInfo;


/* ����åɺ���ѥꥹ�� */
typedef struct t_hospac_dellist
{
	HANDLE hThread;					/* ������륹��åɥϥ�ɥ� */
	struct t_hospac_dellist *next;	/* ���κ���ꥹ�� */
} T_HOSPAC_DELLIST;



DWORD WINAPI TaskEntry(LPVOID param);	/* ����åɤγ��ϴؿ� */



static HANDLE           hospac_hSem      = NULL;	/* �����ƥ����¾�����ѥ��ޥե� */
static T_HOSPAC_DELLIST *hospac_pDelList = NULL;	/* ����åɺ���ѥꥹ�� */



/* �����ƥ�ν���� */
void hospac_ini_sys(void)
{
	/* �����߶ػߤ˸�Ω�Ƥ륻�ޥե��κ��� */
	hospac_hSem = CreateSemaphore(NULL, 1, 1, NULL);
}


/* �����ߵ��� */
void hospac_ena_int(void)
{
	ReleaseSemaphore(hospac_hSem, 1, NULL);
}


/* �����߶ػ� */
void hospac_dis_int(void)
{
	WaitForSingleObject(hospac_hSem, INFINITE);
}


/* �¹ԥ���ƥ����Ȥκ��� */
void hospac_cre_ctx(
		T_HOSPAC_CTXINF *pk_ctxinf,		/* ����ƥ����Ȥ�������륢�ɥ쥹 */
		VP_INT          exinf,			/* �������μ¹Ի��ѥ�᡼�� */
		FP              task,			/* �������ε�ư���� */
		SIZE            stksz,			/* �����å��ΰ�Υ����� */
		VP              stk)			/* �����å��ΰ����Ƭ���� */
{
	T_TaskInfo *pInfo;
	DWORD      dwThreadId;

	/* ������������Ǽ */
	pInfo = (T_TaskInfo *)GlobalAlloc(GMEM_FIXED, sizeof(T_TaskInfo));
	pInfo->task  = task;
	pInfo->exinf = exinf;

	/* ����åɤ򥵥��ڥ�ɾ��֤����� */
	pk_ctxinf->hThread = CreateThread(NULL, 0, TaskEntry,
								(LPVOID)&pInfo, CREATE_SUSPENDED, &dwThreadId);
}


/* ����åɤγ��ϴؿ� */
DWORD WINAPI TaskEntry(LPVOID param)
{
	T_TaskInfo Info;

	Info = *(T_TaskInfo *)param;

	GlobalFree((HGLOBAL)param);

	Info.task(Info.exinf);

	return 0;
}


/* �¹ԥ���ƥ����Ȥκ�� */
void hospac_del_ctx(T_HOSPAC_CTXINF *pk_ctxinf)
{
	T_HOSPAC_DELLIST *pDelList;

	/* ����ꥹ�Ȥκ��� */
	pDelList = (T_HOSPAC_DELLIST *)malloc(sizeof(T_HOSPAC_DELLIST));
	pDelList->hThread = pk_ctxinf->hThread;

	/* ����ꥹ�Ȥ��ɲ� */
	if ( hospac_pDelList == NULL )
	{
		pDelList->next = NULL;
	}
	else
	{
		pDelList->next = hospac_pDelList;
	}
	hospac_pDelList = pDelList;
}


/* �¹ԥ���ƥ����Ȥ����� */
void hospac_swi_ctx(
		T_HOSPAC_CTXINF *pk_pre_ctxinf,		/* ���ߤΥ���ƥ����Ȥ���¸�� */
		T_HOSPAC_CTXINF *pk_nxt_ctxinf)		/* �����˼¹Ԥ��륳��ƥ����� */
{
	T_HOSPAC_DELLIST *pDelList;
	T_HOSPAC_DELLIST *pDelListTmp;
	DWORD dwCount;
	
	/* ����åɤ��ۤʤ���ڤ��ؤ��� */
	if ( pk_nxt_ctxinf != pk_pre_ctxinf )
	{
		/* �ڤ��ؤ��оݤ������ڥ����Ǥ��뤳�Ȥ��ǧ */
		for ( ; ; )
		{
			/* �����ڥ�ɥ����󥿤�����٤˥����ڥ�ɤ����Ƥߤ� */
			while ( (dwCount = SuspendThread(pk_nxt_ctxinf->hThread)) == 0xffffffff )
			{
				Sleep(0);
			}
			ResumeThread(pk_nxt_ctxinf->hThread);
			
			/* �����󥿤�1�Ǥʤ���Х����ڥ�ɤ��Ƥ��� */
			if ( dwCount > 1 )
			{
				break;
			}

			/* �����ڥ�ɴ�λ�ޤ��Ԥ� */
			Sleep(1);
		}

		/* �ڤ��ؤ���Υ���åɤ򵯤��� */
		ResumeThread(pk_nxt_ctxinf->hThread);

		/* ��ʬ���Ȥ򥵥��ڥ�ɤ����� */
		SuspendThread( GetCurrendT
	}

	/* ����ꥹ�Ȥ˥���åɤ�����Ф��Υ����ߥ󥰤Ǻ�� */
	pDelList = hospac_pDelList;
	while ( pDelList != NULL )
	{
		TerminateThread(pDelList->hThread, 0);
		CloseHandle(pDelList->hThread);
		pDelListTmp = pDelList;
		pDelList = pDelList->next;
		free(pDelListTmp);
	}
	hospac_pDelList = NULL;
}


/* �㳰�����¹����� */
void hospac_set_tex(
		T_HOSPAC_CTXINF *pk_pre_ctxinf,		/* �㳰���������ꤹ�륳��ƥ����� */
		void (*exp)(TEXPTN),				/* �㳰�����ϥ�ɥ�Υ��ɥ쥹 */
		TEXPTN rasptn)						/* �㳰�����ϥ�ɥ���Ϥ��㳰�װ� */
{
	/* ��ĥ��Ф��ޤ����Ϻ�줽�������ҤȤޤ���α */
	/* �ɤä��ߤ� Windows�Ǥϥ����å���Ʊ���ޤޤ�ʬ��������ʤΤ� */
	/* longjmp �ʤɤ�ȯ�ԤǤ��ʤ��Ȥ���� */

	return;
}


/* �����ɥ���ν��� */
void hospac_idle(void)
{
	/* �ޥ�����ʤ�ʾ������ϥ⡼�ɤ��ڤ��ؤ���ʤɲ�ǽ */

	/* Windows �ǤϤ�����¾�Υץ����˥ץ��å�������򶡵�ȤȤ�� */
	/* ���󥿡��Х륿���ޤΥ��ߥ�졼����� */
	for ( ; ; )
	{
		dis_dsp();
		isig_tim();		/* ������ƥ��å����� */
		ena_dsp();
		Sleep(10);
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
