## Copyright (C) 2023 Iarina-Ioana Popa (312CA) ##

CFLAGS = -Wall -Wextra -std=c99 -g -MMD -MP
CC = gcc

TARGET = sha256sum
README = documentatie.pdf
SRCS = $(wildcard *.c)

.PHONY: build clean doc test pack

build: $(TARGET)

$(TARGET): $(SRCS:.c=.o)
	$(CC) $(CFLAGS) -o $(TARGET) $^

# genereaza documentatia folosind makefileul din directorul doc
doc: doc/$(README)
	make -C doc

test: $(TARGET)
	./test_stdin.sh $(TARGET) /bin/sha256sum && \
	./test_files.rb $(TARGET) /bin/sha256sum

pack: test doc
	cp doc/$(README) .
	zip -FSr proiect_pclp3.zip $(README) Makefile *.c *.h test_*.{sh,rb}
	rm -f $(README)

# include fisierele .d generate de compilator care contin dependentele
-include $(SRCS:.c=.d)

clean: 
	make -C doc clean
	rm -rf *.o $(TARGET)
