#
# Project manager generated MAKEFILE
#
TITLE = sample
DEVFILE = C:\Program Files\NEC Electronics Tools\DEV\DF3716.800
PROJDIR = C:\cygwin\home\n-okada\hos\hos-v4\sample\v850es
TOOLDIR = C:\Program Files\NEC Electronics Tools\PM+\V6.31\BIN
WORKDIR = C:\cygwin\home\n-okada\hos\hos-v4\sample\v850es
DEBUG = 

CC	= "C:\Program Files\NEC Electronics Tools\CA850\W3.20\bin\ca850.exe"
CFLAGS	= -cpu F3716 -IC:\cygwin\home\n-okada\hos\hos-v4\include -DDEBUG -D__V850ES__ -Fs -Xcxxcom -Xpro_epi_runtime=off -Xr
AS	= "C:\Program Files\NEC Electronics Tools\CA850\W3.20\bin\as850.exe"
ASFLAGS	= -cpu F3716 -I C:\cygwin\home\n-okada\hos\hos-v4\include -g
LD	= "C:\Program Files\NEC Electronics Tools\CA850\W3.20\bin\ld850.exe"
LIBDIR	= C:\Program Files\NEC Electronics Tools\CA850\W3.20\lib850\r32
STARTUP	= crtE.o
DEP_STARTUP = 
LINKDIR	= C:\cygwin\home\n-okada\hos\hos-v4\sample\v850es\sample.dir
LDFLAGS	= -cpu F3716 -D $(LINKDIR)
LIBRARY	= "$(LIBDIR)\libh4v850es.a" \
	  "$(LIBDIR)\libm.a" \
	  "$(LIBDIR)\libc.a" \
	  "$(LIBDIR)\libr.a"
ROMPCRT	= "$(LIBDIR)\rompcrt.o"
LDLIBS	= -lh4v850es -lm -lc -lr $(ROMPCRT)
ROMP	= "C:\Program Files\NEC Electronics Tools\CA850\W3.20\bin\romp850.exe"
RPFLAGS	= 
HX	= "C:\Program Files\NEC Electronics Tools\CA850\W3.20\bin\hx850.exe"
HXFLAGS	= -o romp.hex

OBJS = ostimer.o  \
	sample.o  \
	kernel_cfg.o  \
	inthdr.o 

DEP_ostimer_c = C:\cygwin\home\n-okada\hos\hos-v4\include\kernel.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_hos.h \
	"C:\Program Files\NEC Electronics Tools\CA850\W3.20\inc850\stddef.h" \
	C:\cygwin\home\n-okada\hos\hos-v4\include\itron.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\mknl.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\hosdenv.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\arm\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\h83\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\sh\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\win\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\x86\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\pic.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\ia32gcc\linkage.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\ia32gcc\ioport.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\ia32gcc\hosexp.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\ia32gcc\descriptor.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\ia32gcc\switch.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\ia32gcc\idle.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\mips\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\v850es\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\hoserchk.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_mem.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_hep.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_tsk.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_sem.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_flg.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_dtq.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_mbx.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_mbf.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_mpf.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_mpl.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_tim.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_cyc.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_alm.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_sys.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_int.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_exc.h \
	C:\cygwin\home\n-okada\hos\hos-v4\sample\v850es\kernel_id.h \
	C:\cygwin\home\n-okada\hos\hos-v4\sample\v850es\ostimer.h \
	"C:\Program Files\NEC Electronics Tools\CA850\W3.20\inc850\stdio.h" \
	"C:\Program Files\NEC Electronics Tools\CA850\W3.20\inc850\stdarg.h"

DEP_sample_c = C:\cygwin\home\n-okada\hos\hos-v4\include\kernel.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_hos.h \
	"C:\Program Files\NEC Electronics Tools\CA850\W3.20\inc850\stddef.h" \
	C:\cygwin\home\n-okada\hos\hos-v4\include\itron.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\mknl.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\hosdenv.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\arm\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\h83\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\sh\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\win\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\x86\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\pic.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\ia32gcc\linkage.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\ia32gcc\ioport.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\ia32gcc\hosexp.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\ia32gcc\descriptor.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\ia32gcc\switch.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\ia32gcc\idle.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\mips\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\v850es\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\hoserchk.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_mem.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_hep.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_tsk.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_sem.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_flg.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_dtq.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_mbx.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_mbf.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_mpf.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_mpl.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_tim.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_cyc.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_alm.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_sys.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_int.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_exc.h \
	C:\cygwin\home\n-okada\hos\hos-v4\sample\v850es\kernel_id.h \
	C:\cygwin\home\n-okada\hos\hos-v4\sample\v850es\sample.h \
	"C:\Program Files\NEC Electronics Tools\CA850\W3.20\inc850\stdio.h" \
	"C:\Program Files\NEC Electronics Tools\CA850\W3.20\inc850\stdarg.h"

DEP_kernel_cfg_c = C:\cygwin\home\n-okada\hos\hos-v4\include\kernel.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_hos.h \
	"C:\Program Files\NEC Electronics Tools\CA850\W3.20\inc850\stddef.h" \
	C:\cygwin\home\n-okada\hos\hos-v4\include\itron.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\mknl.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\hosdenv.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\arm\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\h83\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\sh\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\win\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\x86\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\pic.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\ia32gcc\linkage.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\ia32gcc\ioport.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\ia32gcc\hosexp.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\ia32gcc\descriptor.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\ia32gcc\switch.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\ia32\ia32gcc\idle.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\mips\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\v850es\hospac.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\hoserchk.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_mem.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_hep.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_tsk.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_sem.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_flg.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_dtq.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_mbx.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_mbf.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_mpf.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_mpl.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_tim.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_cyc.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_alm.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_sys.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_int.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\knl_exc.h \
	C:\cygwin\home\n-okada\hos\hos-v4\sample\v850es\kernel_id.h \
	C:\cygwin\home\n-okada\hos\hos-v4\sample\v850es\sample.h \
	C:\cygwin\home\n-okada\hos\hos-v4\sample\v850es\ostimer.h \
	C:\cygwin\home\n-okada\hos\hos-v4\include\v850es\vect.h

DEP_inthdr_S = C:\cygwin\home\n-okada\hos\hos-v4\include\v850es\vectasm.inc

GOAL : C:\cygwin\home\n-okada\hos\hos-v4\sample\v850es\romp.out

BeforeBuild:		#ビルド前の処理(疑似ターゲット)
	C:\WINDOWS\system32\cmd.exe /c copy system.cfg system.c
	C:\WINDOWS\system32\cmd.exe /c "c:\Program Files\NEC Electronics Tools\CA850\W3.20\bin\ca850.exe" -Xcxxcom -P system.c
	C:\WINDOWS\system32\cmd.exe /c hos4cfg.exe system.i
	C:\WINDOWS\system32\cmd.exe /c del system.c system.i








ostimer.o : ostimer.c $(DEP_ostimer_c)
	$(CC) $(CFLAGS) -O -c ostimer.c

sample.o : sample.c $(DEP_sample_c)
	$(CC) $(CFLAGS) -O -c sample.c

kernel_cfg.o : kernel_cfg.c $(DEP_kernel_cfg_c)
	$(CC) $(CFLAGS) -O -c kernel_cfg.c

inthdr.o : inthdr.S $(DEP_inthdr_S)
	$(AS) $(ASFLAGS) inthdr.S

crtE.o : C:\cygwin\home\n-okada\hos\hos-v4\sample\v850es\crtE.s $(DEP_STARTUP)
	$(AS) -cpu F3716 -I C:\cygwin\home\n-okada\hos\hos-v4\include -g C:\cygwin\home\n-okada\hos\hos-v4\sample\v850es\crtE.s

romp.out : $(STARTUP) $(LINKDIR) $(OBJS) $(LIBRARY) $(ROMPCRT)
	$(LD) @sample.cld
	$(ROMP) $(RPFLAGS) a.out
	$(HX) $(HXFLAGS) romp.out

