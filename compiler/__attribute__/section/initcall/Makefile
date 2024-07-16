SHELL = bash


SRC := main.c init.c

all: ${SRC} ld.lds
	gcc ${SRC} -Wl,-Tld.lds -o test

clean:
	rm -f test *.o
