# --------------------------------------------------------------------------- 
#  Hyper Operating System V4  ����ץ�ץ����                              
#    �ᥤ���ե��������Ω H8300H  ����C����ѥ����ǡ�                         
#                                                                             
#                                   Copyright (C) 1998-2003 by Project HOS    
#                                   http://sourceforge.jp/projects/hos/       
# --------------------------------------------------------------------------- 



# Borland-C++ Ver 5.5 ��° make �ˤ�ư���ǧ���Ƥ��ޤ���
# system.cfg �Υץ�ץ��å������ˤ� Borland-C++ Ver 5.5 �����Ѥ��Ƥ��ޤ���



# �ѥ�
INCH8DIR = \akih8c			# C����ѥ��������ˤ��碌�ƽ񤭴����Ƥ�������
HOSROOT  = ..\..
INCDIR   = $(HOSROOT)\include
LIBDIR   = $(HOSROOT)\lib\h83\akih8


# �ġ���
CC     = cc38h
CPP    = cpp32				# BC55 �Υץ�ץ��å�������
ASM    = a38h
LINK   = l38h
OBJCNV = c38h


# ���ץ����
CFLAGS   = -CPU=300HN -INCLUDE=$(INCH8DIR),$(INCDIR)
CPPFLAGS = -P-
AFLAGS   = 
LFLAGS   = 

# �������å�
TARGET = sample.mot

#���󥯥롼�ɥե�����
INCS = kernel_id.h sample.h ostimer.h h8t_sci.h

# ���֥������ȥե�����
OBJS = vector.obj crt0.obj sample.obj ostimer.obj h8t_sci.obj kernel_cfg.obj



# �饤�֥������
$(TARGET): $(OBJS) link.sub
	$(LINK) /SUB=link.sub
	$(OBJCNV) sample.abs $(TARGET)


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

h8t_sci.obj: h8t_sci.c $(INCS)
	$(CC) $(CFLAGS) h8t_sci.c

kernel_cfg.c kernel_id.h: system.cfg
	$(CPP) $(CPPFLAGS) -osystem.i system.cfg
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
#  Copyright (C) 1998-2003 by Project HOS                                     
# --------------------------------------------------------------------------- 
