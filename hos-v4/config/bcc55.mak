# -----------------------------------------------------------------------------
#  Hyper Operating System V4  ����ե�����졼����                             
#   Borland-C++ Version 5.5 �� �ᥤ���ե�����                                  
#                                                                              
#                                       Copyright (C) 1998-2002 by Project HOS 
#                                       http://sourceforge.jp/projects/hos/    
# -----------------------------------------------------------------------------


# �ġ���
CC   = bcc32
LINK = bcc32


# ���ץ����
CFLAGS = -c -O2
LFLAGS = 


# �������å�
TARGET  = hos4cfg.exe


# ���֥������ȥե�����
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


# �������å�����
$(TARGET): $(OBJS)
	$(LINK) $(OBJS) -o$(TARGET)

# ���꡼�󥢥å�
clean:
	del $(OBJS) $(TARGET)

# ������§
.cpp.obj:
	$(CC) $(CFLAGS) $<


# -----------------------------------------------------------------------------
#  Copyright (C) 1998-2002 by Project HOS                                      
# -----------------------------------------------------------------------------
