CC = gcc
AS = as
LD = ld
OBJDUMP = objdump
RUN_PFX =
AS_ARGS :=
LD_ARGS :=

CFLAGS :=

CFLAGS += -O0 -g -ggdb

TARGETS_C :=

TARGETS_ASM := hello
TARGETS_ASM += hello-stack
TARGETS_ASM += paciasp
TARGETS_ASM += exit
TARGETS_ASM += ldr
TARGETS_ASM += while
TARGETS_ASM += add
TARGETS_ASM += mov

TARGETS_S :=

ifneq ($(shell lscpu | grep -w -e sve -e sve2),)
	TARGETS_ASM += hello_sve
	TARGETS_C += daxpy
	AS_ARGS := -march=armv8-a+sve2
endif

# Cross compile
# If cross compile, you could use binfmt_misc to running aarch64 on x86_64, ..
ifneq ($(shell uname -m),aarch64)
	AS = aarch64-linux-gnu-as
	LD = aarch64-linux-gnu-ld
	OBJDUMP = aarch64-linux-gnu-objdump
	RUN_PFX = qemu-aarch64
endif
ifeq ($(shell uname -m),aarch64)
	TARGETS_C += add-c
	TARGETS_C += loop-c
	TARGETS_C += puts
	TARGETS_C += paciasp-c

	TARGETS_ASM += branch

	TARGETS_S += say_hello
	TARGETS_S += hello-puts
	TARGETS_S += hello-puts-infinite-loop

	LD_ARGS := -lc
endif

.PHONY: build
build: $(TARGETS_ASM) $(TARGETS_C) $(TARGETS_S)
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
add: add.o
branch: branch.o
hello: hello.o
hello-stack: hello-stack.o
paciasp: paciasp.o
hello-puts: hello-puts.o
hello-puts-infinite-loop: hello-puts-infinite-loop.o
say_hello: say_hello.o
exit: exit.o
hello_sve: hello_sve.o
daxpy: daxpy.o daxpy_sve.o daxpy-c.co
add-c: add-c.o
loop-c: loop-c.o
paciasp-c: paciasp-c.o
puts: puts.o
while: while.o
ldr: ldr.o
mov: mov.o

CFLAGS_hello-puts-infinite-loop := -DINFINITE_LOOP=1

%.o: %.asm
	@echo -e "  CC(asm)  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(AS) $(<) -o $(@) $(AS_ARGS)
	@$(OBJDUMP) -Dr $(@)

%.co: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(<) -c -o $(@) $(CFLAGS) $(CFLAGS_$(*))

%.o: %.S
	@echo -e "  CC(S)  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(<) -c -o $(@) $(CFLAGS) $(CFLAGS_$(*))

%.o: %.c
	@echo -e "  CC(C)  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS_ASM): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(LD) -o $(@) $(^) $(LD_ARGS)

$(TARGETS_S) $(TARGETS_C): %:
	@echo -e "  LD  ld \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^)

test: $(TARGETS_ASM)
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	$(RUN_PFX) ./hello

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS_C) $(TARGETS_ASM) $(TARGETS_S)\033[m"
	@rm -f ${TARGETS_ASM} ${TARGETS_S} ${TARGETS_C} *.o *.d core.* *.co
