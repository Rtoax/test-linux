
CFLAGS := -O3 -fprofile-generate -fprofile-arcs -ftest-coverage -lgcov
#LDFLAGS := -O3 -fprofile-arcs -lgcov
#LDFLAGS := -lgcov
LDFLAGS := -fprofile-arcs

all:
	gcc main.c $(CFLAGS) -c -o main.o
	gcc lib.c $(CFLAGS) -c -o lib.o
	ar rcs liblib.a lib.o
	gcc -fPIC -shared lib.c $(CFLAGS) -o liblib.so
	gcc main.o -o main.shared $(LDFLAGS) -L. -llib
	gcc main.o -o main.static $(LDFLAGS) liblib.a

clean:
	rm -f *.o main.shared main.static *.gcda *.gcno *.out *.so *.a
