# -----------------------------------------------------------------------------
#  HOS-V4 ����ץ�                                                                     
#   �ᥤ���ե����� ��Ω H8/300H ��                                         
#                                                                              
#                                   Copyright (C) 1998-2002 by Ryuji Fuchikami 
# -----------------------------------------------------------------------------


# �ᥤ���ץ����˶��ϰ�¸���ʤ��褦�ˡ�ñ��˵��Ҥ��Ƥ��ޤ���


# �ѥ�
INCH8DIR  = \akih8c
INCDIR    = ..\..\include
LIBDIR    = ..\..\lib\h8

# �ġ���
CC   = cc38h
ASM  = a38h
LINK = l38h

# ���ץ����
CFLAGS = -CPU=300HA -INCLUDE=$(INCH8DIR),$(INCDIR)
AFLAGS = 
LFLAGS = 

# �������å�
TARGET  = sample.abs

#���󥯥롼�ɥե�����
# INCS = kernel_id.h test.h

# ���֥������ȥե�����
# OBJS = $(LIBDIR)\h4akih8v.obj kernel_cfg.obj test.obj $(LIBDIR)\h4akih8.lib
OBJS = crt0.obj sample.obj


# �饤�֥������
$(TARGET): $(OBJS) link.sub
	$(LINK) -SUBCOMMAND=link.sub


# ���֥�����������
#kernel_cfg.obj: kernel_cfg.c $(INCS)
#	$(CC) $(CFLAGS) kernel_cfg.c

crt0.obj: crt0.src
	$(ASM) $(AFLAGS) crt0.src

sample.obj: sample.c $(INCS)
	$(CC) $(CFLAGS) sample.c


# ���꡼��ʥå�
clean:
	del	*.o
	del	$(TARGET)


# -----------------------------------------------------------------------------
#  Copyright (C) 1998-2002 by Ryuji Fuchikami                                  
# -----------------------------------------------------------------------------
