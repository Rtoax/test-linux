SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q



all:
	# clang is ok too
	gcc main.c -pg -g -ggdb -O0
	./a.out
	gprof ./a.out gmon.out | gprof2dot > a.dot
	dot -Tpng a.dot -o a.png
	dot -Tsvg a.dot -o a.svg

clean:
	rm -f *.out *.dot *.png *.svg
