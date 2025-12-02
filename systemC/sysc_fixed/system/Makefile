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

MODULE = runAEtop
SRCS =  add16.cc add32.cc mult16.cc driver.cc sub16.cc scdl.cc test_AEtop.cc 

OBJS = $(SRCS:.cc=.o)

include ./Makefile.defs
