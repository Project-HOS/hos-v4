# -----------------------------------------------------------------------------
#  HOS-V4 サンプル                                                                     
#   メイクファイル 日立 H8/300H 用                                         
#                                                                              
#                                   Copyright (C) 1998-2002 by Ryuji Fuchikami 
# -----------------------------------------------------------------------------


# メイクプログラムに極力依存しないように、単純に記述しています。


# パス
INCH8DIR  = \akih8c
INCDIR    = ..\..\include
LIBDIR    = ..\..\lib\h8

# ツール
CC   = cc38h
ASM  = a38h
LINK = l38h

# オプション
CFLAGS = -CPU=300HA -INCLUDE=$(INCH8DIR),$(INCDIR)
AFLAGS = 
LFLAGS = 

# ターゲット
TARGET  = test.abs

#インクルードファイル
INCS = kernel_id.h test.h

# オブジェクトファイル
OBJS = $(LIBDIR)\h4akih8v.obj kernel_cfg.obj test.obj $(LIBDIR)\h4akih8.lib


# ライブラリ生成
$(TARGET): $(OBJS) link.sub
	$(LINK) -SUBCOMMAND=link.sub


# オブジェクト生成
kernel_cfg.obj: kernel_cfg.c $(INCS)
	$(CC) $(CFLAGS) kernel_cfg.c

test.obj: test.c $(INCS)
	$(CC) $(CFLAGS) test.c


# クリーンナップ
clean:
	del	*.o
	del	$(TARGET)


# -----------------------------------------------------------------------------
#  Copyright (C) 1998-2002 by Ryuji Fuchikami                                  
# -----------------------------------------------------------------------------
