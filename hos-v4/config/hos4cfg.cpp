// ===========================================================================
//  HOS-V4 コンフィギュレーター
//    メインルーチン
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
#include "cretsk.h"
#include "attisr.h"


#define MAX_PATH	1024		// 最大パス名

CApiInclude g_ApiInclude;
CApiCreTsk  g_ApiCreTsk;
CApiAttIsr  g_ApiAttIsr;

// API定義リスト
CApiDef* g_ApiList[] =
	{
		&g_ApiInclude,
		&g_ApiCreTsk,
		&g_ApiAttIsr,
	};

#define API_COUNT	(sizeof(g_ApiList) / sizeof(CApiDef*))		// API個数


int  ReadConfigFile(FILE* fpConfig);	// コンフィギュレーションファイル読み込み
void WriteIdFile(FILE* fp);				// ID 定義ヘッダファイル出力
void WriteCfgFile(FILE* fp);			// C 言語ソース出力

char szConfigFile[MAX_PATH] = "system.cfg";
char szIdFile[MAX_PATH]     = "kernel_id.h";
char szCfgFile[MAX_PATH]    = "kernel_cfg.c";



// メイン関数
int main(int argc, char *argv[])
{
	FILE* fp;
	int  iErr;
	int  i;

	if ( argc >= 2 )
	{
		strcpy(szConfigFile, argv[1]);
	}

	// コンフィギュレーションファイルオープン
	if ( (fp = fopen(szConfigFile, "r")) == NULL )
	{
		printf("\"%s\" が開けません\n", szConfigFile);
		return 1;
	}

	// コンフィギュレーションファイル読み込み
	iErr = ReadConfigFile(fp) != 0;
	fclose(fp);
	if ( iErr != 0 )
	{
		return 1;
	}

	// 自動ID番号割り当て
	for ( i = 0; i < API_COUNT; i++ )
	{
		g_ApiList[i]->AutoId();
	}

	// ID 定義ファイルオープン
	if ( (fp = fopen(szIdFile, "w")) == NULL )
	{
		return 1;
	}

	WriteIdFile(fp);

	fclose(fp);


	// ID 定義ファイルオープン
	if ( (fp = fopen(szCfgFile, "w")) == NULL )
	{
		return 1;
	}

	WriteCfgFile(fp);

	fclose(fp);

	return 0;
}


// コンフィギュレーションファイル読み込み
int ReadConfigFile(FILE* fpConfig)
{
	char szState[READ_MAX_STATE];
	char szApiName[READ_MAX_STATE];
	char szParams[READ_MAX_STATE];
	int  iErr;
	int  i;

	CRead read(fpConfig);	// 読み出しオブジェクト生成

	// 読み込み
	while (	(iErr = read.ReadState(szState)) != CFG_ERR_COMPLETE )
	{
		// 読み込みエラーチェック
		if ( iErr != CFG_ERR_OK )
		{
			printf("%s (%d) : error(%d)\n",
					szConfigFile, read.GetLineNum(), iErr);
			return 1;
		}

		// 構文解析
		iErr = CAnalize::SplitState(szApiName, szParams, szState);
		if ( iErr != CFG_ERR_OK )
		{
			printf("%s (%d) : error(%d) Syntax Error\n",
					szConfigFile, read.GetLineNum(), iErr);
			return 1;
		}
		CAnalize::SpaceCut(szApiName);
		CAnalize::SpaceCut(szParams);
		printf("\nAPI :\"%s\"\nPAR :\"%s\"\n", szApiName, szParams);

		// API検索
		iErr = CFG_ERR_SYNTAX;
		for ( i = 0; i < API_COUNT; i++ )
		{
			if ( strcmp(szApiName, g_ApiList[i]->GetApiName()) == 0 )
			{
				iErr = g_ApiList[i]->AddParams(szParams);
				break;
			}
		}
		if ( iErr != CFG_ERR_OK )
		{
			return 1;
		}
	}

	return 0;
}


// ID定義ヘッダファイル出力
void WriteIdFile(FILE* fp)
{
	int i;

	/* ヘッダ出力 */
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

	// ID 定義ファイル出力
	for ( i = 0; i < API_COUNT; i++ )
	{
		g_ApiList[i]->WriteId(fp);
	}

	// フッタ出力
	fputs(
		"\n\n\n"
		"#endif\t/* __HOS_V4__kernel_cfg_h__ */\n"
		"\n\n"
		"/* ======================================================================== */\n"
		"/*  Copyright (C) 2002 by Ryuji Fuchikami                                   */\n"
		"/* ======================================================================== */\n"
		, fp);
}


// C 言語ソース出力
void WriteCfgFile(FILE* fp)
{
	int i;

	/* ヘッダ出力 */
	fputs(
		"/* ======================================================================== */\n"
		"/*  HOS-V4  kernel configuration                                            */\n"
		"/*    kernel object create and initialize                                   */\n"
		"/*                                                                          */\n"
		"/*                                   Copyright (C) 2002 by Ryuji Fuchikami  */\n"
		"/* ======================================================================== */\n"
		"\n\n"
		"#include \"kernel.h\"\n"
		, fp);

	// ID 定義ファイル出力
	for ( i = 0; i < API_COUNT; i++ )
	{
		g_ApiList[i]->WriteCfgDef(fp);
	}

	// 初期化関数コメント出力
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*          initialize functions              */\n"
		"/* ------------------------------------------ */\n",
		fp);

	// 初期化関数出力
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

	// 初期化関数出力
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

	// フッタ出力
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
