// ---------------------------------------------------------------------------
//  HOS-V4 ����ե�����졼����                                               
//    �ǡ����ɤ߹��ߥ��饹                                                    
//                                                                            
//                                      Copyright (C) 2002 by Ryuji Fuchikami 
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "defercd.h"
#include "read.h"


// ���󥹥ȥ饯��
CRead::CRead(FILE *fp)
{
	m_fpRead    = fp;
	m_iLineNum  = 1;
	m_blLineTop = true;
}


// �ǥ��ȥ饯��
CRead::~CRead()
{
}


// �����ơ����ɤ߹���
int CRead::ReadState(char *szState)
{
	bool blEsc   = false;
	bool blSpace = true;	// true �ǻϤ����Ƭ�ζ�����ɤ����Ф�
	int  iCount = 0;
	int  iErr;
	int  c;

	for ( ; ; )
	{
		// ��ʸ���ɤ߹���
		if ( (c = fgetc(m_fpRead)) == EOF )
		{
			if ( blEsc || iCount != 0 )
			{
				iErr = CFG_ERR_EOF;	// ͽ������EOF
			}
			else
			{
				iErr = CFG_ERR_COMPLETE;	// ��λ
			}
			break;
		}

		// �����������å�
		if ( iCount >= READ_MAX_STATE - 1 )
		{
			iErr = CFG_ERR_STATE_LEN;
			break;
		}

		// ��Ƭ�� # �ʤ饹���å�
		if ( m_blLineTop && c == '#' )
		{
			iErr = SkipPriProcessorLine();
			if ( iErr != CFG_ERR_OK )
			{
				break;
			}
			continue;
		}

		// ����ʸ���ν���
		if ( c == '\n' )
		{
			m_iLineNum++;
			m_blLineTop = true;
		}

		// ����ʸ���Υ����å�
		if ( isspace(c) || c == '\n' )
		{
			if ( !blSpace )
			{
				szState[iCount++] = ' ';
				blSpace = true;
			}
			continue;
		}
		blSpace = false;

		// ʸ����ν���
		if ( c == '\"' || c == '\'' )
		{
			szState[iCount++] = c;
			iErr = ReadString(c, szState, iCount);
			if ( iErr != CFG_ERR_OK )
			{
				break;
			}
			continue;
		}

		// ���ơ��ȴ�λʸ���ʤ�
		if ( c == ';' )
		{
			iErr = CFG_ERR_OK;
			break;
		}

		// ʸ�����ɤ߹���
		szState[iCount++] = c;
	}

	// �����ζ���ʸ�����
	if ( iCount > 0 && szState[iCount - 1] == ' ' )
	{
		iCount--;
	}

	szState[iCount] = '\0';

	return iErr;
}


// �ץ�ץ��å��饤��Υ����å�
int CRead::SkipPriProcessorLine(void)
{
	bool blEsc  = false;
	int  c;

	for ( ; ; )
	{
		// ��ʸ���ɤ߹���
		if ( (c = fgetc(m_fpRead)) == EOF )
		{
			if ( blEsc )
			{
				return CFG_ERR_EOF;	// ͽ������EOF
			}
			return CFG_ERR_OK;
		}

		// \ �μ���̵���˥����å�
		if ( blEsc )
		{
			blEsc  = false;
			continue;
		}
		blEsc  = false;

		// \ �Υ����å�
		if ( c == '\\' )
		{
			blEsc  = true;
			continue;
		}

		// �����Υ����å�
		if ( c == '\n' )
		{
			m_iLineNum++;
			return CFG_ERR_OK;
		}
	}
}


// ʸ�����ɤ߹���
int CRead::ReadString(int cDelimiter, char* szText, int& iCount)
{
	bool blEsc  = false;
	int c;

	for ( ; ; )
	{
		// ��ʸ���ɤ߹���
		if ( (c = fgetc(m_fpRead)) == EOF )
		{
			return CFG_ERR_EOF;	// ͽ������EOF
		}

		// �����������å�
		if ( iCount >= READ_MAX_STATE - 1 )
		{
			return CFG_ERR_STATE_LEN;
		}

		// ���ԥ����å�
		if ( c == '\n' )
		{
			return CFG_ERR_CR;		// �����ʲ���
		}

		// ʸ��������
		szText[iCount++] = c;

		// \ �μ���̵���˥����å�
		if ( blEsc )
		{
			blEsc  = false;
			continue;
		}

		// \ �Υ����å�
		if ( c == '\\' )
		{
			blEsc  = true;
			continue;
		}

		blEsc  = false;

		// �ǥ�ߥ�ʸ���ʤ鴰λ
		if ( c == cDelimiter )
		{
			return CFG_ERR_OK;
		}
	}
}


// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------
