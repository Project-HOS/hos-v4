// ---------------------------------------------------------------------------
//  HOS-V4 コンフィギュレーター
//    HOS_MAX_TIMOUT API の処理
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "maxtmout.h"
#include "analize.h"



// コンストラクタ
CApiMaxTimout::CApiMaxTimout()
{
	// パラメーター構文設定
	m_iParamSyntax[0] = 0;		// 単独パラメーター
	m_iParams         = 1;

	m_iMaxTimout = 16;
}


// デストラクタ
CApiMaxTimout::~CApiMaxTimout()
{
}



// APIの解析
int CApiMaxTimout::AnalizeApi(const char* pszApiName, const char* pszParams)
{
	// API名チェック
	if ( strcmp(pszApiName, "HOS_MAX_TIMOUT") != 0 )
	{
		return CFG_ERR_NOPROC;
	}

	if ( atoi(pszParams) <= 0 )
	{
		return CFG_ERR_PARAM;
	}
	m_iMaxTimout = atoi(pszParams);

	return CFG_ERR_OK;
}


// 文字列を展開
int CApiMaxTimout::AutoId(void)
{
	return CFG_ERR_OK;
}


// cfgファイル定義部書き出し
void  CApiMaxTimout::WriteCfgDef(FILE* fp)
{
	fprintf(
		fp,
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*          create time-out queue             */\n"
		"/* ------------------------------------------ */\n"
		"\n"
		"T_MKNL_TIMOUT mknl_timout[%d];\n"
		"const INT     mknl_timout_size = %d;\n",
		m_iMaxTimout,
		m_iMaxTimout);
}


// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------
