// ===========================================================================
//  HOS V4 コンフィギュレーター
//    API定義クラス
//
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================


#ifndef __HOSV4CFG_DefApi_h__
#define __HOSV4CFG_DefApi_h__


#include "parablk.h"


// API定義構造体
struct TDefApi
{
	const char*  pszApiName;		// API名
	CParamBlock* pParamBlock;		// パラメーターブロック
	TDefApi*     pNext;				// 次のAPI定義
};


// API定義管理クラス
class CDefApi
{
public:
	CDefApi();
	~CDefApi();

	void AddDefine(TDefApi* pDefApi);				// API定義の追加
	TDefApi* GetDefine(const char* pszApiName);		// API定義の取得

protected:
	TDefApi* m_pDefApi;
};


#endif	// __HOSV4CFG_DefApi_h__


// ===========================================================================
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================
