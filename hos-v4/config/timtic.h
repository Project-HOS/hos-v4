// ===========================================================================
//  HOS-V4 コンフィギュレーター
//    HOS_TIM_TIC API の処理
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ===========================================================================


#ifndef __HOSV4CFG_ApiTimTic_h__
#define __HOSV4CFG_ApiTimTic_h__


#include "apidef.h"
#include "parpack.h"


// CRE_TSK 用
class CApiTimTic : public CApiDef
{
public:
	CApiTimTic();		// コンストラクタ
	~CApiTimTic();		// デストラクタ

	int   AnalizeApi(const char* pszApiName, const char* pszParams);	// APIの解析
	int   AutoId(void);							// ID 定義ファイル書き出し
	void  WriteId(FILE* fp);					// cfgファイル定義部書き出し
	void  WriteCfgDef(FILE* fp);				// cfgファイル定義部書き出し

protected:
	int m_iNume;	// タイムティックの周期の分子
	int m_iDeno;	// タイムティックの周期の分母
};


#endif	// __HOSV4CFG_ApiTimTic_h__


// ===========================================================================
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ===========================================================================
