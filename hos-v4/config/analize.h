// ===========================================================================
//  HOS V4 コンフィギュレーター
//    構文解析クラス
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami 
// ===========================================================================


#ifndef __HOSV4CFG__Analize_h__
#define __HOSV4CFG__Analize_h__



// 構文解析クラス
class CAnalize
{
public:
	static int  SplitState(char* pszApiName, char* pszParams, const char *pszState);	// ステートメントをAPI名とパラメーターに分割
	static int  SearchChar(char* pszBuf, const char* &pszText, char c);		// 特定文字のまでの切り出し
	static int  GetParameter(char* pszBuf, const char* &pszText);			// パラメーターの切り出し
	static int  DecodeText(char *pszBuf, const char* pszText);				// 文字列定数を展開する
	static void SpaceCut(char* pszText);			// 前後の空白を削除する
};


#endif	// __HOSV4CFG__Analize_h__


// ===========================================================================
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ===========================================================================
