/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �ץ��å���ݲ�����ݡ��ͥ�� (Windows��)                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include <stdlib.h>
#include "hospac.h"
#include <tchar.h>


/* ���������� */
typedef struct t_TaskInfo
{
	VP_INT exinf;			/* �������μ¹Ի��ѥ�᡼�� */
	FP     task;			/* �������ε�ư���� */
} T_TaskInfo;



DWORD WINAPI TaskEntry(LPVOID param);	/* ����åɤγ��ϴؿ� */
void  HookPrimaryThread(void);			/* �ץ饤�ޥꥹ��åɤΥեå� */

HANDLE hospac_hSem  = NULL;				/* �����ƥ����¾�����ѥ��ޥե� */
BOOL   hospac_blInt = FALSE;			/* �����߽�����ե饰 */

static DWORD  hPrimaryThreadId;			/* �ץ饤�ޥꥹ��å�ID */
static HANDLE hThreadDelete = NULL;		/* ������륹��åɥϥ�ɥ� */



/* �����ƥ�ν���� */
void hospac_ini_sys(void)
{
	/* �ץ饤�ޥꥹ��å�ID����¸ */
	hPrimaryThreadId = GetCurrentThreadId();

	/* �����߶ػߤ˸�Ω�Ƥ륻�ޥե��κ��� */
	hospac_hSem = CreateSemaphore(NULL, 0, 1, NULL);
}


/* �����ߵ��� */
void hospac_ena_int(void)
{
	if ( !hospac_blInt )
	{
		ReleaseSemaphore(hospac_hSem, 1, NULL);
	}
}


/* �����߶ػ� */
void hospac_dis_int(void)
{
	if ( !hospac_blInt )
	{
		WaitForSingleObject(hospac_hSem, INFINITE);
	}
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

	/* ������������Ǽ */
	pInfo = (T_TaskInfo *)GlobalAlloc(GMEM_FIXED, sizeof(T_TaskInfo));
	pInfo->task  = task;
	pInfo->exinf = exinf;
	
	/* ���� */
	pk_ctxinf->blIntSuspend = FALSE;
	pk_ctxinf->hThread = CreateThread(NULL, 0, TaskEntry, (LPVOID)pInfo,
									CREATE_SUSPENDED, &pk_ctxinf->dwThreadId);
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
	if ( GetCurrentThreadId() != pk_ctxinf->dwThreadId )
	{
		/* �¹��楹��åɤǤʤ����¨��� */
		TerminateThread(pk_ctxinf->hThread, 0);
	}
	else
	{
		/* �¹��楹��åɤʤ�����ͽ�� */
		hThreadDelete = pk_ctxinf->hThread;
	}
}


/* �¹ԥ���ƥ����Ȥ����� */
void hospac_swi_ctx(
		T_HOSPAC_CTXINF *pk_pre_ctxinf,		/* ���ߤΥ���ƥ����Ȥ���¸�� */
		T_HOSPAC_CTXINF *pk_nxt_ctxinf)		/* �����˼¹Ԥ��륳��ƥ����� */
{
	DWORD dwCount;

	if ( hospac_blInt )
	{
		return;
	}

	/* ����åɤ��ۤʤ���ڤ��ؤ��� */
	if ( pk_nxt_ctxinf != pk_pre_ctxinf )
	{
		/* �ڤ��ؤ��оݤ������ڥ����Ǥ��뤳�Ȥ��ǧ */
		for ( ; ; )
		{
			/* �����ڥ�ɥ����󥿤�����٤˥����ڥ�ɤ����Ƥߤ� */
			dwCount = SuspendThread(pk_nxt_ctxinf->hThread);
			ResumeThread(pk_nxt_ctxinf->hThread);
			
			/* �����󥿤�0�Ǥʤ���Х����ڥ�ɤ��Ƥ��� */
			if ( dwCount > 0 )
			{
				break;
			}
			
			/* �����ڥ�ɴ�λ�ޤ��Ԥ� */
			Sleep(1);
		}
		
		/* �ڤ��ؤ���Υ���åɤ򵯤��� */
		ResumeThread(pk_nxt_ctxinf->hThread);
		
		/* ���ޥե����ֵ� */
		if ( pk_nxt_ctxinf->blIntSuspend )
		{
			pk_nxt_ctxinf->blIntSuspend = FALSE;
			ReleaseSemaphore(hospac_hSem, 1, NULL);
		}
		
		/* �ץ饤�ޥꥹ��å�I�Υեå� */
		if ( hPrimaryThreadId == GetCurrentThreadId() )
		{
			HookPrimaryThread();
		}

		/* ��ʬ���Ȥ򥵥��ڥ�ɤ����� */
		SuspendThread(GetCurrentThread());
	}
	
	/* ���ͽ��Υ���åɤ�����к�� */
	if ( hThreadDelete != NULL )
	{
		TerminateThread(hThreadDelete, 0);
		CloseHandle(hThreadDelete);
		hThreadDelete = NULL;
	}
}


/* �����ɥ���ν��� */
void hospac_idle(void)
{
	/* �ޥ�����ʤ�ʾ������ϥ⡼�ɤ��ڤ��ؤ���ʤɲ�ǽ */
	
	/* ¾�Υץ����˼¹ԥ����ߥ󥰤�Ϳ���� */
	Sleep(1);
}


/* �ץ饤�ޥꥹ��åɤΥեå� */
void  HookPrimaryThread(void)
{
	/* ����������ɽ�� */
	MessageBox(NULL, _T("OK�򲡤��Ƚ�λ���ޤ�"), _T("Hyper Operationg System V4 for Win32"), MB_OK);

	/* ��λ */
	ExitProcess(0);
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
