// ===========================================================================
//  HOS-V4 コンフィギュレーター
//    ATT_INI API の処理
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ===========================================================================


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "attini.h"
#include "analize.h"

#define ATTINI_INIATR		0
#define ATTINI_EXINF		1
#define ATTINI_INIRTN		2


// コンストラクタ
CApiAttIni::CApiAttIni()
{
	// パラメーター構文設定
	m_iParamSyntax[0] = 3;		// 単独パラメーター
	m_iParams         = 1;
}


// デストラクタ
CApiAttIni::~CApiAttIni()
{
}



// APIの解析
int CApiAttIni::AnalizeApi(const char* pszApiName, const char* pszParams)
{
	if ( strcmp(pszApiName, "ATT_INI") == 0 )
	{
		return AddParams(pszParams);
	}

	return CFG_ERR_NOPROC;
}


// 文字列を展開
int CApiAttIni::AutoId(void)
{
	return CFG_ERR_OK;
}


// cfgファイル定義部書き出し
void  CApiAttIni::WriteCfgStart(FILE* fp)
{
	int i;

	if ( m_iObjs == 0)
	{
		return;
	}

	fputs("\n\t/* call initialize routine*/\n", fp);

	for ( i = 0; i < m_iObjs; i++ )
	{
		fprintf(
			fp,
			"\t((FP)(%s))((VP_INT)(%s));\n",
			m_pParamPacks[i]->GetParam(ATTINI_INIRTN),
			m_pParamPacks[i]->GetParam(ATTINI_EXINF)
			);
	}
}


// ===========================================================================
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ===========================================================================
