// ---------------------------------------------------------------------------
//  Hyper Operating System V4  ����ե�����졼����                           
//    CRE_DTQ API �ν���                                                      
//                                                                            
//                                    Copyright (C) 1998-2002 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "credtq.h"
#include "analyze.h"



#define CREDTQ_DTQID		0
#define CREDTQ_DTQATR		1
#define CREDTQ_DTQCNT		2
#define CREDTQ_DTQ			3



// ���󥹥ȥ饯��
CApiCreDtq::CApiCreDtq()
{
	// �ѥ�᡼������ʸ����
	m_iParamSyntax[0] = 0;		// ñ�ȥѥ�᡼����
	m_iParamSyntax[1] = 3;		// 3�ѥ�᡼�����Υ֥�å�
	m_iParams = 2;
}

// �ǥ��ȥ饯��
CApiCreDtq::~CApiCreDtq()
{
}


// API�β���
int CApiCreDtq::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	if ( strcmp(pszApiName, "CRE_DTQ") == 0 )
	{
		return AddParams(pszParams);
	}
	else if ( strcmp(pszApiName, "HOS_MAX_DTQID") == 0 )
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


// ID ����ե�����񤭽Ф�
void CApiCreDtq::WriteId(FILE* fp)
{
	int i;

	// ID ľ�ܻ���Ǥʤ����֥������Ȥ��ߤ뤫�ɤ���������
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( atoi(m_pParamPacks[i]->GetParam(CREDTQ_DTQID)) == 0 )
		{
			break;
		}
	}
	if ( i == m_iObjs )
	{
		return;
	}

	fputs("\n\n/* data queue ID definetion */\n", fp);
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( atoi(m_pParamPacks[i]->GetParam(CREDTQ_DTQID)) == 0 )
		{
			fprintf(
				fp,
				"#define %s\t\t%d\n",
				m_pParamPacks[i]->GetParam(CREDTQ_DTQID),
				m_iId[i]);
		}
	}
}


// cfg�ե�����������񤭽Ф�
void  CApiCreDtq::WriteCfgDef(FILE* fp)
{
	const char* pszParam;
	bool blOutput;
	int  i, j;

	// �����Ƚ���
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*        create data queue objects           */\n"
		"/* ------------------------------------------ */\n"
		, fp);

	// �ǡ������塼�ΰ����
	blOutput = false;
	for ( i = 0; i < m_iObjs; i++ )
	{
		pszParam = m_pParamPacks[i]->GetParam(CREDTQ_DTQ);
		if ( strcmp(pszParam, "NULL") == 0 )
		{
			if ( !blOutput )
			{
				fputs("\n/* data que area */\n", fp);
				blOutput = true;
			}

			fprintf(
				fp,
				"static VP_INT kernel_dtq%d_dtq[%s];\n",
				m_iId[i],
				m_pParamPacks[i]->GetParam(CREDTQ_DTQCNT));
		}
	}

	if ( m_iObjs > 0 )
	{
		fprintf(
			fp,
			"\n/* data queue control block for rom area */\n"
			"const T_KERNEL_DTQCB_ROM kernel_dtqcb_rom[%d] =\n"
			"\t{\n",
			m_iObjs);

		// ����ȥ���֥�å�(ROM��)����
		for ( i = 0; i < m_iObjs; i++ )
		{
			fprintf(
				fp,
				"\t\t{(ATR)(%s), (FLGPTN)(%s), ",
				m_pParamPacks[i]->GetParam(CREDTQ_DTQATR),
				m_pParamPacks[i]->GetParam(CREDTQ_DTQCNT));
			pszParam = m_pParamPacks[i]->GetParam(CREDTQ_DTQ);
			if ( strcmp(pszParam, "NULL") == 0 )
			{
				fprintf(fp,	"kernel_dtq%d_dtq},\n", m_iId[i]);
			}
			else
			{
				fprintf(fp,	"(VP_INT *)(%s)},\n", pszParam);
			}
		}
		fprintf(fp, "\t};\n");
	}

	// ����ȥ���֥�å�(RAM��)����
	if ( m_iObjs > 0 )
	{
		fprintf(
			fp,
			"\n/* data queue control block for ram area */\n"
			"T_KERNEL_DTQCB_RAM kernel_dtqcb_ram[%d];\n",
			m_iObjs);
	}

	// ����ȥ���֥�å��ơ��֥����
	if ( m_iMaxId > 0 )
	{
		fprintf(
			fp,
			"\n/* data queue control block table */\n"
			"T_KERNEL_DTQCB_RAM *kernel_dtqcb_ram_tbl[%d] =\n"
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
				fprintf(fp, "\t\t&kernel_dtqcb_ram[%d],\n", j);
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
		"\n/* data queue control block count */\n"
		"const INT kernel_dtqcb_cnt = %d;\n",
		m_iMaxId);
}


// cfg�ե������������񤭽Ф�
void  CApiCreDtq::WriteCfgIni(FILE* fp)
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
		"\t/* initialize data queue control block */\n"
		"\tfor ( i = 0; i < %d; i++ )\n"
		"\t{\n"
		"\t\tkernel_dtqcb_ram[i].dtqcb_rom = &kernel_dtqcb_rom[i];\n"
		"\t}\n",
		m_iObjs);
}


// cfg�ե����뵯ư���񤭽Ф�
void  CApiCreDtq::WriteCfgStart(FILE* fp)
{
	// ���֥�������¸�ߥ����å�
	if ( m_iObjs == 0 )
	{
		return;
	}

	fputs("\tkernel_ini_dtq();\t\t/* initialize data queue */\n", fp);
}


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2002 by Project HOS                                    
// ---------------------------------------------------------------------------
