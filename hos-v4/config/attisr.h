// ---------------------------------------------------------------------------
//  HOS-V4 コンフィギュレーター
//    ATT_ISR API の処理
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_AttIsr_h__
#define __HOSV4CFG_AttIsr_h__


#include "apidef.h"
#include "parpack.h"


// ATT_ISR 用
class CApiAttIsr : public CApiDef
{
public:
	CApiAttIsr();		// コンストラクタ
	~CApiAttIsr();		// デストラクタ

	int   AnalizeApi(const char* pszApiName, const char* pszParams);	// APIの解析
	int   AutoId(void);
	void  WriteCfgDef(FILE* fp);	// cfgファイル定義部書き出し
	void  WriteCfgIni(FILE* fp);	// cfgファイル初期化部書き出し

protected:
	int m_iIntStackSize;
	int m_iMaxIntNo;
	int m_iMinIntNo;
	int m_iMaxIsrId;
};


#endif	// __HOSV4CFG_AttIsr_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------
