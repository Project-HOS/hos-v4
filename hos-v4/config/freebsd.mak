# Makefile for FreeBSD
# $Id$
PROG  = hos4cfg
SRCS  =	analize.cpp	apidef.cpp	apiinc.cpp	attini.cpp	\
	attisr.cpp	crecyc.cpp	credtq.cpp	creflg.cpp	\
	crembf.cpp	crembx.cpp	crempf.cpp	cresem.cpp	\
	cretsk.cpp	defercd.cpp	defexc.cpp	deftex.cpp	\
	hos4cfg.cpp	knlheap.cpp	maxtmout.cpp	maxtpri.cpp	\
	parpack.cpp	read.cpp 	timtic.cpp

NOMAN =
CFLAGS += -Wall

.include <bsd.prog.mk>
	