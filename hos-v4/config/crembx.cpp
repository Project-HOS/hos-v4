// ---------------------------------------------------------------------------
//  Hyper Operating System V4  コンフィギュレーター                           
//    CRE_MBX API の処理                                                      
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "crembx.h"
#include "analyze.h"


#define CREMBX_MBXID		0
#define CREMBX_MBXATR		1
#define CREMBX_MAXPRI		2
#define CREMBX_MPRIHD		3



// コンストラクタ
CApiCreMbx::CApiCreMbx()
{
	// パラメーター構文設定
	m_iParamSyntax[0] = 0;		// 単独パラメーター
	m_iParamSyntax[1] = 3;		// 3パラメーターのブロック
	m_iParams = 2;
}

// デストラクタ
CApiCreMbx::~CApiCreMbx()
{
}



// APIの解析
int CApiCreMbx::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	if ( strcmp(pszApiName, "CRE_MBX") == 0 )
	{
		return AddParams(pszParams);
	}
	else if ( strcmp(pszApiName, "HOS_MAX_MBXID") == 0 )
	{
		int iId;
		if ( (iId = atoi(pszParams)) <= 0 )
		{
			return CFG_ERR_PARAM;
		}
		if ( iId > m_iMaxId )
		{
			m_iMaxId = iId;
		}
		return CFG_ERR_OK;
	}

	return CFG_ERR_NOPROC;
}


// ID 定義ファイル書き出し
void CApiCreMbx::WriteId(FILE* fp)
{
	int i;

	// ID 直接指定でないオブジェクトが在るかどうかサーチ
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( atoi(m_pParamPacks[i]->GetParam(CREMBX_MBXID)) == 0 )
		{
			break;
		}
	}
	if ( i == m_iObjs )
	{
		return;
	}

	fputs("\n\n/* mail box ID definetion */\n", fp);
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( atoi(m_pParamPacks[i]->GetParam(CREMBX_MBXID)) == 0 )
		{
			fprintf(
				fp,
				"#define %s\t\t%d\n",
				m_pParamPacks[i]->GetParam(CREMBX_MBXID),
				m_iId[i]);
		}
	}
}


// cfgファイル定義部書き出し
void  CApiCreMbx::WriteCfgDef(FILE* fp)
{
	const char* pszParam;
	bool blOutput;
	int  i, j;

	// コメント出力
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*         create mail box objects            */\n"
		"/* ------------------------------------------ */\n"
		, fp);

	// 優先度別のメッセージキューヘッダの領域
	blOutput = false;
	for ( i = 0; i < m_iObjs; i++ )
	{
		pszParam = m_pParamPacks[i]->GetParam(CREMBX_MPRIHD);
		if ( strcmp(pszParam, "NULL") == 0 )
		{
			if ( !blOutput )
			{
				fputs("\n/* message priority que header area */\n", fp);
				blOutput = true;
			}

			fprintf(
				fp,
				"static UB kernel_mbx%d_mprihd[TSZ_MPRIHD(%s)];\n",
				m_iId[i],
				m_pParamPacks[i]->GetParam(CREMBX_MAXPRI));
		}
	}

	if ( m_iObjs > 0 )
	{
		fprintf(
			fp,
			"\n/* mail box control block for rom area */\n"
			"const T_KERNEL_MBXCB_ROM kernel_mbxcb_rom[%d] =\n"
			"\t{\n",
			m_iObjs);

		// コントロールブロック(ROM部)出力
		for ( i = 0; i < m_iObjs; i++ )
		{
			fprintf(
				fp,
				"\t\t{(ATR)(%s), (PRI)(%s), ",
				m_pParamPacks[i]->GetParam(CREMBX_MBXATR),
				m_pParamPacks[i]->GetParam(CREMBX_MAXPRI));
			
			pszParam = m_pParamPacks[i]->GetParam(CREMBX_MPRIHD);
			if ( strcmp(pszParam, "NULL") == 0 )
			{
				fprintf(
					fp,
					"(VP)kernel_mbx%d_mprihd},\n",
					m_iId[i]);
			}
			else
			{
				fprintf(
					fp,
					"(VP)(%s)},\n",
					m_pParamPacks[i]->GetParam(CREMBX_MAXPRI));
			}

		}
		fprintf(fp, "\t};\n");
	}

	// コントロールブロック(RAM部)出力
	if ( m_iObjs > 0 )
	{
		fprintf(
			fp,
			"\n/* mail box control block for ram area */\n"
			"T_KERNEL_MBXCB_RAM kernel_mbxcb_ram[%d];\n",
			m_iObjs);
	}

	// コントロールブロックテーブル出力
	if ( m_iMaxId > 0 )
	{
		fprintf(
			fp,
			"\n/* mail box control block table */\n"
			"T_KERNEL_MBXCB_RAM *kernel_mbxcb_ram_tbl[%d] =\n"
			"\t{\n",
			m_iMaxId);

		for ( i = 0; i < m_iMaxId; i++ )
		{
			// ID検索
			for ( j = 0; j < m_iObjs; j++ )
			{
				if ( m_iId[j] == i + 1 )
				{
					break;
				}
			}
			if ( j < m_iObjs )
			{
				// オブジェクトが存在した場合
				fprintf(fp, "\t\t&kernel_mbxcb_ram[%d],\n", j);
			}
			else
			{
				// オブジェクトが無い場合
				fputs("\t\tNULL,\n", fp);
			}
		}
		fputs("\t};\n", fp);
	}

	// 個数情報出力
	fprintf(
		fp,
		"\n/* mail box control block count */\n"
		"const INT kernel_mbxcb_cnt = %d;\n",
		m_iMaxId);
}


// cfgファイル初期化部書き出し
void  CApiCreMbx::WriteCfgIni(FILE* fp)
{
	// オブジェクト存在チェック
	if ( m_iObjs == 0 )
	{
		return;
	}

	// 初期化部出力
	fprintf(
		fp,
		"\t\n\t\n"
		"\t/* initialize mail box control block */\n"
		"\tfor ( i = 0; i < %d; i++ )\n"
		"\t{\n"
		"\t\tkernel_mbxcb_ram[i].mbxcb_rom = &kernel_mbxcb_rom[i];\n"
		"\t}\n",
		m_iObjs);
}


// cfgファイル起動部書き出し
void  CApiCreMbx::WriteCfgStart(FILE* fp)
{
	// オブジェクト存在チェック
	if ( m_iObjs == 0 )
	{
		return;
	}

	fputs("\tkernel_ini_mbx();\t\t/* initialize mail box */\n", fp);
}


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
