include ../../tlbuild.mk


sub-dir := hacking

TARGETS := hello
TARGETS += socket
TARGETS += malloc
TARGETS += vdso
TARGETS += dlinfo

ifneq ($(shell uname -m),aarch64)
TARGETS += dlsym-RTLD_DEFAULT
endif

TARGETS_LIBS := libhello.so

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes
CFLAGS += -ldl

LDFLAGS :=
LDLIBS :=

ifdef DEBUG
  CFLAGS += -DDEBUG -O0 -g
endif

CFLAGS += -I../../

ifdef M32
  CFLAGS += -m32 -DM32=1
  LDFLAGS += -m32
  $(info Compile 32bit ELF)
endif

include ../../template/subdir-header.mk

.PHONY: build
build: ${TARGETS} ${TARGETS_LIBS} $(sub-dir-build)
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
hello: hello.o
socket: socket.o libc.o
malloc: malloc.o libc.o
vdso: vdso.o
dlinfo: dlinfo.o proc.o
dlsym-RTLD_DEFAULT: dlsym-RTLD_DEFAULT.o

proc.o: ../../libs/proc.o
	$(info We are in $(shell pwd))
	mv $(<) $(@)

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<) -fpic

%.so: %.o
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(<) -shared -fpic

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS} $(sub-dir-test)
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.so

include ../../template/subdir-footer.mk
