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



# �������å�����
$(TARGET): $(OBJS)
	$(LINK) $(OBJS) -o hos4cfg

clean:
	rm -f $(TARGET) $(TARGET).exe $(OBJS)

.cpp.o:
	$(CC) $(CFLAGS) -c $<

.c.o:
	$(CC) $(CFLAGS) -c $<
