include ../../../../tlbuild.mk



all:
	gcc -o main main.c sm4_aesni_x4.c sm4.c -Og -msse4 -maes
clean:
	rm -f main
