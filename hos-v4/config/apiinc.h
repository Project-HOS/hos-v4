// ===========================================================================
//  HOS-V4 コンフィギュレーター
//    INCLUDE API の処理
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ===========================================================================


#ifndef __HOSV4CFG_ApiInclude_h__
#define __HOSV4CFG_ApiInclude_h__


#include "apidef.h"
#include "parpack.h"


// CRE_TSK 用
class CApiInclude : public CApiDef
{
public:
	CApiInclude();		// コンストラクタ
	~CApiInclude();		// デストラクタ

	char* GetApiName(void);						// API名取得
	int   AddParams(const char* pszParams);		// パラメーター追加
	int   AutoId(void);							// 自動ID番号割り当て
	void  WriteCfgDef(FILE* fp);				// cfgファイル定義部書き出し
};


#endif	// __HOSV4CFG_ApiInclude_h__


// ===========================================================================
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ===========================================================================
