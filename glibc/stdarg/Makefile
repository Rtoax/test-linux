TARGETS := delete_files
TARGETS += sum_int
TARGETS += __VA_ARGS__
TARGETS += va_arg
TARGETS += va_start

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

delete_files: delete_files.o
sum_int: sum_int.o
__VA_ARGS__: __VA_ARGS__.o
va_arg: va_arg.o
va_start: va_start.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o

