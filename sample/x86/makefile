# -----------------------------------------------------------------------------
#  HOS-V4 サンプル                                                             
#   メイクファイル 日立 H8/300H 用                                             
#                                                                              
#                                      Copyright (C) 1998-2002 by Project HOS  
#                                      http://sourceforge.jp/projects/hos/     
# -----------------------------------------------------------------------------


# メイクプログラムに極力依存しないように、単純に記述しています。


# パス
INCDIR    = ..\..\include
LIBDIR    = ..\..\lib\x86

# ツール
CC   = lcc
LINK = lcc

# オプション
CFLAGS = -c -o$@ -I$(INCDIR)
LFLAGS = -o$@ -k'-M'

# ターゲット
TARGET  = test.exe

#インクルードファイル
INCS = knl_id.h test.h

# オブジェクトファイル
OBJS = knl_cfg.obj test.obj $(LIBDIR)\h4lsic_s.lib


# ライブラリ生成
$(TARGET): $(OBJS)
	$(LINK) $(LFLAGS) $(OBJS)


# オブジェクト生成
kernel_cfg.obj: kernel_cfg.c $(INCS)
	$(CC) $(CFLAGS) kernel_cfg.c

test.obj: test.c $(INCS)
	$(CC) $(CFLAGS) test.c


#コンフィギュレーション
knl_cfg.c knl_id.h: system.cfg
	cpp -o system.i system.cfg
	hos4cfg system.i -c knl_cfg.c -i knl_id.h


# クリーンナップ
clean:
	del	*.obj
	del	$(TARGET)


# -----------------------------------------------------------------------------
#  Copyright (C) 1998-2002 by Project HOS                                      
# -----------------------------------------------------------------------------
