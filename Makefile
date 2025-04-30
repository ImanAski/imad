
V =

ifeq ($(strip $(V)),)
	E = @echo
	Q = @
else
	E = @\#
	Q =
endif
export E Q

PROGRAM=em

SRC=main.c version.c

OBJ=main.o version.o

HDR=version.h edef.h efunc.h estruct.h

CC=gcc
WARNINGS=-Wall -Wstrict-prototypes
CFLAGS=-O2 $(WARNINGS) -g

BINDIR=./bin
LIBDIR=./lib

ifeq ($(uname_S),Linux)
 DEFINES=-DAUTOCONF -DPOSIX -DUSG -D_XOPEN_SOURCE=600 -D_GNU_SOURCE
endif

LIBS=-lcurses			# SYSV

LFLAGS=-hbx

$(PROGRAM): $(OBJ)
	$(E) "  LINK   " $@
	$(Q) $(CC) $(LDFLAGS) $(DEFINES) -o $@ $(OBJ) $(LIBS)


clean:
	$(E) "  CLEAN"
	$(Q) rm -f $(PROGRAM) *.o

