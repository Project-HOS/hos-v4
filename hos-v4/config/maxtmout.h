// ===========================================================================
//  HOS-V4 コンフィギュレーター
//    HOS_MAX_TPRI API の処理
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ===========================================================================


#ifndef __HOSV4CFG_ApiMaxTimout_h__
#define __HOSV4CFG_ApiMaxTimout_h__


#include "apidef.h"
#include "parpack.h"


// HOS_MAX_TIMOUT 用
class CApiMaxTimout : public CApiDef
{
public:
	CApiMaxTimout();		// コンストラクタ
	~CApiMaxTimout();		// デストラクタ

	int   AnalizeApi(const char* pszApiName, const char* pszParams);	// APIの解析
	int   AutoId(void);							// 自動ID番号割り当て
	void  WriteCfgDef(FILE* fp);				// cfgファイル定義部書き出し

protected:
	int m_iMaxTimout;
};


#endif	// HOSV4CFG_ApiMaxTimout


// ===========================================================================
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ===========================================================================
