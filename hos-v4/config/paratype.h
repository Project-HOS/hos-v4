// ===========================================================================
//  HOS V4 コンフィギュレーター
//    パラメータータイプ 抽象クラス
//
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================


#ifndef __HOSV4CFG_ParamType_h__
#define __HOSV4CFG_ParamType_h__


// パラメーター型定義
#define PARAMTYPE_NULL			0	// 空パラメーター
#define PARAMTYPE_BLOCK			1	// パラメーターブロック
#define PARAMTYPE_AUTO_INT		2	// 自動割付対応整数値パラメーター
#define PARAMTYPE_NONAUTO_INT	3	// 自動割付非対応整数値パラメーター
#define PARAMTYPE_PREPROP		4	// プリプロセッサ定数式パラメーター
#define PARAMTYPE_GENELAL		5	// 一般定数式パラメーター

// エラーコード定義
#define PARAMTYPE_ERR_OK		0	// 正常
#define PARAMTYPE_ERR_WARNING	1	// 警告ル
#define PARAMTYPE_ERR_ERROR		2	// エラー
#define PARAMTYPE_ERR_FATAL		3	// 致命エラー


// パラメータータイプクラス
class CParamType
{
public:
	virtual ~CParamType();	// デストラクタ

	virtual int GetParamType() = 0;		// 型タイプ取得

	virtual int SetParamString(const char* pszParam) = 0;	// パラメーター文字列の設定
	
	virtual const char* GetParamString(void) = 0;			// パラメーター文字列の取得
	virtual int GetParamInt(void) = 0;						// パラメーターの整数値取得
};


#endif	// __HOSV4CFG_ParamType_h__


// ===========================================================================
//                                                 Copyright (C) 2002 by Ryuz
// ===========================================================================
