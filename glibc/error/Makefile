TARGETS :=
TARGETS += error
TARGETS += error_print_progname
TARGETS += error_at_line

CC = gcc

all: ${TARGETS}

error: error.o
error_print_progname: error_print_progname.o
error_at_line: error_at_line.o

clean:
	rm -f *.o ${TARGETS}
