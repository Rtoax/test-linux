SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q



all:
	gcc -fPIC -shared mcount-nop.c -o libmcount-nop.so
	gcc main.c -pg -o main

run: main libmcount-nop.so
	LD_PRELOAD=./libmcount-nop.so ./main

clean:
	rm -f main libmcount-nop.so
