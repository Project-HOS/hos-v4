// ===========================================================================
//  HOS-V4 コンフィギュレーター
//    CRE_TSK API の処理
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ===========================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "apiinc.h"
#include "analize.h"


// コンストラクタ
CApiInclude::CApiInclude()
{
	// パラメーター構文設定
	m_iParamSyntax[0] = 0;		// 単独パラメーター
	m_iParams = 1;
}

// デストラクタ
CApiInclude::~CApiInclude()
{
}


// API名取得
char* CApiInclude::GetApiName(void)
{
	return "INCLUDE";
}


// パラメーター追加
int CApiInclude::AddParams(const char* pszParams)
{
	char szBuf[4096];
	int iErr;
	
	// 親クラス呼び出し
	iErr = CApiDef::AddParams(pszParams);
	if ( iErr != CFG_ERR_OK )
	{
		return iErr;
	}

	// 文字列の展開
	iErr = CAnalize::DecodeText(szBuf, m_pParamPacks[m_iObjs - 1]->GetParam(0));
	if ( iErr != CFG_ERR_OK )
	{
		return iErr;
	}
	m_pParamPacks[m_iObjs - 1]->SetParam(0, szBuf);

	return CFG_ERR_OK;
}


// 文字列を展開
int CApiInclude::AutoId(void)
{
	return CFG_ERR_OK;
}


// cfgファイル定義部書き出し
void  CApiInclude::WriteCfgDef(FILE* fp)
{
	int i;

	if ( m_iObjs == 0)
	{
		return;
	}

	fputs("\n", fp);

	for ( i = 0; i < m_iObjs; i++ )
	{
		fprintf(fp, "#include %s\n", m_pParamPacks[i]->GetParam(0));
	}
}


// ===========================================================================
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ===========================================================================
