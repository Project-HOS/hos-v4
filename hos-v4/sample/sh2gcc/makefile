

CC     = sh-hms-gcc
ASM    = sh-hms-gcc
LINK   = sh-hms-ld
OBJCNV = sh-hms-objcopy

TARGET = sample

CFLAGS = -c -m2 -I../../include
AFLAGS = -c -m2
LFLAGS = -v -t -nostartfiles -Map sample.map -Tsample.x

INCS   = kernel_id.h sample.h sci.h
OBJS   = crt0.o vector.o sample.o sci.o kernel_cfg.o
LIBS   = ../../lib/sh/sh2gcc/h4sh2gcc.a

${TARGET}.mot: ${OBJS} sample.x
	${LINK} ${LFLAGS} -o ${TARGET}.out ${OBJS} ${LIBS}
	${OBJCNV} -O srec ${TARGET}.out ${TARGET}.mot

vector.o: vector.s
	${ASM} ${AFLAGS} vector.s -o vector.o

crt0.o: crt0.s
	${ASM} ${AFLAGS} crt0.s -o crt0.o

sample.o: sample.c ${INCS}
	${CC} ${CFLAGS} sample.c -o sample.o

sci.o: sci.c sci.h
	${CC} ${CFLAGS} sci.c -o sci.o

kernel_cfg.o: kernel_cfg.c ${INCS}
	${CC} ${CFLAGS} kernel_cfg.c -o kernel_cfg.o

kernel_cfg.c kernel_id.h: system.cfg
	cp system.cfg system_tmp.c
	${CC} -E system_tmp.c -o system.i
	hos4cfg system.i
	rm system.i
	rm system_tmp.c
#	cpp system.cfg > system.i
#	hos4cfg system.i
#	rm system.i


clean:
	rm -f *.mot
	rm -f *.out
	rm -f *.o
	rm -f kernel_id.h
	rm -f kernel_cfg.c
