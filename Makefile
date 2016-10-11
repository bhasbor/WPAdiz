    CC = gcc
CFLAGS = -Wall -O2

PROGRAM_LENGTH   = wpalength
PROGRAM_DATE     = wpadate
PROGRAM_HASHWORD = wpahashword

#DIR FOR BINARY

OUT = bin

#LIBS FOR PROGRAMM

LIB_TOLOWER   = src/lib/tolower.c
LIB_ESSENTIAL = src/lib/essential.c
LIB_OUTERR    = src/lib/outerr.c
LIB_OUTPRINT  = src/lib/wpalength/outprint.c
LIB_DIMINUTIVI= src/lib/wpahashword/diminutivi.c

all:
	mkdir $(OUT)

	$(CC) $(CLFAGS) src/length.c $(LIB_ESSENTIAL) $(LIB_OUTERR) $(LIB_OUTPRINT) -o $(OUT)/$(PROGRAM_LENGTH)

	$(CC) $(CLFAGS) src/date.c $(LIB_ESSENTIAL) $(LIB_OUTERR) -o $(OUT)/$(PROGRAM_DATE)

	$(CC) $(CLFAGS) src/hashword.c $(LIB_ESSENTIAL) $(LIB_OUTERR) $(LIB_TOLOWER) $(LIB_DIMINUTIVI) -o $(OUT)/$(PROGRAM_HASHWORD)
