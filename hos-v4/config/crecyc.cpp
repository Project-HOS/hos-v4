// ---------------------------------------------------------------------------
//  Hyper Operating System V4  ����ե�����졼����                           
//    CRE_CYC API �ν���                                                      
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "crecyc.h"
#include "analyze.h"



#define CRECYC_CYCID		0
#define CRECYC_CYCATR		1
#define CRECYC_EXINF		2
#define CRECYC_CYCHDR		3
#define CRECYC_CYCTIM		4
#define CRECYC_CYCPHS		5



// ���󥹥ȥ饯��
CApiCreCyc::CApiCreCyc()
{
	// �ѥ�᡼������ʸ����
	m_iParamSyntax[0] = 0;		// ñ�ȥѥ�᡼����
	m_iParamSyntax[1] = 5;		// 5�ѥ�᡼�����Υ֥�å�
	m_iParams = 2;
}

// �ǥ��ȥ饯��
CApiCreCyc::~CApiCreCyc()
{
}


// API�β���
int CApiCreCyc::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	static bool blExMid = false;

	if ( strcmp(pszApiName, "CRE_CYC") == 0 )
	{
		return AddParams(pszParams);
	}
	else if ( strcmp(pszApiName, "HOS_MAX_CYCID") == 0 )
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


// ID ����ե�����񤭽Ф�
void CApiCreCyc::WriteId(FILE* fp)
{
	int i;

	// ID ľ�ܻ���Ǥʤ����֥������Ȥ��ߤ뤫�ɤ���������
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( atoi(m_pParamPacks[i]->GetParam(CRECYC_CYCID)) == 0 )
		{
			break;
		}
	}
	if ( i == m_iObjs )
	{
		return;
	}

	fputs("\n\n/* cyclic handler ID definetion */\n", fp);
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( atoi(m_pParamPacks[i]->GetParam(CRECYC_CYCID)) == 0 )
		{
			fprintf(
				fp,
				"#define %s\t\t%d\n",
				m_pParamPacks[i]->GetParam(CRECYC_CYCID),
				m_iId[i]);
		}
	}
}


// cfg�ե�����������񤭽Ф�
void  CApiCreCyc::WriteCfgDef(FILE* fp)
{
	int  i, j;

	// �����Ƚ���
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*       create cyclic handler objects        */\n"
		"/* ------------------------------------------ */\n"
		, fp);

	if ( m_iObjs > 0 )
	{
		fprintf(
			fp,
			"\n/* cyclic handler control block for rom area */\n"
			"const T_KERNEL_CYCCB_ROM kernel_cyccb_rom[%d] =\n"
			"\t{\n",
			m_iObjs);

		// ����ȥ���֥�å�(ROM��)����
		for ( i = 0; i < m_iObjs; i++ )
		{
			fprintf(
				fp,
				"\t\t{(ATR)(%s), (VP_INT)(%s), (FP)(%s), (RELTIM)(%s)},\n",
				m_pParamPacks[i]->GetParam(CRECYC_CYCATR),
				m_pParamPacks[i]->GetParam(CRECYC_EXINF),
				m_pParamPacks[i]->GetParam(CRECYC_CYCHDR),
				m_pParamPacks[i]->GetParam(CRECYC_CYCTIM));
		}
		fprintf(fp, "\t};\n");
	}

	// ����ȥ���֥�å�(RAM��)����
	if ( m_iObjs > 0 )
	{
		fprintf(
			fp,
			"\n/* cyclic handler control block for ram area */\n"
			"T_KERNEL_CYCCB_RAM kernel_cyccb_ram[%d];\n",
			m_iObjs);
	}

	// ����ȥ���֥�å��ơ��֥����
	if ( m_iMaxId > 0 )
	{
		fprintf(
			fp,
			"\n/* cyclic handler control block table */\n"
			"T_KERNEL_CYCCB_RAM *kernel_cyccb_ram_tbl[%d] =\n"
			"\t{\n",
			m_iMaxId);

		for ( i = 0; i < m_iMaxId; i++ )
		{
			// ID����
			for ( j = 0; j < m_iObjs; j++ )
			{
				if ( m_iId[j] == i + 1 )
				{
					break;
				}
			}
			if ( j < m_iObjs )
			{
				// ���֥������Ȥ�¸�ߤ������
				fprintf(fp, "\t\t&kernel_cyccb_ram[%d],\n", j);
			}
			else
			{
				// ���֥������Ȥ�̵�����
				fputs("\t\tNULL,\n", fp);
			}
		}
		fputs("\t};\n", fp);
	}

	// �ơ��֥륵�����������
	fprintf(
		fp,
		"\n/* cyclic handler control block count */\n"
		"const INT kernel_cyccb_cnt = %d;\n",
		m_iMaxId);
}


// cfg�ե������������񤭽Ф�
void  CApiCreCyc::WriteCfgIni(FILE* fp)
{
	// ���֥�������¸�ߥ����å�
	if ( m_iObjs == 0 )
	{
		return;
	}

	// �����������
	fprintf(
		fp,
		"\t\n\t\n"
		"\t/* initialize cyclic handler control block */\n"
		"\tfor ( i = 0; i < %d; i++ )\n"
		"\t{\n"
		"\t\tkernel_cyccb_ram[i].cyccb_rom = &kernel_cyccb_rom[i];\n"
		"\t}\n",
		m_iObjs);
}


// cfg�ե����뵯ư���񤭽Ф�
void  CApiCreCyc::WriteCfgStart(FILE* fp)
{
	// ���֥�������¸�ߥ����å�
	if ( m_iObjs == 0 )
	{
		return;
	}

	fputs("\tkernel_ini_cyc();\t\t/* initialize cyclic handler */\n", fp);
}


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
