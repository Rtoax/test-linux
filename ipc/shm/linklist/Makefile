#
# 2021-08-02	Rong Tao	Create this.

INC = -I.
LIB = mlinklist.c
GDB = -g -ggdb

all:
	gcc consumer.c ${LIB} ${INC} ${GDB} -o consumer
	gcc producer.c ${LIB} ${INC} ${GDB} -o producer

clean:
	rm -f consumer producer test.mmap
