SHELL = bash
include ../../../tlbuild.mk


TARGETS :=

CLANG = $(shell which clang 2>/dev/null)

ifeq ($(CLANG),)
  $(warning Not found clang, please install clang first)
else
  TARGETS += main
endif

CC = ${CLANG}

CFLAGS := -O0 -Wall
CFLAGS += -Wno-override-module

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
main: main.ll

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^)

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d
