// ===========================================================================
//  HOS V4 コンフィギュレーター
//    パラメーターブロック管理クラス
//
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================


#ifndef __HOSV4CFG_ParamBlock_h__
#define __HOSV4CFG_ParamBlock_h__


#include "paratype.h"


// パラメーターブロッククラス
class CParamBlock : public CParamType
{
public:
	CParamBlock(int iMaxParam, int iMinParam);		// コンストラクタ
	~CParamBlock();									// デストラクタ

	int GetParamType();		// 型タイプ取得

	int SetParamString(const char* pszParam);		// パラメーター文字列の設定

	void SetParam(int iIndex, CParamType* pParamType);	// パラメーターの設定
	CParamType* GetParam(int iIndex);					// パラメーターの取得

protected:
	CParamType** m_ppPramList;		// パラメーターリスト
	int m_iMaxParam;				// 最大パラメーター数
	int m_iMinParam;				// 最小パラメーター数
};


#endif	// __HOSV4CFG_ParamBlock_h__


// ===========================================================================
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================
