# Makefile for FreeBSD
# $Id$
PROG  = hos4cfg
SRCS  =	hos4cfg.cpp	analyze.cpp	apidef.cpp	apiinc.cpp	\
	attini.cpp	attisr.cpp	crecyc.cpp	credtq.cpp	\
	creflg.cpp	crembf.cpp	crembx.cpp	crempf.cpp	\
	cresem.cpp	cretsk.cpp	defercd.cpp	defexc.cpp	\
	deftex.cpp	idlstk.cpp	intstk.cpp	knlheap.cpp	\
	maxtpri.cpp	parpack.cpp	read.cpp	timtic.cpp

NOMAN =
CFLAGS += -Wall
#BINDIR = /usr/local/bin

.include <bsd.prog.mk>
	