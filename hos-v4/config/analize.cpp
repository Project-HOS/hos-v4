// ===========================================================================
//  HOS V4 コンフィギュレーター
//    構文解析クラス
//
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================



#include <stdio.h>
#include <ctype.h>
#include "analize.h"



// '{'に対応する'}'の検索
char* CAnalize::SearchBrace(char* pStr)
{
	int  iNest = 0;
	bool bQuotation = false;
	char c;

	while ( (c = *pStr) != '\0' )
	{
		if ( c == '\\' )	// エスケープシーケンスなら
		{
			*pStr++;		// 次の文字をスキップ
			if ( *pStr == '\0' )
			{
				break;
			}
		}
		else if ( bQuotation )	// "" の中なら
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


// '('に対応する')'の検索
char* CAnalize::SearchParentheses(char* pStr)
{
	int  iNest = 0;
	bool bQuotation = false;
	char c;

	while ( (c = *pStr) != '\0' )
	{
		if ( c == '\\' )	// エスケープシーケンスなら
		{
			*pStr++;		// 次の文字をスキップ
			if ( *pStr == '\0' )
			{
				break;
			}
		}
		else if ( bQuotation )	// "" の中なら
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


// 次の','を検索
char* CAnalize::SearchComma(char* pStr)
{
	bool bQuotation = false;
	char c;

	while ( (c = *pStr) != '\0' )
	{
		if ( c == '\\' )	// エスケープシーケンスなら
		{
			*pStr++;		// 次の文字をスキップ
			if ( *pStr == '\0' )
			{
				break;
			}
		}
		else if ( bQuotation )	// "" の中なら
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


// 空白文字を正規化する
void CAnalize::NormalizerSpace(char* pStr)
{
	bool  bSpace = false;
	char* pSrc;
	char* pDes;
	char  c;

	pSrc = pStr;
	pDes = pStr;

	// 先頭の空白文字読み飛ばし */
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

	// 最後尾の空白文字削除
	if ( pDes != pStr && *(pDes - 1) == ' ' )
	{
		*(pDes - 1) = '\0';
	}
}


// ===========================================================================
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================
