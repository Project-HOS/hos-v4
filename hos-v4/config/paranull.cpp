// ===========================================================================
//  HOS V4 コンフィギュレーター
//    NULLパラメータークラス
//
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================


#include "paranull.h"


// 型タイプ取得
int CParamNull::GetParamType()
{
	return PARAMTYPE_NULL;
}


// パラメーター文字列の設定
int CParamNull::SetParamString(const char* pszParam)
{
	return PARAMTYPE_ERR_OK;
}


// パラメーター文字列の取得
const char* CParamNull::GetParamString(void)
{
	return "";
}


// パラメーターの整数値取得
int CParamNull::GetParamInt(void)
{
	return 0;
}


// ===========================================================================
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================
