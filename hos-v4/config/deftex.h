// ---------------------------------------------------------------------------
//  HOS-V4 コンフィギュレーター
//    DEF_TEX API の処理
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_DefTex_h__
#define __HOSV4CFG_DefTex_h__


#include "apidef.h"
#include "parpack.h"


// DEF_TEX 用
class CApiDefTex : public CApiDef
{
public:
	CApiDefTex();		// コンストラクタ
	~CApiDefTex();		// デストラクタ

	int   AnalyzeApi(const char* pszApiName, const char* pszParams);	// APIの解析
	int   AutoId(void);							// 自動ID番号割り当て
	void  WriteCfgDef(FILE* fp);				// cfgファイル定義部書き出し
	void  WriteCfgIni(FILE* fp);				// cfgファイル初期化部書き出し
};


#endif	// __HOSV4CFG_DefTex_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------
