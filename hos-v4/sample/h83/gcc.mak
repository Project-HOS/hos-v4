# --------------------------------------------------------------------------- 
#  Hyper Operating System V4  サンプルプログラム                              
#    メイクファイル（h8300-hms  GNUCコンパイラ版）                         
#                                                                             
#                                   Copyright (C) 1998-2002 by Project HOS    
#                                   http://sourceforge.jp/projects/hos/       
# --------------------------------------------------------------------------- 


# FreeBSD 4.6R付属make、GNU make 3.79.1にて動作確認しています。


# パス
INCDIR   = ../../include
PACDIR   = ../../include/h83
LIBDIR   = ../../lib/h83/

# ツール
CC     = h8300-hms-coff-gcc
CPP    = h8300-hms-coff-gcc
ASM    = h8300-hms-coff-gcc
LINK   = h8300-hms-coff-gcc
OBJCNV = h8300-hms-coff-objcopy -O srec
HOSCFG = ../../config/hos4cfg


# オプション
CFLAGS   = -Os -Wall -I$(INCDIR) -I$(PACDIR) -mh -c -pipe
CPPFLAGS = -E -mh
AFLAGS   = -mh -c
LFLAGS   = -mh -mrelax -nostartfiles -nostdlib -Wl,-Map,$(TARGET).map \
		-Wl,-T$(LDSCRIPT) -L$(LIBDIR)
LIBS	 = -lgcc -lh4h83
# ターゲット
TARGET = sample

#インクルードファイル
INCS = kernel_id.h sample.h h8_sci.h

#リンカスクリプト
LDSCRIPT = h83048.x

# オブジェクトファイル
OBJS = vector.o crt0.o sample.o h8_sci.o kernel_cfg.o


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

h8_sci.o: h8_sci.c $(INCS)
	$(CC) $(CFLAGS) h8_sci.c

kernel_cfg.c kernel_id.h: system.cfg
	cat system.cfg | $(CPP) $(CPPFLAGS) - | $(HOSCFG) -


# フラッシュ書き込み
write:
	h8write -3048 $(TARGET).mot /dev/cuaa0


# クリーンナップ
clean:
	rm  -f  $(TARGET).coff $(TARGET).mot $(TARGET).map \
		$(OBJS) kernel_id.h kernel_cfg.c *~


# --------------------------------------------------------------------------- 
#  Copyright (C) 1998-2002 by Project HOS                                     
# --------------------------------------------------------------------------- 
