TARGETS :=
TARGETS += vasprintf
TARGETS += vfprintf
TARGETS += vsprintf
TARGETS += puts
TARGETS += __freadable
TARGETS += open_memstream
TARGETS += remove
TARGETS += popen

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -I../../../
CFLAGS += -lm
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
vasprintf: vasprintf.o
vfprintf: vfprintf.o
vsprintf: vsprintf.o
puts: puts.o
__freadable: __freadable.o
open_memstream: open_memstream.o
remove: remove.o
popen: popen.o

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.log *.out
