# Makefile for FreeBSD
# $Id$
PROG  = hos4cfg
SRCS =	hos4cfg.cpp	analyze.cpp	parpack.cpp	read.cpp	\
	defercd.cpp	intstk.cpp	idlstk.cpp	knlheap.cpp	\
	maxtpri.cpp	apidef.cpp	apiinc.cpp	cretsk.cpp	\
	deftex.cpp	cresem.cpp	creflg.cpp	credtq.cpp	\
	crembx.cpp	crempf.cpp	crembf.cpp	timtic.cpp	\
	crecyc.cpp	crealm.cpp	defexc.cpp	attini.cpp	\
	attisr.cpp

NOMAN =
CFLAGS += -Wall
#BINDIR = /usr/local/bin

.include <bsd.prog.mk>
	