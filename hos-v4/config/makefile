# -----------------------------------------------------------------------------
#  HOS-V4                                                                      
#   コンフィギュレーターメイクファイル Borland-C++ 5.5用                       
#                                                                              
#                                   Copyright (C) 1998-2002 by Ryuji Fuchikami 
# -----------------------------------------------------------------------------



# ツール
CC   = bcc32
LINK = bcc32


# オプション
CFLAGS = -c
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



# ターゲット生成
$(TARGET): $(OBJS)
	$(LINK) $(OBJS) -ohos4cfg

clean:
	del *.obj

.c.obj:
	$(CC) -c $<


