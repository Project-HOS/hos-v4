// ---------------------------------------------------------------------------
//  Hyper Operating System V4  ����ե�����졼����
//    CRE_MPL API �ν���
//                                                                            
//                                    Copyright (C) 1998-2003 by Project HOS  
//                                    http://sourceforge.jp/projects/hos/     
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "crempl.h"
#include "analyze.h"


#define CREMPL_MPLID		0
#define CREMPL_MPLATR		1
#define CREMPL_MPLSZ		2
#define CREMPL_MPL			3


// ���󥹥ȥ饯��
CApiCreMpl::CApiCreMpl()
{
	// �ѥ�᡼������ʸ����
	m_iParamSyntax[0] = 0;		// ñ�ȥѥ�᡼����
	m_iParamSyntax[1] = 3;		// 4�ѥ�᡼�����Υ֥�å�
	m_iParams = 2;
}

// �ǥ��ȥ饯��
CApiCreMpl::~CApiCreMpl()
{
}



// API�β���
int CApiCreMpl::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	if ( strcmp(pszApiName, "CRE_MPL") == 0 )
	{
		return AddParams(pszParams);
	}
	else if ( strcmp(pszApiName, "HOS_MAX_MPLID") == 0 )
	{
		int iId;

		if ( m_iMaxId > 0 )
		{
			return CFG_ERR_MULTIDEF;
		}

		if ( m_iResObj > 0 )
		{
			return CFG_ERR_DEF_CONFLICT;
		}

		if ( (iId = atoi(pszParams)) <= 0 )
		{
			return CFG_ERR_PARAM;
		}

		m_iMaxId = iId;

		return CFG_ERR_OK;
	}
	else if ( strcmp(pszApiName, "HOS_RES_MPLOBJ") == 0 )
	{
		int iId;

                if ( m_iMaxId > 0 )
		{
                        return CFG_ERR_DEF_CONFLICT;
		}

                if ( (iId = atoi(pszParams)) <= 0 )
		{
                        return CFG_ERR_PARAM;
		}

                m_iResObj += iId;

                return CFG_ERR_OK;
        }

	return CFG_ERR_NOPROC;
}


// ID ����ե�����񤭽Ф�
void CApiCreMpl::WriteId(FILE* fp)
{
	int i;

	// ID ľ�ܻ���Ǥʤ����֥������Ȥ��ߤ뤫�ɤ���������
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( atoi(m_pParamPacks[i]->GetParam(CREMPL_MPLID)) == 0 )
		{
			break;
		}
	}
	if ( i == m_iObjs )
	{
		return;
	}

	fputs("\n\n/* variable size memory-pool ID definetion */\n", fp);
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( atoi(m_pParamPacks[i]->GetParam(CREMPL_MPLID)) == 0 )
		{
			fprintf(
				fp,
				"#define %s\t\t%d\n",
				m_pParamPacks[i]->GetParam(CREMPL_MPLID),
				m_iId[i]);
		}
	}

	fprintf( fp,"\n#define TMAX_MPLID\t\t%d\n", m_iMaxId );
}


// cfg�ե�����������񤭽Ф�
void  CApiCreMpl::WriteCfgDef(FILE* fp)
{
	const char* pszParam;
	bool blOutput;
	int  i, j;

	// �����Ƚ���
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*  create variable size memory-pool objects  */\n"
		"/* ------------------------------------------ */\n"
		, fp);

	// ����֥�å��ΰ����
	blOutput = false;
	for ( i = 0; i < m_iObjs; i++ )
	{
		pszParam = m_pParamPacks[i]->GetParam(CREMPL_MPL);
		if ( strcmp(pszParam, "NULL") == 0 )
		{
			if ( !blOutput )
			{
				fputs("\n/* fixed size memory-pool area */\n", fp);
				blOutput = true;
			}

			fprintf(
				fp,
				"static VP kernel_mpl%d_heap[(((%s) + sizeof(VP) - 1) / sizeof(VP))];\n",
				m_iId[i],
				m_pParamPacks[i]->GetParam(CREMPL_MPLSZ));
		}
	}

	if ( m_iObjs > 0 )
	{
		fprintf(
			fp,
			"\n/* variable size memory-pool control block for rom area */\n"
			"const T_KERNEL_MPLCB_ROM kernel_mplcb_rom[%d] =\n"
			"\t{\n",
			m_iObjs);

		// ����ȥ���֥�å�(ROM��)����
		for ( i = 0; i < m_iObjs; i++ )
		{
			fprintf(
				fp,
				"\t\t{(ATR)(%s), ",
				m_pParamPacks[i]->GetParam(CREMPL_MPLATR));

			pszParam = m_pParamPacks[i]->GetParam(CREMPL_MPL);
			if ( strcmp(pszParam, "NULL") == 0 )
			{
				fprintf(
					fp,
					"(SIZE)sizeof(kernel_mpl%d_heap), (VP)kernel_mpl%d_heap},\n",
					m_iId[i],
					m_iId[i]);
			}
			else
			{
				fprintf(
					fp,
					"(SIZE)(%s), (VP)(%s)},\n",
					m_pParamPacks[i]->GetParam(CREMPL_MPLSZ),
					m_pParamPacks[i]->GetParam(CREMPL_MPL));
			}

		}
		fprintf(fp, "\t};\n");
	}

	// ����ȥ���֥�å�(RAM��)����
	if ( m_iObjs > 0 )
	{
		fprintf(
			fp,
			"\n/* variable size memory-pool control block for ram area */\n"
			"T_KERNEL_MPLCB_RAM kernel_mplcb_ram[%d];\n",
			m_iObjs);
	}

	// ����ȥ���֥�å��ơ��֥����
	if ( m_iMaxId > 0 )
	{
		fprintf(
			fp,
			"\n/* variable size memory-pool control block table */\n"
			"T_KERNEL_MPLCB_RAM *kernel_mplcb_ram_tbl[%d] =\n"
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
				fprintf(fp, "\t\t&kernel_mplcb_ram[%d],\n", j);
			}
			else
			{
				// ���֥������Ȥ�̵�����
				fputs("\t\tNULL,\n", fp);
			}
		}
		fputs("\t};\n", fp);
	}

	// �Ŀ��������
	fprintf(
		fp,
		"\n/* variable size memory-pool control block count */\n"
		"const INT kernel_mplcb_cnt = %d;\n",
		m_iMaxId);
}


// cfg�ե������������񤭽Ф�
void  CApiCreMpl::WriteCfgIni(FILE* fp)
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
		"\t/* initialize variable size memory-pool control block */\n"
		"\tfor ( i = 0; i < %d; i++ )\n"
		"\t{\n"
		"\t\tkernel_mplcb_ram[i].mplcb_rom = &kernel_mplcb_rom[i];\n"
		"\t}\n",
		m_iObjs);
}


// cfg�ե����뵯ư���񤭽Ф�
void  CApiCreMpl::WriteCfgStart(FILE* fp)
{
	// ���֥�������¸�ߥ����å�
	if ( m_iObjs == 0 )
	{
		return;
	}

	fputs("\tkernel_ini_mpl();\t\t/* initialize variable size memory-pool */\n", fp);
}


// ---------------------------------------------------------------------------
//  Copyright (C) 1998-2006 by Project HOS                                    
// ---------------------------------------------------------------------------
