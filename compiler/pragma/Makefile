SHELL = bash
include ../../tlbuild.mk


TARGETS :=
TARGETS += GCC_error
TARGETS += GCC_poison
TARGETS += GCC_diagnostic
TARGETS += GCC_dependency
TARGETS += GCC_system_header
TARGETS += GCC_target
TARGETS += GCC_novector
TARGETS += GCC_unroll
TARGETS += GCC_ivdep
TARGETS += pragma-message
TARGETS += call-func
TARGETS += push_macro
TARGETS += message
TARGETS += _Pragma

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -Werror=unknown-pragmas
CFLAGS += -I../../
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

GCC_poison: GCC_poison.o
GCC_diagnostic: GCC_diagnostic.o
GCC_target: GCC_target.o
GCC_error: GCC_error.o
GCC_dependency: GCC_dependency.o
GCC_system_header: GCC_system_header.o
GCC_novector: GCC_novector.o
GCC_ivdep: GCC_ivdep.o
GCC_unroll: GCC_unroll.o
pragma-message: pragma-message.o
call-func: call-func.o
push_macro: push_macro.o
message: message.o
_Pragma: _Pragma.o

# TODO
CFLAGS_call-func := -Wno-unknown-pragmas
CFLAGS_GCC_system_header := -I./

# Use /etc/os-release file for GCC dependency check, if system upgraded,
# /etc/os-release could be newer than current source code, let's 'Warning',
# not 'error'.
CFLAGS_GCC_dependency := -Wno-error
CFLAGS__Pragma := -Wno-error

CFLAGS_GCC_diagnostic := -pg -Wno-error=pragmas -Wno-error=uninitialized

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	$(call print_elf,$(@))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDLIBS)
	$(call print_elf,$(@))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.out

