// ===========================================================================
//  HOS-V4 ����ե�����졼����
//    �ᥤ��롼����
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ===========================================================================


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "read.h"
#include "analize.h"
#include "apiinc.h"
#include "maxtpri.h"
#include "maxtmout.h"
#include "timtic.h"
#include "cretsk.h"
#include "cresem.h"
#include "creflg.h"
#include "credtq.h"
#include "crecyc.h"
#include "attisr.h"
#include "attini.h"


#define MAX_PATH	1024		// ����ѥ�̾


int  ReadConfigFile(FILE* fpConfig);	// ����ե�����졼�����ե������ɤ߹���
void WriteIdFile(FILE* fp);				// ID ����إå��ե��������
void WriteCfgFile(FILE* fp);			// C ���쥽��������


CApiInclude   g_ApiInclude;
CApiMaxTpri   g_ApiMaxTpri;
CApiMaxTimout g_ApiMaxTimout;
CApiTimTic    g_ApiTimTic;
CApiCreTsk    g_ApiCreTsk;
CApiCreSem    g_ApiCreSem;
CApiCreFlg    g_ApiCreFlg;
CApiCreDtq    g_ApiCreDtq;
CApiCreCyc    g_ApiCreCyc;
CApiAttIsr    g_ApiAttIsr;
CApiAttIni    g_ApiAttIni;

static char szConfigFile[MAX_PATH] = "system.cfg";
static char szIdFile[MAX_PATH]     = "kernel_id.h";
static char szCfgFile[MAX_PATH]    = "kernel_cfg.c";

// API����ꥹ��
static CApiDef* g_ApiList[] =
	{
		&g_ApiInclude,
		&g_ApiMaxTpri,
		&g_ApiMaxTimout,
		&g_ApiTimTic,
		&g_ApiCreTsk,
		&g_ApiCreSem,
		&g_ApiCreFlg,
		&g_ApiCreDtq,
		&g_ApiCreCyc,
		&g_ApiAttIsr,
		&g_ApiAttIni,
	};

#define API_COUNT	(sizeof(g_ApiList) / sizeof(CApiDef*))		// API�Ŀ�




// �ᥤ��ؿ�
int main(int argc, char *argv[])
{
	FILE* fp;
	int  iErr;
	int  i;

	if ( argc >= 2 )
	{
		strcpy(szConfigFile, argv[1]);
	}

	// ����ե�����졼�����ե����륪���ץ�
	if ( (fp = fopen(szConfigFile, "r")) == NULL )
	{
		printf("\"%s\" �������ޤ���\n", szConfigFile);
		return 1;
	}

	// ����ե�����졼�����ե������ɤ߹���
	iErr = ReadConfigFile(fp) != 0;
	fclose(fp);
	if ( iErr != 0 )
	{
		return 1;
	}

	// ��ưID�ֹ�������
	for ( i = 0; i < API_COUNT; i++ )
	{
		g_ApiList[i]->AutoId();
	}

	// ID ����ե����륪���ץ�
	if ( (fp = fopen(szIdFile, "w")) == NULL )
	{
		return 1;
	}

	WriteIdFile(fp);

	fclose(fp);


	// ID ����ե����륪���ץ�
	if ( (fp = fopen(szCfgFile, "w")) == NULL )
	{
		return 1;
	}

	WriteCfgFile(fp);

	fclose(fp);

	return 0;
}


// ����ե�����졼�����ե������ɤ߹���
int ReadConfigFile(FILE* fpConfig)
{
	char szState[READ_MAX_STATE];
	char szApiName[READ_MAX_STATE];
	char szParams[READ_MAX_STATE];
	int  iErr;
	int  i;

	CRead read(fpConfig);	// �ɤ߽Ф����֥�����������

	// �ɤ߹���
	while (	(iErr = read.ReadState(szState)) != CFG_ERR_COMPLETE )
	{
		// �ɤ߹��ߥ��顼�����å�
		if ( iErr != CFG_ERR_OK )
		{
			printf("%s (%d) : error(%d)\n",
					szConfigFile, read.GetLineNum(), iErr);
			return 1;
		}

		// ��ʸ����
		iErr = CAnalize::SplitState(szApiName, szParams, szState);
		if ( iErr != CFG_ERR_OK )
		{
			printf("%s (%d) : error(%d) Syntax Error\n",
					szConfigFile, read.GetLineNum(), iErr);
			return 1;
		}
		CAnalize::SpaceCut(szApiName);
		CAnalize::SpaceCut(szParams);

		// API����
		iErr = CFG_ERR_SYNTAX;
		for ( i = 0; i < API_COUNT; i++ )
		{
			iErr = g_ApiList[i]->AnalizeApi(szApiName, szParams);
			if ( iErr != CFG_ERR_NOPROC )
			{
				break;
			}
		}
		if ( iErr != CFG_ERR_OK )
		{
			printf("err(%d)\n", iErr);
			return 1;
		}
	}

	return 0;
}


// ID����إå��ե��������
void WriteIdFile(FILE* fp)
{
	int i;

	/* �إå����� */
	fputs(
		"/* ======================================================================== */\n"
		"/*  HOS-V4  kernel configuration                                            */\n"
		"/*    kernel object ID definition                                           */\n"
		"/*                                                                          */\n"
		"/*                                   Copyright (C) 2002 by Ryuji Fuchikami  */\n"
		"/* ======================================================================== */\n"
		"\n\n"
		"#ifndef __HOS_V4__kernel_cfg_h__\n"
		"#define __HOS_V4__kernel_cfg_h__\n"
		"\n"
		, fp);

	// ID ����ե��������
	for ( i = 0; i < API_COUNT; i++ )
	{
		g_ApiList[i]->WriteId(fp);
	}

	// �եå�����
	fputs(
		"\n\n\n"
		"#endif\t/* __HOS_V4__kernel_cfg_h__ */\n"
		"\n\n"
		"/* ======================================================================== */\n"
		"/*  Copyright (C) 2002 by Ryuji Fuchikami                                   */\n"
		"/* ======================================================================== */\n"
		, fp);
}


// C ���쥽��������
void WriteCfgFile(FILE* fp)
{
	int i;

	/* �إå����� */
	fputs(
		"/* ======================================================================== */\n"
		"/*  HOS-V4  kernel configuration                                            */\n"
		"/*    kernel object create and initialize                                   */\n"
		"/*                                                                          */\n"
		"/*                                   Copyright (C) 2002 by Ryuji Fuchikami  */\n"
		"/* ======================================================================== */\n"
		"\n\n"
		"#include \"kernel.h\"\n"
		"#include \"kernel_id.h\"\n"
		, fp);

	// ID ����ե��������
	for ( i = 0; i < API_COUNT; i++ )
	{
		g_ApiList[i]->WriteCfgDef(fp);
	}

	// ������ؿ������Ƚ���
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*          initialize functions              */\n"
		"/* ------------------------------------------ */\n",
		fp);

	// ������ؿ�����
	fputs(
		"\n/* object initialize */\n"
		"void kernel_cfg_init(void)\n"
		"{\n"
		"\tint i;\n",
		fp);
	for ( i = 0; i < API_COUNT; i++ )
	{
		g_ApiList[i]->WriteCfgIni(fp);
	}
	fputs("}\n", fp);

	// ������ؿ�����
	fputs(
		"\n/* start up */\n"
		"void kernel_cfg_start(void)\n"
		"{\n",
		fp);
	for ( i = 0; i < API_COUNT; i++ )
	{
		g_ApiList[i]->WriteCfgStart(fp);
	}
	fputs("}\n", fp);

	// �եå�����
	fputs(
		"\n\n"
		"/* ======================================================================== */\n"
		"/*  Copyright (C) 2002 by Ryuji Fuchikami                                   */\n"
		"/* ======================================================================== */\n"
		, fp);
}


// ===========================================================================
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ===========================================================================
