# --------------------------------------------------------------------------- 
#  Hyper Operating System V4  サンプルプログラム                              
#    メイクファイル（日立 H8300H  秋月Cコンパイラ版）                         
#                                                                             
#                                   Copyright (C) 1998-2003 by Project HOS    
#                                   http://sourceforge.jp/projects/hos/       
# --------------------------------------------------------------------------- 



# Borland-C++ Ver 5.5 付属 make にて動作確認しています。
# system.cfg のプリプロセッサ処理にも Borland-C++ Ver 5.5 を利用しています。



# パス
INCH8DIR = \akih8c			# Cコンパイラの設定にあわせて書き換えてください
HOSROOT  = ..\..
INCDIR   = $(HOSROOT)\include
LIBDIR   = $(HOSROOT)\lib\h83\akih8


# ツール
CC     = cc38h
CPP    = cpp32				# BC55 のプリプロセッサを利用
ASM    = a38h
LINK   = l38h
OBJCNV = c38h


# オプション
CFLAGS   = -CPU=300HN -INCLUDE=$(INCH8DIR),$(INCDIR)
CPPFLAGS = -P-
AFLAGS   = 
LFLAGS   = 

# ターゲット
TARGET = sample.mot

#インクルードファイル
INCS = kernel_id.h sample.h ostimer.h h8t_sci.h

# オブジェクトファイル
OBJS = vector.obj crt0.obj sample.obj ostimer.obj h8t_sci.obj kernel_cfg.obj



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

ostimer.obj: ostimer.c $(INCS)
	$(CC) $(CFLAGS) ostimer.c

h8t_sci.obj: h8t_sci.c $(INCS)
	$(CC) $(CFLAGS) h8t_sci.c

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
#  Copyright (C) 1998-2003 by Project HOS                                     
# --------------------------------------------------------------------------- 
