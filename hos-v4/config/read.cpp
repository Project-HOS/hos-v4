// ---------------------------------------------------------------------------
//  HOS-V4 コンフィギュレーター                                               
//    データ読み込みクラス                                                    
//                                                                            
//                                      Copyright (C) 2002 by Ryuji Fuchikami 
// ---------------------------------------------------------------------------


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "defercd.h"
#include "read.h"


// コンストラクタ
CRead::CRead(FILE *fp)
{
	m_fpRead    = fp;
	m_iLineNum  = 1;
	m_blLineTop = true;
}


// デストラクタ
CRead::~CRead()
{
}


// １ステート読み込み
int CRead::ReadState(char *szState)
{
	bool blEsc   = false;
	bool blSpace = true;	// true で始めて先頭の空白を読み飛ばす
	int  iCount = 0;
	int  iErr;
	int  c;

	for ( ; ; )
	{
		// １文字読み込み
		if ( (c = fgetc(m_fpRead)) == EOF )
		{
			if ( blEsc || iCount != 0 )
			{
				iErr = CFG_ERR_EOF;	// 予期せぬEOF
			}
			else
			{
				iErr = CFG_ERR_COMPLETE;	// 完了
			}
			break;
		}

		// サイズチェック
		if ( iCount >= READ_MAX_STATE - 1 )
		{
			iErr = CFG_ERR_STATE_LEN;
			break;
		}

		// 行頭が # ならスキップ
		if ( m_blLineTop && c == '#' )
		{
			iErr = SkipPriProcessorLine();
			if ( iErr != CFG_ERR_OK )
			{
				break;
			}
			continue;
		}

		// 改行文字の処理
		if ( c == '\n' )
		{
			m_iLineNum++;
			m_blLineTop = true;
		}

		// 空白文字のスキップ
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

		// 文字列の処理
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

		// ステート完了文字なら
		if ( c == ';' )
		{
			iErr = CFG_ERR_OK;
			break;
		}

		// 文字の読み込み
		szState[iCount++] = c;
	}

	// 末尾の空白文字削除
	if ( iCount > 0 && szState[iCount - 1] == ' ' )
	{
		iCount--;
	}

	szState[iCount] = '\0';

	return iErr;
}


// プリプロセッサラインのスキップ
int CRead::SkipPriProcessorLine(void)
{
	bool blEsc  = false;
	int  c;

	for ( ; ; )
	{
		// １文字読み込み
		if ( (c = fgetc(m_fpRead)) == EOF )
		{
			if ( blEsc )
			{
				return CFG_ERR_EOF;	// 予期せぬEOF
			}
			return CFG_ERR_OK;
		}

		// \ の次は無条件にスキップ
		if ( blEsc )
		{
			blEsc  = false;
			continue;
		}
		blEsc  = false;

		// \ のチェック
		if ( c == '\\' )
		{
			blEsc  = true;
			continue;
		}

		// 行末のチェック
		if ( c == '\n' )
		{
			m_iLineNum++;
			return CFG_ERR_OK;
		}
	}
}


// 文字列読み込み
int CRead::ReadString(int cDelimiter, char* szText, int& iCount)
{
	bool blEsc  = false;
	int c;

	for ( ; ; )
	{
		// １文字読み込み
		if ( (c = fgetc(m_fpRead)) == EOF )
		{
			return CFG_ERR_EOF;	// 予期せぬEOF
		}

		// サイズチェック
		if ( iCount >= READ_MAX_STATE - 1 )
		{
			return CFG_ERR_STATE_LEN;
		}

		// 改行チェック
		if ( c == '\n' )
		{
			return CFG_ERR_CR;		// 不正な改行
		}

		// 文字の設定
		szText[iCount++] = c;

		// \ の次は無条件にスキップ
		if ( blEsc )
		{
			blEsc  = false;
			continue;
		}

		// \ のチェック
		if ( c == '\\' )
		{
			blEsc  = true;
			continue;
		}

		blEsc  = false;

		// デリミタ文字なら完了
		if ( c == cDelimiter )
		{
			return CFG_ERR_OK;
		}
	}
}


// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------
