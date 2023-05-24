# Copyright 2023 Iarina-Ioana Popa 

CFLAGS= -Wall -Wextra -g
CC= gcc
TARGET= sha256sum

build: io.o sha.o main.o bit_functions.o sha256_consts.o
	$(CC) $(CFLAGS) -o $(TARGET) $^

clean: 
	rm -rf *.o