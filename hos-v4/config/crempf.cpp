// ---------------------------------------------------------------------------
//  HOS-V4 ����ե�����졼����
//    CRE_MPF API �ν���
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defercd.h"
#include "crempf.h"
#include "analyze.h"


#define CREMPF_MPFID		0
#define CREMPF_MPFATR		1
#define CREMPF_BLKCNT		2
#define CREMPF_BLKSZ		3
#define CREMPF_MPF			4



// ���󥹥ȥ饯��
CApiCreMpf::CApiCreMpf()
{
	// �ѥ�᡼������ʸ����
	m_iParamSyntax[0] = 0;		// ñ�ȥѥ�᡼����
	m_iParamSyntax[1] = 4;		// 4�ѥ�᡼�����Υ֥�å�
	m_iParams = 2;
}

// �ǥ��ȥ饯��
CApiCreMpf::~CApiCreMpf()
{
}



// API�β���
int CApiCreMpf::AnalyzeApi(const char* pszApiName, const char* pszParams)
{
	if ( strcmp(pszApiName, "CRE_MPF") == 0 )
	{
		return AddParams(pszParams);
	}
	else if ( strcmp(pszApiName, "HOS_MAX_MPFID") == 0 )
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
void CApiCreMpf::WriteId(FILE* fp)
{
	int i;

	// ID ľ�ܻ���Ǥʤ����֥������Ȥ��ߤ뤫�ɤ���������
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( atoi(m_pParamPacks[i]->GetParam(CREMPF_MPFID)) == 0 )
		{
			break;
		}
	}
	if ( i == m_iObjs )
	{
		return;
	}

	fputs("\n\n/* fixed size memory-pool ID definetion */\n", fp);
	for ( i = 0; i < m_iObjs; i++ )
	{
		if ( atoi(m_pParamPacks[i]->GetParam(CREMPF_MPFID)) == 0 )
		{
			fprintf(
				fp,
				"#define %s\t\t%d\n",
				m_pParamPacks[i]->GetParam(CREMPF_MPFID),
				m_iId[i]);
		}
	}
}


// cfg�ե�����������񤭽Ф�
void  CApiCreMpf::WriteCfgDef(FILE* fp)
{
	const char* pszParam;
	bool blOutput;
	int  i, j;

	// �����Ƚ���
	fputs(
		"\n\n\n"
		"/* ------------------------------------------ */\n"
		"/*   create fixed size memory-pool objects    */\n"
		"/* ------------------------------------------ */\n"
		, fp);

	// ����֥�å��ΰ����
	blOutput = false;
	for ( i = 0; i < m_iObjs; i++ )
	{
		pszParam = m_pParamPacks[i]->GetParam(CREMPF_MPF);
		if ( strcmp(pszParam, "NULL") == 0 )
		{
			if ( !blOutput )
			{
				fputs("\n/* fixed size memory-pool area */\n", fp);
				blOutput = true;
			}

			fprintf(
				fp,
				"static VP kernel_mpf%d_heap[%s][(((%s) + sizeof(VP) - 1) / sizeof(VP))];\n",
				m_iId[i],
				m_pParamPacks[i]->GetParam(CREMPF_BLKCNT),
				m_pParamPacks[i]->GetParam(CREMPF_BLKSZ));
		}
	}

	if ( m_iObjs > 0 )
	{
		fprintf(
			fp,
			"\n/* fixed size memory-pool control block for rom area */\n"
			"const T_KERNEL_MPFCB_ROM kernel_mpfcb_rom[%d] =\n"
			"\t{\n",
			m_iObjs);

		// ����ȥ���֥�å�(ROM��)����
		for ( i = 0; i < m_iObjs; i++ )
		{
			fprintf(
				fp,
				"\t\t{(ATR)(%s), (UINT)(%s), ",
				m_pParamPacks[i]->GetParam(CREMPF_MPFATR),
				m_pParamPacks[i]->GetParam(CREMPF_BLKCNT));

			pszParam = m_pParamPacks[i]->GetParam(CREMPF_MPF);
			if ( strcmp(pszParam, "NULL") == 0 )
			{
				fprintf(
					fp,
					"(SIZE)sizeof(kernel_mpf%d_heap[0]), (VP)kernel_mpf%d_heap},\n",
					m_iId[i],
					m_iId[i]);
			}
			else
			{
				fprintf(
					fp,
					"(SIZE)(%s), (VP)(%s)},\n",
					m_pParamPacks[i]->GetParam(CREMPF_BLKSZ),
					m_pParamPacks[i]->GetParam(CREMPF_MPF));
			}

		}
		fprintf(fp, "\t};\n");
	}

	// ����ȥ���֥�å�(RAM��)����
	if ( m_iObjs > 0 )
	{
		fprintf(
			fp,
			"\n/* fixed size memory-pool control block for ram area */\n"
			"T_KERNEL_MPFCB_RAM kernel_mpfcb_ram[%d];\n",
			m_iObjs);
	}

	// ����ȥ���֥�å��ơ��֥����
	if ( m_iMaxId > 0 )
	{
		fprintf(
			fp,
			"\n/* fixed size memory-pool control block table */\n"
			"T_KERNEL_MPFCB_RAM *kernel_mpfcb_ram_tbl[%d] =\n"
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
				fprintf(fp, "\t\t&kernel_mpfcb_ram[%d],\n", j);
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
		"\n/* fixed size memory-pool control block count */\n"
		"const INT kernel_mpfcb_cnt = %d;\n",
		m_iMaxId);
}


// cfg�ե������������񤭽Ф�
void  CApiCreMpf::WriteCfgIni(FILE* fp)
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
		"\t/* initialize fixed size memory-pool control block */\n"
		"\tfor ( i = 0; i < %d; i++ )\n"
		"\t{\n"
		"\t\tkernel_mpfcb_ram[i].mpfcb_rom = &kernel_mpfcb_rom[i];\n"
		"\t}\n",
		m_iObjs);
}


// cfg�ե����뵯ư���񤭽Ф�
void  CApiCreMpf::WriteCfgStart(FILE* fp)
{
	// ���֥�������¸�ߥ����å�
	if ( m_iObjs == 0 )
	{
		return;
	}

	fputs("\tkernel_ini_mpf();\t\t/* initialize fixed size memory-pool */\n", fp);
}


// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------
