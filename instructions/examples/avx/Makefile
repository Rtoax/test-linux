CFLAGS_ORIG += -DTYPE_FLOAT

CFLAGS :=
CFLAGS += -O0
CFLAGS += -ftree-vectorize
CFLAGS += ${CFLAGS_ORIG}

all:
	gcc sum.c ${CFLAGS_ORIG} -o orig
	gcc sum.c ${CFLAGS} -mavx -o avx
	gcc sum.c ${CFLAGS} -mavx2 -o avx2

clean:
	rm -f orig avx avx2
