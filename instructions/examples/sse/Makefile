
all:
	gcc sum.c -O3 -ftree-vectorize -msse -o sse
	gcc sum.c -O3 -ftree-vectorize -msse2 -o sse2
	gcc sum.c -O3 -ftree-vectorize -msse3 -o sse3
	gcc sum.c -O3 -ftree-vectorize -mssse3 -o ssse3
	gcc sum.c -O3 -ftree-vectorize -msse4.1 -o sse4.1
	gcc sum.c -O3 -ftree-vectorize -msse4.2 -o sse4.2
	gcc sum.c -O3 -ftree-vectorize -msse4 -o sse4

clean:
	rm -f sse sse2 sse3 ssse3 sse4.1 sse4.2 sse4
