// ===========================================================================
//  HOS V4 コンフィギュレーター Ver 1.00
//    データ読み込みクラス
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami 
// ===========================================================================



#ifndef __HOSV4CFG_Read_h__
#define __HOSV4CFG_Read_h__


#define READ_MAX_STATE		4096	// １ステートの最大文字数


// 構文解析クラス
class CRead
{
public:
	CRead(FILE *fp);				// コンストラクタ
	~CRead();						// デストラクタ

	int ReadState(char *szState);	// １ステート読み込み
	int GetLineNum(void)			// 現在の行番号取得
	{ return m_iLineNum; }

protected:
	int SkipPriProcessorLine(void);	// プリプロセッサラインのスキップ
	int ReadString(int cDelimiter, char* szText, int& iCount);	// 文字列読み込み

	FILE *m_fpRead;					// 読み込み用ファイルポインタ
	int  m_iLineNum;				// 現在の行番号
	bool m_blLineTop;				// 行の先頭
};


#endif	// __HOSV4CFG_Read_h__


// ===========================================================================
//                                      Copyright (C) 2002 by Ryuji Fuchikami 
// ===========================================================================
