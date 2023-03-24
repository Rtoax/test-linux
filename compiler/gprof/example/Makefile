
all:
	# clang is ok too
	gcc example.c -pg -g -ggdb -O0
	./a.out
	gprof ./a.out gmon.out | gprof2dot | dot -Tpng -o a.png

clean:
	rm -f *.out *.png
