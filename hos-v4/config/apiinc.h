// ---------------------------------------------------------------------------
//  HOS-V4 コンフィギュレーター
//    INCLUDE API の処理
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_ApiInclude_h__
#define __HOSV4CFG_ApiInclude_h__


#include "apidef.h"
#include "parpack.h"


// INCLUDE 用
class CApiInclude : public CApiDef
{
public:
	CApiInclude();		// コンストラクタ
	~CApiInclude();		// デストラクタ

	int   AnalizeApi(const char* pszApiName, const char* pszParams);	// APIの解析
	int   AutoId(void);							// 自動ID番号割り当て
	void  WriteCfgDef(FILE* fp);				// cfgファイル定義部書き出し
};


#endif	// __HOSV4CFG_ApiInclude_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------
