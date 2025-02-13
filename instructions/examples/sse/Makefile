include ../../../tlbuild.mk


# man gcc: GCC depresses SSEx instructions when -mavx is used

CFLAGS_ORIG += -DTYPE_FLOAT
CFLAGS :=
CFLAGS += -O1
CFLAGS += -ftree-vectorize
CFLAGS += ${CFLAGS_ORIG}

all:
	gcc sum.c $(CFLAGS_ORIG) -o orig
	gcc sum.c $(CFLAGS) -msse -o sse
	gcc sum.c $(CFLAGS) -msse2 -o sse2
	gcc sum.c $(CFLAGS) -msse3 -o sse3
	gcc sum.c $(CFLAGS) -mssse3 -o ssse3
	gcc sum.c $(CFLAGS) -msse4.1 -o sse4.1
	gcc sum.c $(CFLAGS) -msse4.2 -o sse4.2
	gcc sum.c $(CFLAGS) -msse4 -o sse4

clean:
	rm -f orig sse sse2 sse3 ssse3 sse4.1 sse4.2 sse4 *.out
