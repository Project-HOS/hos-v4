// ---------------------------------------------------------------------------
//  Hyper Operating System V4  コンフィギュレーター                           
//    CRE_TSK API の処理                                                      
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "cretsk.h"
#include "analyze.h"


#define CRETSK_TSKID		0
#define CRETSK_TSKATR		1
#define CRETSK_EXINF		2
#define CRETSK_TASK			3
#define CRETSK_ITSKPRI		4
#define CRETSK_STKSZ		5
#define CRETSK_STK			6



// コンストラクタ
CApiCreTsk::CApiCreTsk()
{
	// パラメーター構文設定
	m_iParamSyntax[0] = 0;		// 単独パラメーター
	m_iParamSyntax[1] = 6;		// 6パラメーターのブロック
	m_iParams = 2;
}

// デストラクタ
CApiCreTsk::~CApiCreTsk()
{
}



// APIの解析
int CApiCreTsk::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	static bool blExMid = false;

	if ( strcmp(pszApiName, "CRE_TSK") == 0 )
	{
		return AddParams(pszParams);
	}
	else if ( strcmp(pszApiName, "HOS_MAX_TSKID") == 0 )
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
void CApiCreTsk::WriteId(FILE* fp)
{
	int i;

	// ID 直接指定でないオブジェクトが在るかどうかサーチ
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( atoi(m_pParamPacks[i]->GetParam(CRETSK_TSKID)) == 0 )
		{
			break;
		}
	}
	if ( i == m_iObjs )
	{
		return;
	}

	fputs("\n\n/* task ID definetion */\n", fp);
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( atoi(m_pParamPacks[i]->GetParam(CRETSK_TSKID)) == 0 )
		{
			fprintf(
				fp,
				"#define %s\t\t%d\n",
				m_pParamPacks[i]->GetParam(CRETSK_TSKID),
				m_iId[i]);
		}
	}

	fprintf( fp,"\n#define TMAX_TSKID\t\t%d\n", m_iMaxId );
}


// cfgファイル定義部書き出し
void  CApiCreTsk::WriteCfgDef(FILE* fp)
{
	const char* pszParam;
	bool blOutput;
	int  i, j;

	// コメント出力
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*          create task objects               */\n"
		"/* ------------------------------------------ */\n"
		, fp);

	// スタック領域出力
	blOutput = false;
	for ( i = 0; i < m_iObjs; i++ )
	{
		pszParam = m_pParamPacks[i]->GetParam(CRETSK_STK);
		if ( strcmp(pszParam, "NULL") == 0 )
		{
			if ( !blOutput )
			{
				fputs("\n/* stack area */\n", fp);
				blOutput = true;
			}

			fprintf(
				fp,
				"static VP kernel_tsk%d_stk[((%s) + sizeof(VP) - 1) / sizeof(VP)];\n",
				m_iId[i],
				m_pParamPacks[i]->GetParam(CRETSK_STKSZ));
		}
	}

	if ( m_iObjs > 0 )
	{
		fprintf(
			fp,
			"\n/* task control block for rom area */\n"
			"const T_KERNEL_TCB_ROM kernel_tcb_rom[%d] =\n"
			"\t{\n",
			m_iObjs);

		// タスクコントロールブロック(ROM部)出力
		for ( i = 0; i < m_iObjs; i++ )
		{
			fprintf(
				fp,
				"\t\t{(ATR)(%s), (VP_INT)(%s), (FP)(%s), (PRI)(%s), (SIZE)(%s), ",
				m_pParamPacks[i]->GetParam(CRETSK_TSKATR),
				m_pParamPacks[i]->GetParam(CRETSK_EXINF),
				m_pParamPacks[i]->GetParam(CRETSK_TASK),
				m_pParamPacks[i]->GetParam(CRETSK_ITSKPRI),
				m_pParamPacks[i]->GetParam(CRETSK_STKSZ));

			pszParam = m_pParamPacks[i]->GetParam(CRETSK_STK);
			if ( strcmp(pszParam, "NULL") == 0 )
			{
				fprintf(
					fp,
					"(VP)kernel_tsk%d_stk},\n",
					m_iId[i]);
			}
			else
			{
				fprintf(
					fp,
					"(VP)(%s)},\n",
					m_pParamPacks[i]->GetParam(CRETSK_STK));
			}
		}
		fprintf(fp, "\t};\n");
	}

	// タスクコントロールブロック(RAM部)出力
	if ( m_iObjs > 0 )
	{
		fprintf(
			fp,
			"\n/* task control block for ram area */\n"
			"T_KERNEL_TCB_RAM kernel_tcb_ram[%d];\n",
			m_iObjs);
	}

	// タスクコントロールブロックテーブル出力
	if ( m_iMaxId > 0 )
	{
		fprintf(
			fp,
			"\n/* task control block table */\n"
			"T_KERNEL_TCB_RAM *kernel_tcb_ram_tbl[%d] =\n"
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
				fprintf(fp, "\t\t&kernel_tcb_ram[%d],\n", j);
			}
			else
			{
				// オブジェクトが無い場合
				fputs("\t\tNULL,\n", fp);
			}
		}
		fputs("\t};\n", fp);
	}

	// タスク情報出力
	fprintf(
		fp,
		"\n/* task control block count */\n"
		"const INT kernel_tcb_cnt = %d;\n",
		m_iMaxId);
}


// cfgファイル初期化部書き出し
void  CApiCreTsk::WriteCfgIni(FILE* fp)
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
		"\t/* initialize task control block */\n"
		"\tfor ( i = 0; i < %d; i++ )\n"
		"\t{\n"
		"\t\tkernel_tcb_ram[i].tcb_rom = &kernel_tcb_rom[i];\n"
		"\t}\n",
		m_iObjs);
}


// cfgファイル起動部書き出し
void  CApiCreTsk::WriteCfgStart(FILE* fp)
{
	// オブジェクト存在チェック
	if ( m_iObjs == 0 )
	{
		return;
	}

	fputs("\tkernel_ini_tsk();\t\t/* initialize task */\n", fp);
}


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
