// ---------------------------------------------------------------------------
//  Hyper Operating System V4  コンフィギュレーター                           
//    CRE_SEM API の処理                                                      
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "cresem.h"
#include "analyze.h"


#define CRESEM_SEMID		0
#define CRESEM_SEMATR		1
#define CRESEM_SEMCNT		2
#define CRESEM_MAXSEM		3



// コンストラクタ
CApiCreSem::CApiCreSem()
{
	// パラメーター構文設定
	m_iParamSyntax[0] = 0;		// 単独パラメーター
	m_iParamSyntax[1] = 3;		// 3パラメーターのブロック
	m_iParams = 2;
}

// デストラクタ
CApiCreSem::~CApiCreSem()
{
}


// APIの解析
int CApiCreSem::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	static bool blExMid = false;

	if ( strcmp(pszApiName, "CRE_SEM") == 0 )
	{
		return AddParams(pszParams);
	}
	else if ( strcmp(pszApiName, "HOS_MAX_SEMID") == 0 )
	{
		int iId;

		if ( blExMid == true )
		{
			return CFG_ERR_MULTIDEF;
		}

		blExMid = true;

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
void CApiCreSem::WriteId(FILE* fp)
{
	int i;

	// ID 直接指定でないオブジェクトが在るかどうかサーチ
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( atoi(m_pParamPacks[i]->GetParam(CRESEM_SEMID)) == 0 )
		{
			break;
		}
	}
	if ( i == m_iObjs )
	{
		return;
	}

	fputs("\n\n/* semaphore ID definetion */\n", fp);
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( atoi(m_pParamPacks[i]->GetParam(CRESEM_SEMID)) == 0 )
		{
			fprintf(
				fp,
				"#define %s\t\t%d\n",
				m_pParamPacks[i]->GetParam(CRESEM_SEMID),
				m_iId[i]);
		}
	}
}


// cfgファイル定義部書き出し
void  CApiCreSem::WriteCfgDef(FILE* fp)
{
	int  i, j;

	// コメント出力
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*         create semaphore objects           */\n"
		"/* ------------------------------------------ */\n"
		, fp);

	if ( m_iObjs > 0 )
	{
		fprintf(
			fp,
			"\n/* semaphore control block for rom area */\n"
			"const T_KERNEL_SEMCB_ROM kernel_semcb_rom[%d] =\n"
			"\t{\n",
			m_iObjs);

		// コントロールブロック(ROM部)出力
		for ( i = 0; i < m_iObjs; i++ )
		{
			fprintf(
				fp,
				"\t\t{(ATR)(%s), (UINT)(%s), (UINT)(%s)},\n",
				m_pParamPacks[i]->GetParam(CRESEM_SEMATR),
				m_pParamPacks[i]->GetParam(CRESEM_SEMCNT),
				m_pParamPacks[i]->GetParam(CRESEM_MAXSEM));
		}
		fprintf(fp, "\t};\n");
	}

	// コントロールブロック(RAM部)出力
	if ( m_iObjs > 0 )
	{
		fprintf(
			fp,
			"\n/* semaphore control block for ram area */\n"
			"T_KERNEL_SEMCB_RAM kernel_semcb_ram[%d];\n",
			m_iObjs);
	}

	// コントロールブロックテーブル出力
	if ( m_iMaxId > 0 )
	{
		fprintf(
			fp,
			"\n/* semaphore control block table */\n"
			"T_KERNEL_SEMCB_RAM *kernel_semcb_ram_tbl[%d] =\n"
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
				fprintf(fp, "\t\t&kernel_semcb_ram[%d],\n", j);
			}
			else
			{
				// オブジェクトが無い場合
				fputs("\t\tNULL,\n", fp);
			}
		}
		fputs("\t};\n", fp);
	}

	// テーブルサイズ情報出力
	fprintf(
		fp,
		"\n/* semaphore control block count */\n"
		"const INT kernel_semcb_cnt = %d;\n",
		m_iMaxId);
}


// cfgファイル初期化部書き出し
void  CApiCreSem::WriteCfgIni(FILE* fp)
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
		"\t/* initialize semaphore control block */\n"
		"\tfor ( i = 0; i < %d; i++ )\n"
		"\t{\n"
		"\t\tkernel_semcb_ram[i].semcb_rom = &kernel_semcb_rom[i];\n"
		"\t}\n",
		m_iObjs);
}


// cfgファイル起動部書き出し
void  CApiCreSem::WriteCfgStart(FILE* fp)
{
	// オブジェクト存在チェック
	if ( m_iObjs == 0 )
	{
		return;
	}

	fputs("\tkernel_ini_sem();\t\t/* initialize semaphore */\n", fp);
}


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
