

all: compile run gcov html

compile:
	@echo "[compile]---------------------------------------"
	gcc -fprofile-arcs -ftest-coverage -o test test.c

asm:
	@echo "[make assembler]----------------------------------"
	gcc test.c -S -o test.s
	gcc test.c -S -o test-gcov.s -ftest-coverage -fprofile-arcs
	diff -up test.s test-gcov.s

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

