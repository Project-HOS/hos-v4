// ===========================================================================
//  HOS-V4 コンフィギュレーター
//    HOS_MAX_TPRI API の処理
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ===========================================================================


#ifndef __HOSV4CFG_ApiMaxTpri_h__
#define __HOSV4CFG_ApiMaxTpri_h__


#include "apidef.h"
#include "parpack.h"


// HOS_MAX_TPRI 用
class CApiMaxTpri : public CApiDef
{
public:
	CApiMaxTpri();		// コンストラクタ
	~CApiMaxTpri();		// デストラクタ

	int   AnalizeApi(const char* pszApiName, const char* pszParams);	// APIの解析
	int   AutoId(void);							// 自動ID番号割り当て
	void  WriteCfgDef(FILE* fp);				// cfgファイル定義部書き出し

protected:
	int m_iMaxPri;
};


#endif	// __HOSV4CFG_ApiMaxTpri_h__


// ===========================================================================
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ===========================================================================
