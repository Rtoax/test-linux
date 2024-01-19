CC = gcc
AS = as
LD = ld
RUN_PFX =
AS_ARGS :=

CFLAGS :=

CFLAGS += -O0 -g -ggdb

TARGETS_C :=
TARGETS_C += add-c
TARGETS_C += loop-c
TARGETS_C += puts

TARGETS_ASM := hello
TARGETS_ASM += hello-stack
TARGETS_ASM += exit
TARGETS_ASM += ldr
TARGETS_ASM += while

TARGETS_S :=
TARGETS_S += say_hello
TARGETS_S += hello-puts
TARGETS_S += hello-puts-infinite-loop

ifneq ($(shell lscpu | grep -w -e sve -e sve2),)
	TARGETS_ASM += hello_sve
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
build: $(TARGETS_ASM) $(TARGETS_C) $(TARGETS_S)
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
hello: hello.o
hello-stack: hello-stack.o
hello-puts: hello-puts.o
hello-puts-infinite-loop: hello-puts-infinite-loop.o
say_hello: say_hello.o
exit: exit.o
hello_sve: hello_sve.o
daxpy: daxpy.o daxpy_sve.o daxpy-c.co
add-c: add-c.o
loop-c: loop-c.o
puts: puts.o
while: while.o
ldr: ldr.o

CFLAGS_hello-puts-infinite-loop := -DINFINITE_LOOP=1

%.o: %.asm
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(AS) $(<) -o $(@) $(AS_ARGS)
	objdump -Dr $(@)

%.co: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(<) -c -o $(@) $(CFLAGS) $(CFLAGS_$(*))

%.o: %.S
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(<) -c -o $(@) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS_ASM): %.o:
	@echo -e "Target ld \033[1;32m$(@)\033[m"
	$(LD) -o $(@) $(^) -lc -I ${DYNAMIC_LINKER}

$(TARGETS_S) $(TARGETS_C): %.o:
	@echo -e "Target ld \033[1;32m$(@)\033[m"
	$(CC) -o $(@) $(^)

test: $(TARGETS_ASM)
	@echo -e "Test   \033[1;32m$(@)\033[m"
	$(RUN_PFX) ./hello

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS_ASM} ${TARGETS_S} ${TARGETS_C} *.o *.d core.* *.co
