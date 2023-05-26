
all:
	gcc sum.c -O3 -ftree-vectorize -mavx -o avx
	gcc sum.c -O3 -ftree-vectorize -mavx2 -o avx2

clean:
	rm -f avx avx2
