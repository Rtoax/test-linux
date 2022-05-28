
TARGET=filter-write.out

all: ${TARGET}

filter-write.out:
	gcc -o filter-write.out filter-write.c

run-filter-write: filter-write.out
	strace -f ./filter-write.out "ls -la"

clean:
	rm -f *.out
