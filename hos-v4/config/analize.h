// ===========================================================================
//  HOS V4 コンフィギュレーター
//    構文解析クラス
//
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================


#ifndef __HOSV4CFG_Analize_h__
#define __HOSV4CFG_Analize_h__


// 構文解析クラス
class CAnalize
{
public:
	static char* SearchBrace(char* pStr);			// '{'に対応する'}'の検索
	static char* SearchParentheses(char* pStr);		// '('に対応する')'の検索
	static char* SearchComma(char* pStr);			// 次の','を検索
	static void  NormalizerSpace(char* pStr);		// 空白文字を正規化する
};


#endif	// __HOSV4CFG_Analize_h__


// ===========================================================================
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================
