// ---------------------------------------------------------------------------
//  HOS-V4 コンフィギュレーター
//    エラーコード管理
//
//                                      Copyright (C) 2002 by Ryuji Fuchikami
// ---------------------------------------------------------------------------


#ifndef __HOSV4CFG_DefErrorCode_h__
#define __HOSV4CFG_DefErrorCode_h__


// 正常系エラーコード定義 */
#define CFG_ERR_NOPROC			(-2)	// 未処理
#define CFG_ERR_COMPLETE		(-1)	// 完了
#define CFG_ERR_OK				0		// 正常

// 異常系エラーコード定義
#define CFG_ERR_EOF				1		// 予期せぬEOF
#define CFG_ERR_CR				2		// 不正な改行
#define CFG_ERR_STATE_LEN		3		// １ステートが長すぎる
#define CFG_ERR_SYNTAX			4		// 構文エラー
#define CFG_ERR_PAREN			5		// ()の不整合
#define CFG_ERR_BRACE			6		// {}の不整合
#define CFG_ERR_SEMICOLON		7		// セミコロンが無い
#define CFG_ERR_TEXT			8		// 不正な文字列定数
#define CFG_ERR_ID_CONFLICT		9		// ID衝突
#define CFG_ERR_PARAM			10		// パラメーター不正


const char* GetErrMessage(int iErr);


#endif	// __HOSV4CFG_DefErrorCode_h__


// ---------------------------------------------------------------------------
//  Copyright (C) 2002 by Ryuji Fuchikami                                     
// ---------------------------------------------------------------------------
