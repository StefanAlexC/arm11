CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

.SUFFIXES: .c .o

.PHONY: all clean

all: assemble emulate

assemble: assemble.o

emulate: emulate.o execute/$(wildcard *.o) decode/$(wildcard *.o)

clean:
	rm -f $(wildcard *.o)
	rm -f assemble:q
	rm -f emulate
