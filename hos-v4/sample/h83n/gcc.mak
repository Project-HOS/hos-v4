# --------------------------------------------------------------------------- 
#  Hyper Operating System V4  サンプルプログラム                              
#    メイクファイル（h8300-hms  GNUCコンパイラ版）                            
#                                                                             
#                                   Copyright (C) 1998-2003 by Project HOS    
#                                   http://sourceforge.jp/projects/hos/       
# --------------------------------------------------------------------------- 


# FreeBSD 4.6R付属make、GNU make 3.79.1にて動作確認しています。


# パス
HOSROOT  = ../..
INCDIR   = $(HOSROOT)/include
HINCDIR  = .
PACDIR   = $(HOSROOT)/include/h83
LIBDIR   = $(HOSROOT)/lib/h83/gcc

# ツール
CC     = h8300-hms-gcc
CPP    = h8300-hms-gcc
ASM    = h8300-hms-gcc -x assembler-with-cpp
LINK   = h8300-hms-gcc
OBJCNV = h8300-hms-objcopy -O srec
HOSCFG = ../../config/hos4cfg

RM     = rm -f
#RM    = command /c del
#RM    = del

# オプション
CFLAGS   = -O2 -fomit-frame-pointer -Wall -I$(INCDIR) -I$(PACDIR) -I$(HINCDIR) -mh -mn -c -pipe
CPPFLAGS = -E -mh -mn -x c
AFLAGS   = -mh -mn -c
LFLAGS   = -mh -mn -mrelax -nostartfiles -nostdlib -Wl,-Map,$(TARGET).map \
		-Wl,-T$(LDSCRIPT) -L$(LIBDIR)
LIBS	 = -lgcc -lh4h83n
# ターゲット
TARGET = sample

#インクルードファイル
INCS = kernel_id.h sample.h h8t_sci.h

#リンカスクリプト
LDSCRIPT = h83664.x

# オブジェクトファイル
OBJS = crt0.o vector.o sample.o h8t_sci.o kernel_cfg.o ostimer.o

# ターゲットモジュール生成
$(TARGET).mot: $(OBJS) $(LDSCRIPT)
	$(LINK) $(LFLAGS) -o $(TARGET).coff $(OBJS) $(LIBS)
	$(OBJCNV) $(TARGET).coff $(TARGET).mot

# オブジェクト生成
kernel_cfg.o: kernel_cfg.c $(INCS)
	$(CC) $(CFLAGS) kernel_cfg.c

vector.o: vector.s
	$(ASM) $(AFLAGS) vector.s

crt0.o: crt0.s
	$(ASM) $(AFLAGS) crt0.s

sample.o: sample.c $(INCS)
	$(CC) $(CFLAGS) sample.c

h8t_sci.o: h8t_sci.c $(INCS)
	$(CC) $(CFLAGS) h8t_sci.c

ostimer.o: ostimer.c $(INCS)
	$(CC) $(CFLAGS) ostimer.c

kernel_cfg.c kernel_id.h: system.cfg
	$(CPP) $(CPPFLAGS) system.cfg | $(HOSCFG) -

# フラッシュ書き込み
write: $(TARGET).mot
	h8write -3664 $(TARGET).mot /dev/cuaa0

# クリーンナップ
clean:
	$(RM) $(TARGET).coff
	$(RM) $(TARGET).mot
	$(RM) $(TARGET).map
	$(RM) *.o
	$(RM) kernel_id.h
	$(RM) kernel_cfg.c
	$(RM) *~

# --------------------------------------------------------------------------- 
#  Copyright (C) 1998-2003 by Project HOS                                     
# --------------------------------------------------------------------------- 
