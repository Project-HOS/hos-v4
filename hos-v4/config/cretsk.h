// ---------------------------------------------------------------------------
//  HOS-V4 コンフィギュレーター
//    CRE_TSK API の処理
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_CreTak_h__
#define __HOSV4CFG_CreTak_h__


#include "apidef.h"
#include "parpack.h"


// CRE_TSK 用
class CApiCreTsk : public CApiDef
{
public:
	CApiCreTsk();		// コンストラクタ
	~CApiCreTsk();		// デストラクタ

	int   AnalizeApi(const char* pszApiName, const char* pszParams);	// APIの解析
	void  WriteId(FILE* fp);					// ID 定義ファイル書き出し
	void  WriteCfgDef(FILE* fp);				// cfgファイル定義部書き出し
	void  WriteCfgIni(FILE* fp);				// cfgファイル初期化部書き出し
	void  WriteCfgStart(FILE* fp);				// cfgファイル起動部書き出し
};


#endif	// __HOSV4CFG_CreTak_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------
