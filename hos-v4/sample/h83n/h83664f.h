/* ------------------------------------------------------------------------- */
/*  H8/3664F 用 ヘッダファイル                                               */
/*  全てのデバイスで検証をしている訳では無いので、使用にあたっては十分注意   */
/*  が必要です。                                                             */
/*  この辺が個人の限界と言う事で、バグ報告待ってます。                       */
/*                                                                           */
/*  日立統一ヘッダーファイル バージョン２との違い                            */
/*  日立のヘッダーファイルでは16bit長のフィールドは intで表しています。      */
/*  このヘッダーファイルもそれに倣おうかとも思いましたが、shortで表す事に    */
/*  しました。と言うのも SHなんかも結構 H8で作成したコーディングそのまま動   */
/*  いちゃう事が多いのですが(特に SCI等)、例えば ADはやはり10bitでその長さ   */
/*  は H8も SHも変わらず、レジスタは16bitでアクセスします。あっちは intで    */
/*  こっちは shortとなるのがイマイチ嫌なので、両方とも揃える為に shortで宣   */
/*  言しています。                                                           */
/*  また、日立コンパイラー バージョン３以上では問題とならないビットフィー    */
/*  ルドの省略ですが、秋月コンパイラ、つまり日立コンパイラ バージョン２の    */
/*  サブセットではコンパイルエラーとなるので、適当なフィールド名を充ててい   */
/*  ます。                                                                   */
/*                                                                           */
/*                                   Copyright (C) 1998-2003 by Project HOS  */
/* ------------------------------------------------------------------------- */


#ifndef __PROJECT_HOS__H8_3664_H_
#define __PROJECT_HOS__H8_3664_H_

/* IO デバイスアドレス定義 */
#define	__EKR_ADD__		0xFF10		/* EKRレジスタスタートアドレス */
#define	__TIMER_W_ADD__	0xFF80		/* TWレジスタスタートアドレス */
#define	__FLASH_ADD__	0xFF90		/* FLASHレジスタスタートアドレス */
#define	__TIMER_V_ADD__	0xFFA0		/* TVレジスタスタートアドレス */
#define	__TIMER_A_ADD__	0xFFA6		/* TAレジスタスタートアドレス */
#define	__SCI3_ADD__	0xFFA8		/* SCI3レジスタスタートアドレス */
#define	__AD_ADD__		0xFFB0		/* A/Dレジスタスタートアドレス */
#define	__WDT_ADD__		0xFFC0		/* WDTレジスタスタートアドレス */
#define	__IIC_ADD__		0xFFC4		/* IICレジスタスタートアドレス */
#define	__ADDRESS_BREAK_ADD__	0xFFC8		/* アドレスブレイクレジスタスタートアドレス */
#define	__IO_PORT_ADD__		0xFFD0	/* IOポートレジスタスタートアドレス */
#define	__SYSCR1_ADD__	0xFFF0		/* SYSCR1レジスタスタートアドレス */
#define	__SYSCR2_ADD__	0xFFF1		/* SYSCR2レジスタスタートアドレス */
#define	__IEGR1_ADD__	0xFFF2		/* IEGR1レジスタスタートアドレス */
#define	__IEGR2_ADD__	0xFFF3		/* IEGR2レジスタスタートアドレス */
#define	__IENR1_ADD__	0xFFF4		/* IENR1レジスタスタートアドレス */
#define	__IRR1_ADD__	0xFFF6		/* IRR1レジスタスタートアドレス */
#define	__IWPR_ADD__	0xFFF8		/* IWPRレジスタスタートアドレス */
#define	__MSTCR1_ADD__	0xFFF9		/* MSTCR1レジスタスタートアドレス */
#define	__TSCR_ADD__	0xFFFC		/* TSCRレジスタスタートアドレス */

/*TIMER W*/
struct __TIMER_W_REGISTER__
{
	union								/*TMRW*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char CTS:1;		/*カウンタスタート*/
			unsigned char rsv1:1;		/*予約*/
			unsigned char BUFEB:1;		/*バッファ動作 B*/
			unsigned char BUFEA:1;		/*バッファ動作 A*/
			unsigned char rsv2:1;		/*予約*/
			unsigned char PWMD:1;		/*PWMモード D*/
			unsigned char PWMC:1;		/*PWMモード C*/
			unsigned char PWMB:1;		/*PWMモード B*/
		} BIT;
	} TMRW;
	union								/*TCRW*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char CCLR:1;		/*カウンタクリア*/
			unsigned char CKS:3;		/*クロックセレクト*/
			unsigned char TOD:1;		/*タイマ出力レベルセット D*/
			unsigned char TOC:1;		/*タイマ出力レベルセット C*/
			unsigned char TOB:1;		/*タイマ出力レベルセット B*/
			unsigned char TOA:1;		/*タイマ出力レベルセット A*/
		} BIT;
	} TCRW;
	union								/*TIERW*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char OVIE:1;		/*タイマオーバーフロー割込みイネーブル*/
			unsigned char rsv1:3;		/*予約*/
			unsigned char IMIED:1;		/*インプットキャプチャ/コンペアマッチ割込みイネーブル D*/
			unsigned char IMIEC:1;		/*インプットキャプチャ/コンペアマッチ割込みイネーブル C*/
			unsigned char IMIEB:1;		/*インプットキャプチャ/コンペアマッチ割込みイネーブル B*/
			unsigned char IMIEA:1;		/*インプットキャプチャ/コンペアマッチ割込みイネーブル A*/
		} BIT;
	} TIERW;
	union								/*TSRW*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char OVF:1;		/*タイマオーバーフロー*/
			unsigned char rsv1:3;		/*予約*/
			unsigned char IMFD:1;		/*インプットキャプチャ/コンペアマッチフラグ D*/
			unsigned char IMFC:1;		/*インプットキャプチャ/コンペアマッチフラグ C*/
			unsigned char IMFB:1;		/*インプットキャプチャ/コンペアマッチフラグ B*/
			unsigned char IMFA:1;		/*インプットキャプチャ/コンペアマッチフラグ A*/
		} BIT;
	} TSRW;
	union								/*TIOR0*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char rsv1:1;		/*予約*/
			unsigned char IOB:3;		/*IOコントロール B*/
			unsigned char rsv2:1;		/*予約*/
			unsigned char IOA:3;		/*IOコントロール A*/
		} BIT;
	} TIOR0;
	union								/*TIOR1*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char rsv1:1;		/*予約*/
			unsigned char IOD:3;		/*IOコントロール D*/
			unsigned char rsv2:1;		/*予約*/
			unsigned char IOC:3;		/*IOコントロール C*/
		} BIT;
	} TIOR1;
	unsigned short	TCNT;				/*タイマカウンタ*/
	unsigned short	GRA;				/*ジェネラルレジスタ A*/
	unsigned short	GRB;				/*ジェネラルレジスタ B*/
	unsigned short	GRC;				/*ジェネラルレジスタ C*/
	unsigned short	GRD;				/*ジェネラルレジスタ D*/
};

#define	TW	(*(volatile struct __TIMER_W_REGISTER__ *)__TIMER_W_ADD__)


/*FLASH ROM*/
struct __FLASH_ROM_REGISTER__
{
	union								/*FLMCR1*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char rsv1:1;		/*予約*/
			unsigned char SWE:1;		/*ソフトウエアライトイネーブル*/
			unsigned char ESU:1;		/*イレースセットアップ*/
			unsigned char PSU:1;		/*プログラムセットアップ*/
			unsigned char EV:1;			/*イレースベリファイ*/
			unsigned char PV:1;			/*プログラムベリファイ*/
			unsigned char E:1;			/*いイレース*/
			unsigned char P:1;			/*プログラム*/
		} BIT;
	} FLMCR1;
	union								/*FLMCR2*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char FLER:1;		/*FLASH ROM 書き込みエラー*/
			unsigned char rsv1:7;		/*予約*/
		} BIT;
	} FLMCR2;
	union								/*FLPWCR*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char PDWND:1;		/*パワーダウンディスエーブル*/
			unsigned char rsv1:7;		/*予約*/
		} BIT;
	} FLPWCR;
	union								/*EBR1*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char rsv1:3;		/*予約*/
			unsigned char EB4:1;		/*イレースブロック 4*/
			unsigned char EB3:1;		/*イレースブロック 3*/
			unsigned char EB2:1;		/*イレースブロック 2*/
			unsigned char EB1:1;		/*イレースブロック 1*/
			unsigned char EB0:1;		/*イレースブロック 0*/
		} BIT;
	} EBR1;
	char	rsv1[ 0xff9b - 0xff93 - 1 ];	/*空き*/
	union								/*FENR*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char FLSHE:1;		/*フラッシュメモリコントロールレジスタイネーブル*/
			unsigned char rsv1:7;		/*予約*/
		} BIT;
	} FENR;
};

#define	FLASH	(*(volatile struct __FLASH_ROM_REGISTER__ *)__FLASH_ADD__)

/*TIMER V*/
struct __TIMER_V_REGISTER__
{
	union								/*TCRV0*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char CMIEB:1;		/*コンペアマッチインタラプトイネーブル B*/
			unsigned char CMIEA:1;		/*コンペアマッチインタラプトイネーブル A*/
			unsigned char OVIE:1;		/*タイマオーバーフローインタラプトイネーブル B*/
			unsigned char CCLR:2;		/*カウンタクリア*/
			unsigned char CKS:3;		/*クロックセレクト*/
		} BIT;
	} TCRV0;
	union								/*TCSRV*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char CMFB:1;		/*コンペアマッチフラグ B*/
			unsigned char CMFA:1;		/*コンペアマッチフラグ A*/
			unsigned char OVF:1;		/*タイマオーバーフローフラグ*/
			unsigned char rsv1:1;		/*予約*/
			unsigned char OS:4;			/*アウトプットセレクト*/
		} BIT;
	} TCSRV;
	unsigned char TCORA;				/*タイムコンスタントレジスタ A*/
	unsigned char TCORB;				/*タイムコンスタントレジスタ B*/
	unsigned char TCNTV;				/*タイマカウントタ V*/
	union								/*TCRV1*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char rsv1:3;		/*予約*/
			unsigned char TVEG:2;		/*TRGV 入力エッジセレクト*/
			unsigned char TRGE:1;		/*カウントアップの開始とカウントアップの停止の禁止と*/
			unsigned char rsv2:1;		/*予約*/
			unsigned char ICKS:1;		/*インターナルクロックセレクト 0*/
		} BIT;
	} TCRV1;
};

#define	TV	(*(volatile struct __TIMER_V_REGISTER__ *)__TIMER_V_ADD__)

/*TIMER A*/
struct __TIMER_A_REGISTER__
{
	union								/*TMA*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char CKSO:3;		/*TMOW端子から出力するクロックの選択*/
			unsigned char rsv1:1;		/*予約*/
			unsigned char CKSI:4;		/*タイマAの動作モードの設定*/
		} BIT;
	} TMA;
	unsigned char TCA;					/*タイマカウンタ A*/
};

#define	TA	(*(volatile struct __TIMER_A_REGISTER__ *)__TIMER_A_ADD__)

/*SCI3*/
struct __SCI3_REGISTER__
{
	union								/*SMR*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char COM:1;		/*コミュニケーションモード*/
			unsigned char CHR:1;		/*キャラクタレングス*/
			unsigned char PE:1;			/*パリティイネーブル*/
			unsigned char PM:1;			/*パリティモード*/
			unsigned char STOP:1;		/*ストップビットレングス*/
			unsigned char MP:1;			/*マルチプロセッサモード*/
			unsigned char CKS:2;		/*クロックセレクト*/
		} BIT;
	} SMR;
	unsigned char BRR;					/*ビットレートレジスタ*/
	union								/*SCR3*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char TIE:1;		/*トランスミットインタラプトイネーブル*/
			unsigned char RIE:1;		/*レシーブインタラプトイネーブル*/
			unsigned char TE:1;			/*トランスミットイネーブル*/
			unsigned char RE:1;			/*レシーブイネーブル*/
			unsigned char MPIE:1;		/*マルチプロセッサインタラプトイネーブル*/
			unsigned char TEIE:1;		/*トランスミットエンドインタラプトイネーブル*/
			unsigned char CKE:2;		/*クロックイネーブル*/
		} BIT;
	} SCR3;
	unsigned char TDR;					/**/
	union								/*SSR*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char TDRE:1;		/*トランスミットデータレジスタエンプティ*/
			unsigned char RDRF:1;		/*レシーブデータレジスタフル*/
			unsigned char OER:1;		/*オーバーランエラー*/
			unsigned char FER:1;		/*フレーミングエラー*/
			unsigned char PER:1;		/*パリティエラー*/
			unsigned char TEND:1;		/*トランスミットエンド*/
			unsigned char MPBR:1;		/*マルチプロセッサビットレシーブ*/
			unsigned char MPBT:1;		/*マルチプロセッサビットトランスファ*/
		} BIT;
	} SSR;
	unsigned char RDR;					/*レシーブデータレジスタ*/
};

#define	SCI3	(*(volatile struct __SCI3_REGISTER__ *)__SCI3_ADD__)

/*AD*/
struct __AD_REGISTER__
{
	unsigned short ADDRA;				/*A/D データレジスタ A*/
	unsigned short ADDRB;				/*A/D データレジスタ B*/
	unsigned short ADDRC;				/*A/D データレジスタ C*/
	unsigned short ADDRD;				/*A/D データレジスタ D*/
	union								/*ADCSR*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char ADF:1;		/*A/D エンドフラグ*/
			unsigned char ADIE:1;		/*A/D インタラプトイネーブル*/
			unsigned char ADST:1;		/*A/D スタート*/
			unsigned char SCAN:1;		/*スキャンモード*/
			unsigned char CKS:1;		/*クロックセレクト*/
			unsigned char CH:3;			/*チャネルセレクト*/
		} BIT;
	} ADCSR;
	union								/*ADCR*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char TRGE:1;		/*トリガイネーブル*/
			unsigned char rsv1:7;		/*予約*/
		} BIT;
	} ADCR;
};

#define	AD	(*(volatile struct __AD_REGISTER__ *)__AD_ADD__)

/*WDT*/
struct __WDT_REGISTER__
{
	union								/*TCSRWD*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char B6WI:1;		/*ビット 6 書込み禁止*/
			unsigned char TCWE:1;		/*タイマカウンタ W 書き込み許可*/
			unsigned char B4WI:1;		/*ビット 4 書込み禁止*/
			unsigned char TCSRWE:1;		/*タイマコントロール/ステータスレジスタ W 書き込み許可*/
			unsigned char B2WI:1;		/*ビット 2 書込み禁止*/
			unsigned char WDON:1;		/*ウオッチドッグタイマオン*/
			unsigned char B0WI:1;		/*ビット 0 書込み禁止*/
			unsigned char WRST:1;		/*ウオッチドッグタイマリセット*/
		} BIT;
	} TCSRWD;
	unsigned char	TCWD;				/*タイマカウンタ*/
	union								/*TMWD*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char rsv1:4;		/*予約*/
			unsigned char CKS:4;		/*クロックセレクト*/
		} BIT;
	} TMWD;
};

#define	WDT	(*(volatile struct __WDT_REGISTER__ *)__WDT_ADD__)

/*IIC*/
struct __IIC_REGISTER__
{
	union								/*ICCR*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char ICE:1;		/*I2Cバスインタフェースイネーブル*/
			unsigned char IEIC:1;		/*I2Cバスインタフェース割込みイネーブル*/
			unsigned char MST:1;		/*マスター/スレーブ選択*/
			unsigned char TRS:1;		/*送受選択*/
			unsigned char ACKE:1;		/*アクノリッジビット判定選択*/
			unsigned char BBSY:1;		/*バスビジー*/
			unsigned char IRIC:1;		/*I2Cバスインタフェース割込み要求フラグ*/
			unsigned char SCP:1;		/*開始条件/停止条件発行禁止ビット*/
		} BIT;
	} ICCR;
	union								/*ICSR*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char ESTP:1;		/*エラー停止条件検出フラグ*/
			unsigned char STOP:1;		/*正常停止条件検出フラグ*/
			unsigned char IRTR:1;		/*I2Cバスインタフェース連続送受信割込み要求フラグ*/
			unsigned char AASX:1;		/*第二スレーブアドレス認識フラグ*/
			unsigned char AL:1;			/*アービトレーションロストフラグ*/
			unsigned char AAS:1;		/*スレーブアドレス認識フラグ*/
			unsigned char ADZ:1;		/*ゼネラルコールアドレス認識フラグ*/
			unsigned char ACKB:1;		/*アクノリッジビット*/
		} BIT;
	} ICSR;
	union
	{
		struct
		{
			union
			{
				unsigned char	BYTE;	/*Byte Access*/
				struct					/*Bit Access*/
				{
					unsigned char SVAX:7;	/*第二スレーブアドレス*/
					unsigned char FSX:1;	/*SARのFSとの組み合わせで転送フォーマットを設定*/
				} BIT;
			} UN_SARX;
			union
			{
				unsigned char	BYTE;	/*Byte Access*/
				struct					/*Bit Access*/
				{
					unsigned char SVA:7;	/*スレーブアドレス*/
					unsigned char FS:1;		/*SARXのFSXとの組み合わせで転送フォーマットを設定*/
				} BIT;
			} UN_SAR;
		} ICE0;
		struct
		{
			unsigned char	UN_ICDR;	/* I2Cバス データレジスタ*/
			union
			{
				unsigned char	BYTE;	/*Byte Access*/
				struct					/*Bit Access*/
				{
					unsigned char MLS:1;	/*MSBファースト/LSBファースト選択*/
					unsigned char WAIT:1;	/*ウエイト挿入ビット*/
					unsigned char CKS:3;	/*転送クロック選択*/
					unsigned char BC:3;		/*ビットカウンター*/
				} BIT;
			} UN_ICMR;
		} ICE1;
	} EQU;
};

#define	IIC	(*(volatile struct __IIC_REGISTER__ *)__IIC_ADD__)
#define	ICDR	EQU.ICE1.UN_ICDR		/* ICDR */
#define	ICMR	EQU.ICE1.UN_ICMR		/* ICDR */
#define	SAR		EQU.ICE0.UN_SAR			/* SAR  */
#define	SARX	EQU.ICE0.UN_SARX		/* SARX */

/*ADDRESS BREAK*/
struct __ADDRESS_BREAK_REGISTER__
{
	union								/*ABRKCR*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char RTINTE:1;		/*RTE割込みイネーブル*/
			unsigned char CSEL:2;		/*コンディションセレクト*/
			unsigned char ACMP:3;		/*アドレスコンペア*/
			unsigned char DCMP:2;		/*データコンペア*/
		} BIT;
	} CR;
	union								/*ABRKSR*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char ABIF:1;		/*ABRKCRで設定された条件が成立した時*/
			unsigned char ABIE:1;		/* 1の時アドレスブレーク割込み要求をイネーブルにします*/
			unsigned char rsv1:6;		/*予約*/
		} BIT;
	} SR;
	void			*BAR;				/*ブレークアドレスレジスタ*/
	unsigned short	BDR;				/*ブレークデータレジスタ*/
};

#define	ABRK	(*(volatile struct __ADDRESS_BREAK_REGISTER__ *)__ADDRESS_BREAK_ADD__)

/*IO PORT*/
struct __IO_PORT_REGISTER__
{
	union								/*PUCR1*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char B7:1;			/* Bit 7 */
			unsigned char B6:1;			/* Bit 6 */
			unsigned char B5:1;			/* Bit 5 */
			unsigned char B4:1;			/* Bit 4 */
			unsigned char rsv1:1;		/*予約*/
			unsigned char B2:1;			/* Bit 2 */
			unsigned char B1:1;			/* Bit 1 */
			unsigned char B0:1;			/* Bit 0 */
		} BIT;
	} PUCR1;
	union								/*PUCR5*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char rsv1:2;		/*予約*/
			unsigned char B5:1;			/* Bit 5 */
			unsigned char B4:1;			/* Bit 4 */
			unsigned char B3:1;			/* Bit 3 */
			unsigned char B2:1;			/* Bit 2 */
			unsigned char B1:1;			/* Bit 1 */
			unsigned char B0:1;			/* Bit 0 */
		} BIT;
	} PUCR5;
	char	rsv1[ 0xffd4 - 0xffd1 - 1 ];	/*空き*/
	union								/*PDR1*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char B7:1;			/* Bit 7 */
			unsigned char B6:1;			/* Bit 6 */
			unsigned char B5:1;			/* Bit 5 */
			unsigned char B4:1;			/* Bit 4 */
			unsigned char rsv1:1;		/*予約*/
			unsigned char B2:1;			/* Bit 2 */
			unsigned char B1:1;			/* Bit 1 */
			unsigned char B0:1;			/* Bit 0 */
		} BIT;
	} PDR1;
	union								/*PDR2*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char rsv1:5;		/*予約*/
			unsigned char B2:1;			/* Bit 2 */
			unsigned char B1:1;			/* Bit 1 */
			unsigned char B0:1;			/* Bit 0 */
		} BIT;
	} PDR2;
	char	rsv2[ 0xffd8 - 0xffd5 - 1 ];	/*空き*/
	union								/*PDR5*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char B7:1;			/* Bit 7 */
			unsigned char B6:1;			/* Bit 6 */
			unsigned char B5:1;			/* Bit 5 */
			unsigned char B4:1;			/* Bit 4 */
			unsigned char B3:1;			/* Bit 3 */
			unsigned char B2:1;			/* Bit 2 */
			unsigned char B1:1;			/* Bit 1 */
			unsigned char B0:1;			/* Bit 0 */
		} BIT;
	} PDR5;
	char	rsv3[ 0xffda - 0xffd8 - 1 ];	/*空き*/
	union								/*PDR7*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char rsv1:1;		/*予約*/
			unsigned char B6:1;			/* Bit 6 */
			unsigned char B5:1;			/* Bit 5 */
			unsigned char B4:1;			/* Bit 4 */
			unsigned char rsv2:4;		/*予約*/
		} BIT;
	} PDR7;
	union								/*PDR8*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char B7:1;			/* Bit 7 */
			unsigned char B6:1;			/* Bit 6 */
			unsigned char B5:1;			/* Bit 5 */
			unsigned char B4:1;			/* Bit 4 */
			unsigned char B3:1;			/* Bit 3 */
			unsigned char B2:1;			/* Bit 2 */
			unsigned char B1:1;			/* Bit 1 */
			unsigned char B0:1;			/* Bit 0 */
		} BIT;
	} PDR8;
	char	rsv4[ 0xffdd - 0xffdb - 1 ];	/*空き*/
	union								/*PDRB*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char B7:1;			/* Bit 7 */
			unsigned char B6:1;			/* Bit 6 */
			unsigned char B5:1;			/* Bit 5 */
			unsigned char B4:1;			/* Bit 4 */
			unsigned char B3:1;			/* Bit 3 */
			unsigned char B2:1;			/* Bit 2 */
			unsigned char B1:1;			/* Bit 1 */
			unsigned char B0:1;			/* Bit 0 */
		} BIT;
	} PDRB;
	char	rsv5[ 0xffe0 - 0xffdd - 1 ];	/*空き*/
	union								/*PMR1*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char IRQ3:1;		/*P17/IRQ3/TRGV端子の機能の選択をします*/
			unsigned char IRQ2:1;		/*P16/IRQ2端子の機能の選択をします*/
			unsigned char IRQ1:1;		/*P15/IRQ1端子の機能の選択をします*/
			unsigned char IRQ0:1;		/*P14/IRQ0端子の機能の選択をします*/
			unsigned char rsv1:2;		/*予約*/
			unsigned char TXD:1;		/*P22/TXD端子の機能の選択をします*/
			unsigned char TMOW:1;		/*P10/TMOW端子の機能の選択をします*/
		} BIT;
	} PMR1;
	union								/*PMR5*/
	{
		unsigned char BYTE;				/*Byte Access*/
		struct							/*Bit Access*/
		{
			unsigned char rsv1:2;		/*予約*/
			unsigned char WKP5:1;		/*P55/WKP5端子の機能の選択をします*/
			unsigned char WKP4:1;		/*P54/WKP4端子の機能の選択をします*/
			unsigned char WKP3:1;		/*P53/WKP3端子の機能の選択をします*/
			unsigned char WKP2:1;		/*P52/WKP2端子の機能の選択をします*/
			unsigned char WKP1:1;		/*P51/WKP1端子の機能の選択をします*/
			unsigned char WKP0:1;		/*P50/WKP0端子の機能の選択をします*/
		} BIT;
	} PMR5;
	char	rsv6[ 0xffe4 - 0xffe1 - 1 ];	/*空き*/
	unsigned char	PCR1;				/**/
	unsigned char	PCR2;				/**/
	char	rsv7[ 0xffe8 - 0xffe5 - 1 ];	/*空き*/
	unsigned char	PCR5;				/**/
	char	rsv8[ 0xffea - 0xffe8 - 1 ];	/*空き*/
	unsigned char	PCR7;				/**/
	unsigned char	PCR8;				/**/
};

#define	IO	(*(volatile struct __IO_PORT_REGISTER__ *)__IO_PORT_ADD__)

/*SYSCR1*/
union __SYSCR1_REGISTER__
{
	unsigned char BYTE;					/*Byte Access*/
	struct								/*Bit Access*/
	{
		unsigned char SSBY:1;			/*ソフトウエアスタンバイ*/
		unsigned char STS:3;			/*スタンバイタイマセレクト*/
		unsigned char NESEL:1;			/*ノイズ除去サンプリング周波数選択*/
		unsigned char rsv1:3;			/*予約*/
	} BIT;
};

#define	SYSCR1	(*(volatile union __SYSCR1_REGISTER__ *)__SYSCR1_ADD__)

/*SYSCR2*/
union __SYSCR2_REGISTER__
{
	unsigned char BYTE;					/*Byte Access*/
	struct								/*Bit Access*/
	{
		unsigned char SMSEL:1;			/*スリープモード選択*/
		unsigned char LSON:1;			/*ロースピードオンフラグ*/
		unsigned char DTON:1;			/*ダイレクトトランスファオンフラグ*/
		unsigned char MA:3;				/*アクティブモードクロックセレクト*/
		unsigned char SA:2;				/*サブアクティブモードクロックセレクト*/
	} BIT;
};

#define	SYSCR2	(*(volatile union __SYSCR2_REGISTER__ *)__SYSCR2_ADD__)

/*IEGR1*/
union __IEGR1_REGISTER__
{
	unsigned char BYTE;					/*Byte Access*/
	struct								/*Bit Access*/
	{
		unsigned char NMIEG:1;			/*NMIエッジセレクト*/
		unsigned char rsv1:3;			/*予約*/
		unsigned char IEG3:1;			/*IRQ3エッジセレクト*/
		unsigned char IEG2:1;			/*IRQ2エッジセレクト*/
		unsigned char IEG1:1;			/*IRQ1エッジセレクト*/
		unsigned char IEG0:1;			/*IRQ0エッジセレクト*/
	} BIT;
};

#define	IEGR1	(*(volatile union __IEGR1_REGISTER__ *)__IEGR1_ADD__)

/*IEGR2*/
union __IEGR2_REGISTER__
{
	unsigned char BYTE;					/*Byte Access*/
	struct								/*Bit Access*/
	{
		unsigned char rsv1:2;			/*予約*/
		unsigned char WPEG5:1;			/*WKOP5エッジセレクト*/
		unsigned char WPEG4:1;			/*WKOP4エッジセレクト*/
		unsigned char WPEG3:1;			/*WKOP3エッジセレクト*/
		unsigned char WPEG2:1;			/*WKOP2エッジセレクト*/
		unsigned char WPEG1:1;			/*WKOP1エッジセレクト*/
		unsigned char WPEG0:1;			/*WKOP0エッジセレクト*/
	} BIT;
};

#define	IEGR2	(*(volatile union __IEGR2_REGISTER__ *)__IEGR2_ADD__)

/*IENR1*/
union __IENR1_REGISTER__
{
	unsigned char BYTE;					/*Byte Access*/
	struct								/*Bit Access*/
	{
		unsigned char IENDT:1;			/*直接遷移割込み要求イネーブル*/
		unsigned char IENTA:1;			/*タイマ A 割込み要求イネーブル*/
		unsigned char IENWP:1;			/* WAKE UP 割込み要求イネーブル*/
		unsigned char rsv1:1;			/*予約*/
		unsigned char IEN3:1;			/*IRQ3 割込み要求イネーブル*/
		unsigned char IEN2:1;			/*IRQ2 割込み要求イネーブル*/
		unsigned char IEN1:1;			/*IRQ1 割込み要求イネーブル*/
		unsigned char IEN0:1;			/*IRQ0 割込み要求イネーブル*/
	} BIT;
};

#define	IENR1	(*(volatile union __IENR1_REGISTER__ *)__IENR1_ADD__)

/*IRR1*/
union __IRR1_REGISTER__
{
	unsigned char BYTE;					/*Byte Access*/
	struct								/*Bit Access*/
	{
		unsigned char IRRDT:1;			/*直接遷移割込み要求フラグ*/
		unsigned char IRRTA:1;			/*タイマ A 割込み要求フラグ*/
		unsigned char rsv1:2;			/*予約*/
		unsigned char IRRI3:1;			/*IRQ3 割込み要求フラグ*/
		unsigned char IRRI2:1;			/*IRQ2 割込み要求フラグ*/
		unsigned char IRRI1:1;			/*IRQ1 割込み要求フラグ*/
		unsigned char IRRI0:1;			/*IRQ0 割込み要求フラグ*/
	} BIT;
};

#define	IRR1	(*(volatile union __IRR1_REGISTER__ *)__IRR1_ADD__)

/*IWPR*/
union __IWPR_REGISTER__
{
	unsigned char BYTE;					/*Byte Access*/
	struct								/*Bit Access*/
	{
		unsigned char rsv1:2;			/*予約*/
		unsigned char IWPF5:1;			/*WKP5 割込み要求フラグ*/
		unsigned char IWPF4:1;			/*WKP4 割込み要求フラグ*/
		unsigned char IWPF3:1;			/*WKP3 割込み要求フラグ*/
		unsigned char IWPF2:1;			/*WKP2 割込み要求フラグ*/
		unsigned char IWPF1:1;			/*WKP1 割込み要求フラグ*/
		unsigned char IWPF0:1;			/*WKP0 割込み要求フラグ*/
	} BIT;
};

#define	IWPR	(*(volatile union __IWPR_REGISTER__ *)__IWPR_ADD__)

/*MSTCR1*/
union __MSTCR1_REGISTER__
{
	unsigned char BYTE;					/*Byte Access*/
	struct								/*Bit Access*/
	{
		unsigned char rsv1:1;			/*予約*/
		unsigned char MSTIIC:1;			/*IICモジュールスタンバイ*/
		unsigned char MSTS3:1;			/*SCI3モジュールスタンバイ*/
		unsigned char MSTAD:1;			/*A/D変換モジュールスタンバイ*/
		unsigned char MSTWD:1;			/*ウオッチドッグタイマーモジュールスタンバイ*/
		unsigned char MSTTW:1;			/*タイマ W モジュールスタンバイ*/
		unsigned char MSTTV:1;			/*タイマ V モジュールスタンバイ*/
		unsigned char MSTTA:1;			/*タイマ A モジュールスタンバイ*/
	} BIT;
};

#define	MSTCR1	(*(volatile union __MSTCR1_REGISTER__ *)__MSTCR1_ADD__)

/*TSCR*/
union __TSCR_REGISTER__
{
	unsigned char BYTE;					/*Byte Access*/
	struct								/*Bit Access*/
	{
		unsigned char rsv1:6;			/*予約*/
		unsigned char IICRST:1;			/*IICRSTは、I2Cレジスタを除くコントロール部をRESETします。*/
		unsigned char IICX:1;			/*ICMRのCKS2〜0との組み合わせで、マスターモードの転送レートを選択します。*/
	} BIT;
};

#define	TSCR	(*(volatile union __TSCR_REGISTER__ *)__TSCR_ADD__)

/*EKR*/
union __EKR_REGISTER__
{
	unsigned char BYTE;					/*Byte Access*/
	struct								/*Bit Access*/
	{
		unsigned char B7:1;				/* Bit 7 */
		unsigned char B6:1;				/* Bit 6 */
		unsigned char B5:1;				/* Bit 5 */
		unsigned char B4:1;				/* Bit 4 */
		unsigned char B3:1;				/* Bit 3 */
		unsigned char B2:1;				/* Bit 2 */
		unsigned char B1:1;				/* Bit 1 */
		unsigned char B0:1;				/* Bit 0 */
	} BIT;
};

#define	EKR	(*(volatile union __EKR_REGISTER__ *)__EKR_ADD__)

#endif /* __PROJECT_HOS__H8_3664_H_ */
