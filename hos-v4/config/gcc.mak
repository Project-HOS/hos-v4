# -----------------------------------------------------------------------------
#  HOS-V4                                                                      
#   ����ե�����졼�����ᥤ���ե����� GCC��                       
#                                                                              
#                                       Copyright (C) 1998-2002 by Project HOS 
#                                       http://sourceforge.jp/projects/hos/    
# -----------------------------------------------------------------------------



# �ġ���
CC   = gcc
LINK = gcc


# ���ץ����
CFLAGS = -O2 -pipe
LFLAGS = 


# �������å�
TARGET  = hos4cfg


# ���֥������ȥե�����
OBJS = hos4cfg.o \
       analyze.o \
       parpack.o \
       read.o \
       defercd.o \
       intstk.o \
       idlstk.o \
       knlheap.o \
       maxtpri.o \
       apidef.o \
       apiinc.o \
       cretsk.o \
       deftex.o \
       cresem.o \
       creflg.o \
       credtq.o \
       crembx.o \
       crempf.o \
       crembf.o \
       timtic.o \
       crecyc.o \
       crealm.o \
       defexc.o \
       attini.o \
       attisr.o



# �������å�����
$(TARGET): $(OBJS)
	$(LINK) $(OBJS) -o $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe $(OBJS)

.cpp.o:
	$(CC) $(CFLAGS) -c $<

.c.o:
	$(CC) $(CFLAGS) -c $<


# -----------------------------------------------------------------------------
#  Copyright (C) 1998-2002 by Project HOS                                      
# -----------------------------------------------------------------------------
