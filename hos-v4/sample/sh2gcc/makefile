

CC     = sh-hms-gcc
ASM    = sh-hms-gcc
LINK   = sh-hms-ld
OBJCNV = sh-hms-objcopy

TARGET = sample

CFLAGS = -c -g -v -O0 -m2 -I../../include
AFLAGS = -c -g -v -O0 -m2
LFLAGS = -v -t -nostartfiles -Map sample.map -Tsample.x

INCS   = kernel_id.h test.h
OBJS   = vector.o crt0.o main.o test.o kernel_cfg.o
LIBS   = ../../lib/sh/h4sh2gcc.a

${TARGET}.mot: ${OBJS}
	${LINK} ${LFLAGS} -o ${TARGET}.out ${OBJS} ${LIBS}
	${OBJCNV} -O srec ${TARGET}.out ${TARGET}.mot

vector.o: vector.s
	${ASM} ${AFLAGS} vector.s -o vector.o

crt0.o: crt0.s
	${ASM} ${AFLAGS} crt0.s -o crt0.o

main.o: main.c ${INCS}
	${CC} ${CFLAGS} main.c -o main.o

kernel_cfg.o: kernel_cfg.c ${INCS}
	${CC} ${CFLAGS} kernel_cfg.c -o kernel_cfg.o

kernel_cfg.c kernel_id.h: system.cfg
	cp system.cfg system_tmp.c
	${CC} -E system_tmp.c -o system.i
	hos4cfg system.i


clean:
	rm -f *.mot
	rm -f *.out
	rm -f *.o
