/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    �ץ��å���ݲ�����ݡ��ͥ�� (Windows��)                            */
/*                                                                          */
/*                               Copyright (C) 1998-2002 by Ryuji Fuchikami */
/* ------------------------------------------------------------------------ */


#include <stdlib.h>
#include "kernel.h"
#include "hospac.h"




/* ����åɺ���ѥꥹ�� */
typedef struct t_hospac_dellist
{
	HANDLE hThread;					/* ������륹��åɥϥ�ɥ� */
	struct t_hospac_dellist *next;	/* ���κ���ꥹ�� */
} T_HOSPAC_DELLIST;



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
void hospac_cre_cnt(
		T_HOSPAC_CTXINF *pk_ctxinf,		/* ����ƥ����Ȥ�������륢�ɥ쥹 */
		VP_INT exinf,					/* �������μ¹Ի��ѥ�᡼�� */
		FP    task,						/* �������ε�ư���� */
		SIZE  stksz,					/* �����å��ΰ�Υ����� */
		VP    stk)						/* �����å��ΰ����Ƭ���� */
{
	DWORD dwThreadId;
	pk_ctxinf->hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)task,
								(LPVOID)exinf, CREATE_SUSPENDED, &dwThreadId);
}


/* �¹ԥ���ƥ����Ȥκ�� */
void hospac_del_cnt(T_HOSPAC_CTXINF *pk_ctxinf)
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
void hospac_swi_cnt(
		T_HOSPAC_CTXINF *pk_pre_ctxinf,		/* ���ߤΥ���ƥ����Ȥ���¸�� */
		T_HOSPAC_CTXINF *pk_nxt_ctxinf)		/* �����˼¹Ԥ��륳��ƥ����� */
{
	static volatile HANDLE hPrevThread;
	T_HOSPAC_DELLIST *pDelList;
	T_HOSPAC_DELLIST *pDelListTmp;;

	/* ���Υ����ɥ뤫��ε�ư�ʤ饹��åɥϥ�ɥ����� */
	if ( pk_pre_ctxinf->hThread == NULL )
	{
		HANDLE hProcess;
		hProcess = GetCurrentProcess();
		DuplicateHandle(hProcess, GetCurrentThread(), hProcess,
					&pk_pre_ctxinf->hThread, 0, TRUE, DUPLICATE_SAME_ACCESS);
	}

	/* ���ߤΥ���åɤ���¸ */
	hPrevThread = pk_pre_ctxinf->hThread;
	
	/* ����åɤ��ۤʤ���ڤ��ؤ��� */
	if ( pk_nxt_ctxinf != pk_pre_ctxinf )
	{
		/* �����ʥ���åɤ˼¹Ԥ��ڤ��ؤ��� */
		ResumeThread(pk_nxt_ctxinf->hThread);
		SuspendThread(pk_pre_ctxinf->hThread);

		/* ľ���Υ���åɤ������˥����ڥ�ɤ���ޤ��Ԥ� */
		while ( SuspendThread(hPrevThread) == 2 )
		{
			ResumeThread(hPrevThread);
			Sleep(0);
		}
		ResumeThread(hPrevThread);
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
		isig_tim();		/* ������ƥ��å����� */
		Sleep(10);
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
