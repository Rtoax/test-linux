
CFLAGS := -O0

all:
	gcc main.c ${CFLAGS} -S -o main.s
	gcc main.c ${CFLAGS} -S -pg -o main-pg.s

clean:
	rm -f *.s *.S *.out

