// ===========================================================================
//  HOS V4 コンフィギュレーター
//    NULLパラメータークラス
//
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================


#ifndef __HOSV4CFG_ParamNull_h__
#define __HOSV4CFG_ParamNull_h__


#include "paratype.h"


// パラメーターブロッククラス
class CParamNull : public CParamType
{
public:
	int GetParamType();			// 型タイプ取得

	int SetParamString(const char* pszParam);	// パラメーター文字列の設定
	const char* GetParamString(void);			// パラメーター文字列の取得
	int GetParamInt(void);						// パラメーターの整数値取得
};


#endif	// __HOSV4CFG_ParamNull_h__


// ===========================================================================
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================
