// ---------------------------------------------------------------------------
//  Hyper Operating System V4  コンフィギュレーター                           
//    HOS_INT_STK API の処理                                                  
//                                                                            
//                                    Copyright (C) 1998-2003 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "intstk.h"
#include "analyze.h"


#define INTSTK_STKSZ		0
#define INTSTK_STK			1


// コンストラクタ
CApiIntStack::CApiIntStack()
{
	// パラメーター構文設定
	m_iParamSyntax[0] = 0;		// 単独パラメーター
	m_iParams = 2;

	// スタックポインタ
	m_szStackPointer[0] = '\0';
}


// デストラクタ
CApiIntStack::~CApiIntStack()
{
}


// 自動ID番号割り当て
int CApiIntStack::AutoId(void)
{
	return CFG_ERR_OK;
}


// APIの解析
int CApiIntStack::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	if ( strcmp(pszApiName, "HOS_INT_STK") == 0 )
	{
		if ( m_iObjs > 0 )
		{
			return CFG_ERR_MULTIDEF;
		}

		if ( m_szStackPointer[0] != '\0' )
		{
			return CFG_ERR_DEF_CONFLICT;
		}

		return AddParams(pszParams);
	}
	else if ( strcmp(pszApiName, "HOS_INT_SP") == 0 )
	{
		if ( m_iObjs > 0 )
		{
			return CFG_ERR_DEF_CONFLICT;
		}

		if ( m_szStackPointer[0] != '\0' )
		{
			return CFG_ERR_MULTIDEF;
		}

		strcpy(m_szStackPointer, pszParams);
		return CFG_ERR_OK;
	}

	return CFG_ERR_NOPROC;
}


// cfgファイル定義部書き出し
void  CApiIntStack::WriteCfgDef(FILE* fp)
{
	const char* pszSize;
	const char* pszStack;

	// パラメータ読み出し
	if ( m_iObjs <= 0 && m_szStackPointer[0] == '\0' )
	{
		return ;
	}

	// コメント出力
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*             interrupt stack                */\n"
		"/* ------------------------------------------ */\n\n"
		, fp);

	// 割り込み用スタックポインタ出力
	if ( m_szStackPointer[0] != '\0' )
	{
		fprintf(
			fp,
			"const VP kernel_int_sp = (VP)(%s);\t/* interrupt stack pointer */\n",
			m_szStackPointer);
	}
	else
	{
		pszSize  = m_pParamPacks[0]->GetParam(INTSTK_STKSZ);
		pszStack = m_pParamPacks[0]->GetParam(INTSTK_STK);

		if ( strcmp(pszStack, "NULL") == 0 )
		{
			fprintf(
				fp,
				"VP         kernel_int_stkblk[((%s) + sizeof(VP) - 1) / sizeof(VP)];\t/* interrupt stack block*/\n"
				"const VP   kernel_int_sp  = &kernel_int_stkblk[sizeof(kernel_int_stkblk) / sizeof(VP)];\t/* interrupt stack pointer */\n",
				pszSize);
		}
		else
		{
			fprintf(
				fp,
				"const VP kernel_int_sp = (VP)((UB *)(%s) + (%s));\t/* interrupt stack pointer */\n",
				pszStack, pszSize);
		}
	}
}


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2003 by Project HOS                                    
// ---------------------------------------------------------------------------
