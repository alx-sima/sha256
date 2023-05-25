# Copyright 2023 Iarina-Ioana Popa 

CFLAGS= -Wall -Wextra -g
CC= gcc
TARGET= sha256sum

.PHONY: build documentation pack clean

build: io.o sha.o main.o bit_functions.o sha256_consts.o
	$(CC) $(CFLAGS) -o $(TARGET) $^

documentation:
	make -C doc

pack: documentation
	zip -FSr proiect_pclp3.zip doc/documentatie.pdf Makefile *.c *.h

clean: 
	make -C doc clean
	rm -rf *.o $(TARGET)
