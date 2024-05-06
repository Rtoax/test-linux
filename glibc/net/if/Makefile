TARGETS :=
TARGETS += if_indextoname
TARGETS += if_nametoindex
TARGETS += if_nameindex

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

LDFLAGS :=
LDLIBS :=


.PHONY: build
build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

if_indextoname: if_indextoname.o
if_nametoindex: if_nametoindex.o
if_nameindex: if_nameindex.o

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o
