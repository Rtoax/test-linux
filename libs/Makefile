# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk

include ../kconfig.mk

sub-dir := readline

TARGETS_LIBSO :=
TARGETS_LIBA :=
TARGETS :=
CFLAGS :=

TARGETS += byteswap
TARGETS += endian
TARGETS += file
TARGETS += fd
TARGETS += gotoxy goprint
TARGETS += log
TARGETS += memshow
TARGETS += mac
TARGETS += proc_examples
TARGETS += progress
TARGETS += str
TARGETS += ipaddr

LIB_OBJS := ipaddr.obj proc.obj readline.obj

TARGETS_LIBSO += libtest-linux-c.so
TARGETS_LIBA += libtest-linux-c.a

CC = gcc

CFLAGS += -Werror -Wall
ifdef DEBUG
  CFLAGS += -DDEBUG -O0 -g -ggdb
endif
CFLAGS += -DTEST=1
ifeq (${CONFIG_ANON_VMA_NAME},y)
  $(info INFO: Support CONFIG_ANON_VMA_NAME)
  CFLAGS += -DCONFIG_ANON_VMA_NAME=1
endif

ifdef LINK_LIB
  CFLAGS += -ltest-linux-c
  LDFLAGS += libtest-linux-c.so
endif

include ../elf/pie.mk

sub-dir-build := $(addprefix $(shell pwd)/,$(sub-dir:=.build))
sub-dir-clean := $(addprefix $(shell pwd)/,$(sub-dir:=.clean))

.PHONY: build
build: ${TARGETS_LIBSO} ${TARGETS_LIBA} ${TARGETS} $(sub-dir-build)
	@echo -e " \033[1;33m Done \033[m"

byteswap: byteswap.o
endian: endian.o
gotoxy: gotoxy.o
goprint: goprint.o
file: file.o
fd: fd.o
log: log.o
memshow: memshow.o
mac: mac.o
progress: progress.o
proc_examples: proc_examples.o proc.o
str: str.o
ipaddr: ipaddr.o

libtest-linux-c.so: ${LIB_OBJS}
libtest-linux-c.a: ${LIB_OBJS}

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@LD_LIBRARY_PATH=$(shell pwd) $(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

%.obj: %.c
	@echo -e "  CC OBJ  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*)) -fPIC

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@LD_LIBRARY_PATH=$(shell pwd) $(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*))

$(TARGETS_LIBSO): %:
	@echo -e "  SO  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) -shared -fPIC $(LDFLAGS_SO) $(LDFLAGS_SO_$(*))

$(TARGETS_LIBA): %:
	@echo -e "  AR  \033[1;32m$(^) to $(@)\033[m"
	@ar rcs $(@) $(^)

.PHONY: test
test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	${Q}LD_LIBRARY_PATH=$(shell pwd) ./byteswap
	${Q}clear
	${Q}./gotoxy
	${Q}clear


.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS) ${TARGETS_LIBSO} ${TARGETS_LIBA}\033[m"
	${Q}rm -f ${TARGETS} ${TARGETS_LIBSO} ${TARGETS_LIBA} *.o *.obj vdso.elf*

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	${Q}make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	${Q}make -C $(@:.clean=) clean

