# ------------------------------------------------------------------------
#  Hyper Operating System V4  サンプルプログラム                      
#  i386-elf 用メイクファイル                                                     
#                                  Copyright (C) 1998-2002 by Project HOS
#                                  http://sourceforge.jp/projects/hos/
# ------------------------------------------------------------------------

CC     = i386-elf-gcc
CPP    = i386-elf-cpp
ASM    = i386-elf-gcc
LINK   = i386-elf-gcc
OBJCNV = i386-elf-objcopy
DISASM = i386-elf-objdump
MKMAP  = i386-elf-nm
SORT   = sort
MKDISK = /bin/sh ./mkdisk.sh
HOSCFG = ../../config/hos4cfg

TARGET = sample

LIBDIR = ../../lib/ia32/ia32gcc
INCDIR = ../../include
IA32INC = /usr/cross-i386-elf/i386-elf/include

CFLAGS = -g -O2 -Wall -c  -I$(INCDIR) -I$(IA32INC) -pipe
AFLAGS = -c -Wall 
LFLAGS = -nostdlib -m elf_i386 -L$(LIBDIR) -T hos4.lds -lgcc 

CPPFLAGS = -E  -I$(INCDIR) -pipe

INCS   = kernel_id.h printk.h
OBJS   = crt0.o sample.o ostimer.o exphdrs.o kernel_cfg.o printk.o
LIBS   = -lc -lia32gcc

$(TARGET).bin: $(OBJS) 
	$(LINK) $(LFLAGS) -o $(TARGET).out $(OBJS) $(LIBS)
	$(DISASM) -S $(TARGET).out > $(TARGET).asm
	$(MKMAP)  $(TARGET).out |$(SORT) > $(TARGET).map
	$(OBJCNV) -g -O binary $(TARGET).out $(TARGET).bin

crt0.o: crt0.S
	$(ASM) $(AFLAGS) crt0.S -o crt0.o

sample.o: sample.c $(INCS)
	$(CC) $(CFLAGS) sample.c -o sample.o
exphdrs.o: exphdrs.c $(INCS)
	$(CC) $(CFLAGS) exphdrs.c -o exphdrs.o
ostimer.o: ostimer.c ostimer.h
	$(CC) $(CFLAGS) ostimer.c -o ostimer.o

printk.o: printk.c printk.h
	$(CC) $(CFLAGS) printk.c -o printk.o

kernel_cfg.o: kernel_cfg.c $(INCS)
	$(CC) $(CFLAGS) kernel_cfg.c -o kernel_cfg.o

kernel_cfg.c kernel_id.h: system.cfg ia32.cfg
	$(CPP) $(CPPFLAGS) system.cfg | $(HOSCFG) -

disk:$(TARGET).bin
	$(MKDISK) $(TARGET).bin
clean:
	rm -f $(TARGET).bin $(TARGET).out $(TARGET).asm $(TARGET).map $(OBJS) \
		kernel_id.h kernel_cfg.c *~

# ------------------------------------------------------------------------
#                                  Copyright (C) 1998-2002 by Project HOS
#                                  http://sourceforge.jp/projects/hos/
# ------------------------------------------------------------------------
