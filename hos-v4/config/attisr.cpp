// ===========================================================================
//  HOS-V4 コンフィギュレーター
//    ATT_ISR API の処理
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ===========================================================================


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "attisr.h"
#include "analize.h"


#define ATTISR_ISRATR		0
#define ATTISR_EXINF		1
#define ATTISR_INTNO		2
#define ATTISR_ISR			3


// コンストラクタ
CApiAttIsr::CApiAttIsr()
{
	// パラメーター構文設定
	m_iParamSyntax[0] = 4;		// 4つのパラメーターブロック
	m_iParams = 1;
}

// デストラクタ
CApiAttIsr::~CApiAttIsr()
{
}

// API名取得
char* CApiAttIsr::GetApiName(void)
{
	return "ATT_ISR";
}


// 自動ID番号割り当て
int CApiAttIsr::AutoId(void)
{
	return CFG_ERR_OK;
}


// cfgファイル初期化部書き出し
void  CApiAttIsr::WriteCfgIni(FILE* fp)
{
	int i;

	// オブジェクト存在チェック
	if ( m_iObjs == 0 )
	{
		return;
	}

	// コメント出力
	fputs("\n\t/* initialize interrupt table */\n", fp);
	
	// 初期化部出力
	for ( i = 0; i < m_iObjs; i++ )
	{
		fprintf(
			fp,
			"\tkernel_intcb_tbl[%s].exinf = (VP_INT)(%s);\n"
			"\tkernel_intcb_tbl[%s].isr   = (FP)(%s);\n",
			m_pParamPacks[i]->GetParam(ATTISR_INTNO),
			m_pParamPacks[i]->GetParam(ATTISR_EXINF),
			m_pParamPacks[i]->GetParam(ATTISR_INTNO),
			m_pParamPacks[i]->GetParam(ATTISR_ISR));
	}
}



// ===========================================================================
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ===========================================================================
