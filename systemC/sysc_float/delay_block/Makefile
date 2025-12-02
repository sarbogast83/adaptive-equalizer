TARGET_ARCH = linux64

CC     = g++
OPT    = -O3
WARNH    = -Wno-deprecated
WARNSC    = -Wno-char-subscripts
WARNMSG	  = -Wno-return-type
DEBUG  = -g
OTHER  = -Wall
# CFLAGS = $(OPT) $(OTHER)
CFLAGS = $(DEBUG) $(OPT) $(OTHER) $(WARNH) $(WARNSC) $(WARNMSG)

MODULE = runDelayBlock
SRCS = dff.cc test_delayBlock.cc

OBJS = $(SRCS:.cc=.o)

include ./Makefile.defs
