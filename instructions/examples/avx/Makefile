CFLAGS_ORIG += -DTYPE_FLOAT

CFLAGS :=
CFLAGS += -O0
#CFLAGS += -ftree-vectorize
CFLAGS += ${CFLAGS_ORIG}

all:
	gcc sum.c ${CFLAGS_ORIG} -o orig
	gcc sum.c ${CFLAGS} -mavx -o avx
	objdump -d avx > avx.out
	gcc sum.c ${CFLAGS} -mavx2 -o avx2
	objdump -d avx2 > avx2.out

clean:
	rm -f orig avx avx2 *.out
