// ===========================================================================
//  HOS V4 ����ե�����졼����
//    ��ʸ���ϥ��饹
//
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================



#include <stdio.h>
#include <ctype.h>
#include "analize.h"



// '{'���б�����'}'�θ���
char* CAnalize::SearchBrace(char* pStr)
{
	int  iNest = 0;
	bool bQuotation = false;
	char c;

	while ( (c = *pStr) != '\0' )
	{
		if ( c == '\\' )	// ���������ץ������󥹤ʤ�
		{
			*pStr++;		// ����ʸ���򥹥��å�
			if ( *pStr == '\0' )
			{
				break;
			}
		}
		else if ( bQuotation )	// "" ����ʤ�
		{
			if ( c == '\"' )
			{
				bQuotation = false;
			}
		}
		else if ( c == '\"' )
		{
			bQuotation = true;
		}
		else if ( c == '{' )
		{
			iNest++;
		}
		if ( c == '}' && iNest == 0)
		{
			break;
		}

		pStr++;
	}

	if ( c != '}' )
	{
		return NULL;
	}

	return pStr;
}


// '('���б�����')'�θ���
char* CAnalize::SearchParentheses(char* pStr)
{
	int  iNest = 0;
	bool bQuotation = false;
	char c;

	while ( (c = *pStr) != '\0' )
	{
		if ( c == '\\' )	// ���������ץ������󥹤ʤ�
		{
			*pStr++;		// ����ʸ���򥹥��å�
			if ( *pStr == '\0' )
			{
				break;
			}
		}
		else if ( bQuotation )	// "" ����ʤ�
		{
			if ( c == '\"' )
			{
				bQuotation = false;
			}
		}
		else if ( c == '\"' )
		{
			bQuotation = true;
		}
		else if ( c == '(' )
		{
			iNest++;
		}
		if ( c == ')' && iNest == 0)
		{
			break;
		}

		pStr++;
	}

	if ( c != ')' )
	{
		return NULL;
	}

	return pStr;
}


// ����','�򸡺�
char* CAnalize::SearchComma(char* pStr)
{
	bool bQuotation = false;
	char c;

	while ( (c = *pStr) != '\0' )
	{
		if ( c == '\\' )	// ���������ץ������󥹤ʤ�
		{
			*pStr++;		// ����ʸ���򥹥��å�
			if ( *pStr == '\0' )
			{
				break;
			}
		}
		else if ( bQuotation )	// "" ����ʤ�
		{
			if ( c == '\"' )
			{
				bQuotation = false;
			}
		}
		else if ( c == '\"' )
		{
			bQuotation = true;
		}
		if ( c == ',' )
		{
			break;
		}

		pStr++;
	}

	return pStr;
}


// ����ʸ��������������
void CAnalize::NormalizerSpace(char* pStr)
{
	bool  bSpace = false;
	char* pSrc;
	char* pDes;
	char  c;

	pSrc = pStr;
	pDes = pStr;

	// ��Ƭ�ζ���ʸ���ɤ����Ф� */
	while ( isspace(*pSrc) )
	{
		pSrc++;
	}

	while ( (c = *pSrc) != '\0' )
	{
		if ( isspace(c) )
		{
			if ( !bSpace )
			{
				*pDes++ = ' ';
				bSpace = true;
			}
		}
		else
		{
			*pDes++ = c;
			bSpace = false;
		}

		pSrc++;
	}

	*pDes = '\0';

	// �Ǹ����ζ���ʸ�����
	if ( pDes != pStr && *(pDes - 1) == ' ' )
	{
		*(pDes - 1) = '\0';
	}
}


// ===========================================================================
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================
