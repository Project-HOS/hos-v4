# ------------------------------------------------------------------------
#  Hyper Operating System V4  サンプルプログラム                      
#                                                                     
#                                  Copyright (C) 1998-2002 by Project HOS
#                                  http://sourceforge.jp/projects/hos/
# ------------------------------------------------------------------------

CC     = sh-hms-gcc
CPP    = sh-hms-gcc
ASM    = sh-hms-gcc
LINK   = sh-hms-gcc
OBJCNV = sh-hms-objcopy
HOSCFG = ../../config/hos4cfg

TARGET = sample

LIBDIR = ../../lib/sh/sh4gcc
INCDIR = ../../include
SH4INC = /usr/local/include/hitachi/SH4

CFLAGS = -O2 -Wall -c -ml -m4-single-only  -I$(INCDIR) -I$(SH4INC) -pipe
AFLAGS = -c -ml -m4-single-only  -x assembler-with-cpp
LFLAGS = -ml -m4-single-only -mrelax -nostartfiles -L$(LIBDIR)\
	-Wl,-v,-t,-Map,sample.map,-Ttext=0x8c010000

CPPFLAGS = -E -x c -ml -m4-single-only  -I$(INCDIR) -pipe

INCS   = kernel_id.h sample.h scif.h
#OBJS   = startup.o sample.o ostimer.o scif.o sh7750.o kernel_cfg.o
OBJS   = crt0.o sample.o ostimer.o scif.o sh7750.o kernel_cfg.o
LIBS   = -lh4sh4

$(TARGET).mot: $(OBJS)
	$(LINK) $(LFLAGS) -o $(TARGET).out $(OBJS) $(LIBS)
	$(OBJCNV) -O srec $(TARGET).out $(TARGET).mot

crt0.o: crt0.s
	$(ASM) $(AFLAGS) crt0.s -o crt0.o

startup.o: startup.s
	$(ASM) $(AFLAGS) startup.s -o startup.o

sample.o: sample.c $(INCS)
	$(CC) $(CFLAGS) sample.c -o sample.o

ostimer.o: ostimer.c ostimer.h
	$(CC) $(CFLAGS) ostimer.c -o ostimer.o

scif.o: scif.c scif.h
	$(CC) $(CFLAGS) scif.c -o scif.o

sh7750.o: sh7750.c sh7750.h
	$(CC) $(CFLAGS) sh7750.c -o sh7750.o

kernel_cfg.o: kernel_cfg.c $(INCS)
	$(CC) $(CFLAGS) kernel_cfg.c -o kernel_cfg.o

kernel_cfg.c kernel_id.h: system.cfg
	$(CPP) $(CPPFLAGS) system.cfg | $(HOSCFG) -

clean:
	rm -f $(TARGET).mot $(TARGET).out $(TARGET).map $(OBJS) \
		kernel_id.h kernel_cfg.c *~

# ------------------------------------------------------------------------
#                                  Copyright (C) 1998-2002 by Project HOS
#                                  http://sourceforge.jp/projects/hos/
# ------------------------------------------------------------------------
