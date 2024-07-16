SHELL = bash

CC = gcc

TARGETS := symcache

CFLAGS := -lbcc
LDFLAGS := -lbcc

all: $(TARGETS)

symcache: symcache.o

clean:
	rm -f *.o $(TARGETS)

