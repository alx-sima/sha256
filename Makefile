# Copyright 2023 Iarina-Ioana Popa 

CFLAGS= -Wall -Wextra -g
CC= gcc
TARGET= test

build: io.o sha.o main.o bit_functions.o
	$(CC) $(CFLAGS) -o $(TARGET) $^

clean: 
	rm -rf *.o