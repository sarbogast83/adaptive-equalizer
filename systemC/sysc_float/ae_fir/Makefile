TARGET_ARCH = linux64
#TARGET_ARCH = cygwin64

CC     = g++
OPT    = -O3
WARNH    = -Wno-deprecated
WARNSC    = -Wno-char-subscripts
WARNMSG	  = -Wno-return-type
DEBUG  = -g
OTHER  = -Wall
# CFLAGS = $(OPT) $(OTHER)
CFLAGS = $(DEBUG) $(OPT) $(OTHER) $(WARNH) $(WARNSC) $(WARNMSG)

MODULE = runAE_fitler
SRCS = dff.cc add.cc mult.cc driver.cc test_FIR_filter.cc

OBJS = $(SRCS:.cc=.o)

include ./Makefile.defs
