// ---------------------------------------------------------------------------
//  HOS-V4 ����ե�����졼����
//    �ᥤ��롼����
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "read.h"
#include "analize.h"
#include "apiinc.h"
#include "knlheap.h"
#include "timtic.h"
#include "maxtmout.h"
#include "maxtpri.h"
#include "cretsk.h"
#include "deftex.h"
#include "cresem.h"
#include "creflg.h"
#include "credtq.h"
#include "crembx.h"
#include "crembf.h"
#include "crempf.h"
#include "crecyc.h"
#include "attisr.h"
#include "attini.h"
#include "defexc.h"


#define MAX_PATH	1024		// ����ѥ�̾


int  ReadConfigFile(FILE* fpConfig);	// ����ե�����졼�����ե������ɤ߹���
void WriteIdFile(FILE* fp);				// ID ����إå��ե��������
void WriteCfgFile(FILE* fp);			// C ���쥽��������


CApiInclude    g_ApiInclude;
CApiKernelHeap g_ApiKernelHeap;
CApiTimTic     g_ApiTimTic;
CApiMaxTimout  g_ApiMaxTimout;
CApiMaxTpri    g_ApiMaxTpri;
CApiCreTsk     g_ApiCreTsk;
CApiDefTex     g_ApiDefTex;
CApiCreSem     g_ApiCreSem;
CApiCreFlg     g_ApiCreFlg;
CApiCreDtq     g_ApiCreDtq;
CApiCreMbx     g_ApiCreMbx;
CApiCreMbf     g_ApiCreMbf;
CApiCreMpf     g_ApiCreMpf;
CApiCreCyc     g_ApiCreCyc;
CApiAttIsr     g_ApiAttIsr;
CApiAttIni     g_ApiAttIni;
CApiDefExc     g_ApiDefExc;

static char s_szInputFile[MAX_PATH]  = "system.cfg";
static char s_szIdFile[MAX_PATH]     = "kernel_id.h";
static char s_szCfgFile[MAX_PATH]    = "kernel_cfg.c";

// API����ꥹ��
static CApiDef* g_ApiList[] =
	{
		&g_ApiInclude,
		&g_ApiKernelHeap,
		&g_ApiTimTic,
		&g_ApiMaxTimout,
		&g_ApiMaxTpri,
		&g_ApiCreTsk,
		&g_ApiDefTex,
		&g_ApiCreSem,
		&g_ApiCreFlg,
		&g_ApiCreDtq,
		&g_ApiCreMbx,
		&g_ApiCreMbf,
		&g_ApiCreMpf,
		&g_ApiCreCyc,
		&g_ApiAttIsr,
		&g_ApiAttIni,
		&g_ApiDefExc,
	};

#define API_COUNT	((int)(sizeof(g_ApiList) / sizeof(CApiDef*)))		// API�Ŀ�




// �ᥤ��ؿ�
int main(int argc, char *argv[])
{
	FILE* fpInput;
	FILE* fpCfg;
	FILE* fpId;
	int  iErr;
	int  i;

	// ���ޥ�ɥ饤�����
	for ( i = 1; i < argc; i++ )
	{
		if ( strcmp(argv[i], "-c") == 0 )
		{
			i++;
			if ( i >= argc )
			{
				fprintf(stderr, "option error \"-c\"\n");
				return 1;
			}
			strncpy(s_szCfgFile, argv[i], MAX_PATH - 1);
			s_szCfgFile[MAX_PATH - 1] = '\0';
		}
		else if ( strcmp(argv[i], "-i") == 0 )
		{
			i++;
			if ( i >= argc )
			{
				fprintf(stderr, "option error \"-i\"\n");
				return 1;
			}
			strncpy(s_szIdFile, argv[i], MAX_PATH - 1);
			s_szIdFile[MAX_PATH - 1] = '\0';
		}
		else
		{
			strncpy(s_szInputFile, argv[i], MAX_PATH - 1);
			s_szInputFile[MAX_PATH - 1] = '\0';
		}
	}

	// ���ϥե����륪���ץ�
	if ( (fpInput = fopen(s_szInputFile, "r")) == NULL )
	{
		printf("could not open file \"%s\"\n", s_szInputFile);
		return 1;
	}

	// ����ե�����졼�����ե������ɤ߹���
	iErr = ReadConfigFile(fpInput) != 0;
	fclose(fpInput);
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
	if ( (fpId = fopen(s_szIdFile, "w")) == NULL )
	{
		printf("could not open file \"%s\"\n", s_szIdFile);
		return 1;
	}

	WriteIdFile(fpId);

	fclose(fpId);


	// Cfg�ե����륪���ץ�
	if ( (fpCfg = fopen(s_szCfgFile, "w")) == NULL )
	{
		printf("could not open file \"%s\"\n", s_szCfgFile);
		return 1;
	}

	WriteCfgFile(fpCfg);

	fclose(fpCfg);

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
			printf("%s line(%d) : %s\n",
					s_szInputFile, read.GetLineNum(), GetErrMessage(iErr));
			return 1;
		}

		// ��ʸ����
		iErr = CAnalize::SplitState(szApiName, szParams, szState);
		if ( iErr != CFG_ERR_OK )
		{
			printf("%s line(%d) : %s\n",
					s_szInputFile, read.GetLineNum(), GetErrMessage(iErr));
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
			printf("%s line(%d) : %s\n",
					s_szInputFile, read.GetLineNum(), GetErrMessage(iErr));
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
		"/* ------------------------------------------------------------------------ */\n"
		"/*  HOS-V4  kernel configuration                                            */\n"
		"/*    kernel object ID definition                                           */\n"
		"/*                                                                          */\n"
		"/* ------------------------------------------------------------------------ */\n"
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
		"/* ------------------------------------------------------------------------ */\n"
		"/*  End of file                                                             */\n"
		"/* ------------------------------------------------------------------------ */\n"
		, fp);
}


// C ���쥽��������
void WriteCfgFile(FILE* fp)
{
	int i;

	/* �إå����� */
	fprintf(
		fp,
		"/* ------------------------------------------------------------------------ */\n"
		"/*  HOS-V4  kernel configuration                                            */\n"
		"/*    kernel object create and initialize                                   */\n"
		"/*                                                                          */\n"
		"/* ------------------------------------------------------------------------ */\n"
		"\n\n"
		"#include \"kernel.h\"\n"
		"#include \"%s\"\n"
		, s_szIdFile);

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
		"/* ------------------------------------------------------------------------ */\n"
		"/*  End of file                                                             */\n"
		"/* ------------------------------------------------------------------------ */\n"
		, fp);
}


// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------
