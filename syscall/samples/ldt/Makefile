TARGETS :=
ifeq ($(shell uname -m),x86_64)
TARGETS += get_thread_area
TARGETS += set_thread_area
TARGETS += modify_ldt
endif

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
get_thread_area: get_thread_area.o
set_thread_area: set_thread_area.o
modify_ldt: modify_ldt.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.txt
