# --------------------------------------------------------------------------- 
#  Hyper Operating System V4  ����ץ�ץ������                              
#    �ᥤ���ե��������Ω H8300H  ����C����ѥ����ǡ�                         
#                                                                             
#                                   Copyright (C) 1998-2002 by Project HOS    
#                                   http://sourceforge.jp/projects/hos/       
# --------------------------------------------------------------------------- 



# Borland-C++ Ver 5.5 ��° make �ˤ�ư���ǧ���Ƥ��ޤ���
# system.cfg �Υץ�ץ����å������ˤ� Borland-C++ Ver 5.5 �����Ѥ��Ƥ��ޤ���



# �ѥ�
HOSROOT  = ..\..
INCDIR   = $(HOSROOT)\include
LIBDIR   = $(HOSROOT)\lib\h83\htc


# �ġ���
CC     = ch38
CPP    = ch38
ASM    = asm38
LINK   = optlnk


# ���ץ����
CFLAGS   = -CPU=300HA -INCLUDE=$(INCH8DIR),$(INCDIR)
CPPFLAGS = -P-
AFLAGS   = 
LFLAGS   = 

# �������å�
TARGET = sample.mot

#���󥯥롼�ɥե�����
INCS = kernel_id.h sample.h ostimer.h h8_sci.h

# ���֥������ȥե�����
OBJS = vector.obj crt0.obj sample.obj ostimer.obj h8_sci.obj kernel_cfg.obj



# �饤�֥������
$(TARGET): $(OBJS) link.sub
	$(LINK) -SUB=htc.sub


# ���֥�����������
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

h8_sci.obj: h8_sci.c $(INCS)
	$(CC) $(CFLAGS) h8_sci.c

kernel_cfg.c kernel_id.h: system.cfg
	$(CPP) $(CFLAGS) -PREP=system.i system.cfg
	hos4cfg system.i


# ���꡼��ʥå�
clean:
	-del *.i
	-del *.abs
	-del *.obj
	-del kernel_cfg.c
	-del kernel_id.h
	-del $(TARGET)



# --------------------------------------------------------------------------- 
#  Copyright (C) 1998-2002 by Project HOS                                     
# --------------------------------------------------------------------------- 