// ---------------------------------------------------------------------------
//  HOS-V4 コンフィギュレーター
//    HOS_MAX_TPRI API の処理
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "maxtpri.h"
#include "analyze.h"



// コンストラクタ
CApiMaxTpri::CApiMaxTpri()
{
	// パラメーター構文設定
	m_iParamSyntax[0] = 0;		// 単独パラメーター
	m_iParams         = 1;

	m_iMaxPri = 16;
}


// デストラクタ
CApiMaxTpri::~CApiMaxTpri()
{
}



// APIの解析
int CApiMaxTpri::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	// API名チェック
	if ( strcmp(pszApiName, "HOS_MAX_TPRI") != 0 )
	{
		return CFG_ERR_NOPROC;
	}

	if ( atoi(pszParams) <= 0 )
	{
		return CFG_ERR_PARAM;
	}
	m_iMaxPri = atoi(pszParams);

	return CFG_ERR_OK;
}


// 文字列を展開
int CApiMaxTpri::AutoId(void)
{
	return CFG_ERR_OK;
}


// cfgファイル定義部書き出し
void  CApiMaxTpri::WriteCfgDef(FILE* fp)
{
	fprintf(
		fp,
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*           create ready queue               */\n"
		"/* ------------------------------------------ */\n"
		"\n"
		"T_MKNL_QUE mknl_rdq_tbl[%d];\n"
		"const INT mknl_rdq_cnt = %d;\n",
		m_iMaxPri,
		m_iMaxPri);
}


// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------
