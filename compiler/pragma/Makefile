TARGETS :=
TARGETS += GCC_poison
TARGETS += GCC_diagnostic
TARGETS += GCC_dependency
TARGETS += GCC_system_header
TARGETS += pragma-message
TARGETS += call-func
TARGETS += push_macro
TARGETS += message
TARGETS += _Pragma

ifneq ($(shell uname -m),aarch64)
TARGETS += GCC_target
endif

ifneq ($(shell uname -m),x86_64)
TARGETS += GCC_error
endif

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
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
pragma-message: pragma-message.o
call-func: call-func.o
push_macro: push_macro.o
message: message.o
_Pragma: _Pragma.o

# TODO
CFLAGS_call-func := -Wno-unknown-pragmas
CFLAGS_GCC_system_header := -I./

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	$(call print_elf,$(@))

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDLIBS)
	$(call print_elf,$(@))

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.out

