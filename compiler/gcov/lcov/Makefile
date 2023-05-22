

all:test run

test:
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
	@echo "[gcov test.c]---------------------------------------"
	gcov test.c
	@echo "[show]----------------------------------------"
	cat test.c.gcov | sed 's/^/>>  /'
	@echo "[gcov dump]----------------------------------------"
	gcov-dump test.gcda
	gcov-dump test.gcno
	@echo "[gen html]--------------------------------------"
	lcov -c -d . -o test.info
	genhtml -o html test.info

clean:
	rm -rf test test.gcda *.gcno test.c.gcov test.info html *.s

