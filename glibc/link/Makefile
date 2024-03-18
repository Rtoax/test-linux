CC = gcc

TARGETS := dl_iterate_phdr
TARGETS += has_shared_object

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

LDFLAGS :=
LDLIBS :=


.PHONY: build
build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

dl_iterate_phdr: dl_iterate_phdr.o
has_shared_object: has_shared_object.o

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o
