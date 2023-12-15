CC = gcc
AS = as
LD = ld
RUN_PFX =
AS_ARGS :=

TARGETS_C :=
TARGETS := hello
TARGETS += hello-stack

ifneq ($(shell lscpu | grep -w -e sve -e sve2),)
	TARGETS += hello_sve
	TARGETS_C += daxpy
	AS_ARGS := -march=armv8-a+sve2
endif

ifneq ($(shell uname -m),aarch64)
	AS = aarch64-linux-gnu-as
	LD = aarch64-linux-gnu-ld
	RUN_PFX = qemu-aarch64
endif

DYNAMIC_LINKER =
ifneq ($(wildcard /lib/ld-linux-aarch64.so.1),)
DYNAMIC_LINKER = /lib/ld-linux-aarch64.so.1
endif
ifneq ($(wildcard /lib64/ld-linux-aarch64.so.1),)
DYNAMIC_LINKER = /lib64/ld-linux-aarch64.so.1
endif

.PHONY: build
build: $(TARGETS) $(TARGETS_C)
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
hello: hello.o
hello-stack: hello-stack.o
hello_sve: hello_sve.o
daxpy: daxpy.o daxpy_sve.o daxpy-c.co

%.o: %.asm
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(AS) $(<) -o $(@) $(AS_ARGS)

%.co: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(<) -c -o $(@) $(CFLAGS)

$(TARGETS): %.o:
	@echo -e "Target ld \033[1;32m$(@)\033[m"
	$(LD) -o $(@) $(^) -lc -I ${DYNAMIC_LINKER}

$(TARGETS_C): %.o:
	@echo -e "Target ld \033[1;32m$(@)\033[m"
	$(CC) -o $(@) $(^)

test: $(TARGETS)
	@echo -e "Test   \033[1;32m$(@)\033[m"
	$(RUN_PFX) ./hello

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} ${TARGETS_C} *.o *.d core.* *.co
