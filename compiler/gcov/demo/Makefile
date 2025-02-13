SHELL = bash
include ../../../tlbuild.mk




all: compile run gcov html

compile:
	@echo "[compile]---------------------------------------"
	gcc -fprofile-arcs -ftest-coverage -o test test.c

asm:
	@echo "[make assembler]----------------------------------"
	gcc test.c -S -o test-orig.s
	gcc test.c -S -o test-arcs.s -fprofile-arcs
	gcc test.c -S -o test-arcs-test.s -ftest-coverage -fprofile-arcs
	gcc test.c -S -o test-values.s -fprofile-values
	gcc test.c -S -o test-gen.s -fprofile-generate

run:
	@echo "[execute]---------------------------------------"
	./test

gcov:
	@echo "[gcov test.c]---------------------------------------"
	# generate test.c.gcov if no --stdout
	gcov test.c --stdout

gcov-dump:
	@echo "[gcov dump gcda]----------------------------------------"
	gcov-dump test.gcda
	@echo "[gcov dump gcno]----------------------------------------"
	gcov-dump test.gcno

html:
	@echo "[gen html]--------------------------------------"
	lcov -c -d . -o test.info
	genhtml -o html test.info

clean:
	rm -rf test test.gcda *.gcno test.c.gcov test.info html *.s

