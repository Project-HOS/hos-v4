# --------------------------------------------------------------------------- 
#  Hyper Operating System V4  日立 H8 用 サンプルプログラム                   
#    メイクファイル（秋月Cコンパイラ版）                                      
#                                                                             
#  1. 著作者は本ソースファイルの利用によって発生する如何なる損害にもその      
#     責任を負いません。                                                      
#  2. 再配布において著作権情報及び免責事項の情報改竄を固く禁じます。          
#  3. 上記を守る限り、改版したものの再配布を含め、商用／非商用を問わず        
#     あらゆる用途に自由に利用できます。                                      
#  4. 改版物の再配布時は、改版者の著作情報と連絡先を必ず追記してください。    
#                                                                             
#                                   Copyright (C) 1998-2002 by Project HOS    
#                                   http://sourceforge.jp/projects/hos/       
# --------------------------------------------------------------------------- 



# Borland-C++ Ver 5.5 付属 make にて動作確認しています。
# system.cfg のプリプロセッサ処理にも Borland-C++ Ver 5.5 を利用しています。



# パス
INCH8DIR = \akih8c			# Cコンパイラの設定にあわせて書き換えてください
INCDIR   = ..\..\include
LIBDIR   = ..\..\lib\h8


# ツール
CC     = cc38h
CPP    = cpp32				# BC55 のプリプロセッサを利用
ASM    = a38h
LINK   = l38h
OBJCNV = c38h


# オプション
CFLAGS   = -CPU=300HA -INCLUDE=$(INCH8DIR),$(INCDIR)
CPPFLAGS = -P-
AFLAGS   = 
LFLAGS   = 

# ターゲット
TARGET = sample.mot

#インクルードファイル
INCS = kernel_id.h sample.h h8_sci.h

# オブジェクトファイル
OBJS = vector.obj crt0.obj sample.obj h8_sci.obj kernel_cfg.obj



# ライブラリ生成
$(TARGET): $(OBJS) link.sub
	$(LINK) /SUB=link.sub
	$(OBJCNV) sample.abs $(TARGET)


# オブジェクト生成
kernel_cfg.obj: kernel_cfg.c $(INCS)
	$(CC) $(CFLAGS) kernel_cfg.c

vector.obj: vector.src
	$(ASM) $(AFLAGS) vector.src

crt0.obj: crt0.src
	$(ASM) $(AFLAGS) crt0.src

sample.obj: sample.c $(INCS)
	$(CC) $(CFLAGS) sample.c

h8_sci.obj: h8_sci.c $(INCS)
	$(CC) $(CFLAGS) h8_sci.c

kernel_cfg.c kernel_id.h: system.cfg
	$(CPP) $(CPPFLAGS) -osystem.i system.cfg
	hos4cfg system.i


# クリーンナップ
clean:
	-del *.i
	-del *.abs
	-del *.obj
	-del kernel_cfg.c
	-del kernel_id.h
	-del $(TARGET)



# --------------------------------------------------------------------------- 
#  Copyright (C) 1998-2002 by Project HOS                                     
# --------------------------------------------------------------------------- 
