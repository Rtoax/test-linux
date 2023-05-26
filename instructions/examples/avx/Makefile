CFLAGS :=
CFLAGS += -O3
CFLAGS += -ftree-vectorize
CFLAGS += -DTYPE_FLOAT

all:
	gcc sum.c ${CFLAGS} -mavx -o avx
	gcc sum.c ${CFLAGS} -mavx2 -o avx2

clean:
	rm -f avx avx2
