TARGETS :=
TARGETS += sysinfo
TARGETS += get_avphys_pages get_phys_pages
TARGETS += get_nprocs get_nprocs_conf

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -I../../../
CFLAGS += -lm
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
sysinfo: sysinfo.o
get_avphys_pages: get_avphys_pages.o
get_phys_pages: get_phys_pages.o
get_nprocs: get_nprocs.o
get_nprocs_conf: get_nprocs_conf.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d
