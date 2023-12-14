TARGETS :=

ifeq ($(shell uname -m),aarch64)
TARGETS += add
TARGETS += branch
TARGETS += mov
endif

DYNAMIC_LINKER =
ifneq ($(wildcard /lib/ld-linux-aarch64.so.1),)
DYNAMIC_LINKER = /lib/ld-linux-aarch64.so.1
endif
ifneq ($(wildcard /lib64/ld-linux-aarch64.so.1),)
DYNAMIC_LINKER = /lib64/ld-linux-aarch64.so.1
endif

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
add: add.o
branch: branch.o
mov: mov.o

%.o: %.S
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	as $(<) -o $(@)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	ld -o $(@) $(^) -lc -I $(DYNAMIC_LINKER)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d
