// ===========================================================================
//  HOS V4 コンフィギュレーター Ver 1.00
//    データ読み込みクラス
//
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================



#ifndef __HOSV4CFG_Read_h__
#define __HOSV4CFG_Read_h__



// 構文解析クラス
class CRead
{
public:
	static void ReadConfig(FILE* fpIn, FILE* fpOut);	// コンフィギュレーションファイルの読み込み

protected:
	static void  Analize(void);

	static char* m_pFileText;		// コンフィギュレーションファイルデータ
	static int   m_iFileSize;		// コンフィギュレーションファイルサイズ
	static int   m_iLineNum;		// 行番号
};


#endif	// __HOSV4CFG_Read_h__


// ===========================================================================
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================
