# -----------------------------------------------------------------------------
#  Hyper Operating System V4  コンフィギュレーター                             
#   Borland-C++ Version 5.5 用 メイクファイル                                  
#                                                                              
#                                       Copyright (C) 1998-2002 by Project HOS 
#                                       http://sourceforge.jp/projects/hos/    
# -----------------------------------------------------------------------------


# ツール
CC   = bcc32
LINK = bcc32


# オプション
CFLAGS = -c -O2
LFLAGS = 


# ターゲット
TARGET  = hos4cfg.exe


# オブジェクトファイル
OBJS = hos4cfg.obj \
       analyze.obj \
       apidef.obj \
       apiinc.obj \
       attini.obj \
       attisr.obj \
       crecyc.obj \
       credtq.obj \
       creflg.obj \
       crembf.obj \
       crembx.obj \
       crempf.obj \
       cresem.obj \
       cretsk.obj \
       defercd.obj \
       defexc.obj \
       deftex.obj \
       knlheap.obj \
       maxtmout.obj \
       maxtpri.obj \
       parpack.obj \
       read.obj \
       timtic.obj


.suffixes:
.suffixes: .cpp


# ターゲット生成
$(TARGET): $(OBJS)
	$(LINK) $(OBJS) -o$(TARGET)

# クリーンアップ
clean:
	del $(OBJS) $(TARGET)

# 推論規則
.cpp.obj:
	$(CC) $(CFLAGS) $<


# -----------------------------------------------------------------------------
#  Copyright (C) 1998-2002 by Project HOS                                      
# -----------------------------------------------------------------------------
