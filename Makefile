    CC = gcc
CFLAGS = -Wall -Wreturn-type -O2

PROGRAM_LENGTH   = wpalength
PROGRAM_DATE     = wpadate
PROGRAM_HASHWORD = wpahashword

# IF install

PERC            = /usr/local/bin/

#LIBS FOR PROGRAMM

LIB_WRITE_FILE= src/lib/wpahashword/write_file.c
LIB_ESSENTIAL = src/lib/essential.c
LIB_OUTERR    = src/lib/outerr.c
LIB_OUTPRINT  = src/lib/wpalength/outprint.c
LIB_DIMINUTIVI= src/lib/wpahashword/diminutivi.c

all:

	$(CC) $(CLFAGS) src/length.c $(LIB_ESSENTIAL) $(LIB_OUTERR) $(LIB_OUTPRINT) -o $(PROGRAM_LENGTH)

	$(CC) $(CLFAGS) src/date.c $(LIB_ESSENTIAL) $(LIB_OUTERR) -o $(PROGRAM_DATE)

	$(CC) $(CLFAGS) src/hashword.c $(LIB_ESSENTIAL) $(LIB_OUTERR) $(LIB_WRITE_FILE) $(LIB_DIMINUTIVI) -o $(PROGRAM_HASHWORD)
install:

	mv $(PROGRAM_HASHWORD) $(PERC)
	mv $(PROGRAM_DATE)     $(PERC)
	mv $(PROGRAM_LENGTH)   $(PERC)

	@echo
	@echo "Installation Succesfully"

unistall:

	rm $(PERC)$(PROGRAM_HASHWORD)
	rm $(PERC)$(PROGRAM_LENGTH)
	rm $(PERC)$(PROGRAM_DATE)

	@echo
	@echo "Disinstallation Completed"
