# -----------------------------------------------------------------------------
#  HOS-V4                                                                      
#   コンフィギュレーターメイクファイル GCC用                       
#                                                                              
#                                       Copyright (C) 1998-2002 by Project HOS 
#                                       http://sourceforge.jp/projects/hos/    
# -----------------------------------------------------------------------------



# ツール
CC   = gcc
LINK = gcc


# オプション
CFLAGS = -O2 -pipe
LFLAGS = 


# ターゲット
TARGET  = hos4cfg


# オブジェクトファイル
OBJS = hos4cfg.o \
       analyze.o \
       apidef.o \
       apiinc.o \
       attini.o \
       attisr.o \
       crecyc.o \
       credtq.o \
       creflg.o \
       crembf.o \
       crembx.o \
       crempf.o \
       cresem.o \
       cretsk.o \
       defercd.o \
       defexc.o \
       deftex.o \
       knlheap.o \
       maxtmout.o \
       maxtpri.o \
       parpack.o \
       read.o \
       timtic.o



# ターゲット生成
$(TARGET): $(OBJS)
	$(LINK) $(OBJS) -o hos4cfg

clean:
	rm -f $(TARGET) $(TARGET).exe $(OBJS)

.cpp.o:
	$(CC) $(CFLAGS) -c $<

.c.o:
	$(CC) $(CFLAGS) -c $<
