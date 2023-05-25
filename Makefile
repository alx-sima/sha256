# Copyright 2023 Iarina-Ioana Popa 

CFLAGS= -Wall -Wextra -std=c99 -g -MMD -MP
CC= gcc

TARGET = sha256sum
SRCS = $(wildcard *.c)

.PHONY: build documentation pack clean

build: $(TARGET)

$(TARGET): $(SRCS:.c=.o)
	$(CC) $(CFLAGS) -o $(TARGET) $^

documentation:
	make -C doc

pack: documentation
	zip -FSr proiect_pclp3.zip doc/documentatie.pdf test/test.sh Makefile *.c *.h

-include $(SRCS:.c=.d)

clean: 
	make -C doc clean
	rm -rf *.o $(TARGET)
