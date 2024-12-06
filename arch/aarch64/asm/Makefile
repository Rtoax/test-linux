SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


CC = gcc
AS = as
LD = ld
OBJDUMP = objdump
RUN_PFX =
AS_ARGS :=
LDFLAGS :=

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
TARGETS_ASM += nanosleep

TARGETS_S :=

ifneq ($(shell lscpu | grep -w -e sve -e sve2),)
  TARGETS_ASM += hello_sve
  TARGETS_C += daxpy
  AS_ARGS := -march=armv8-a+sve2
endif

# Cross compile
# If cross compile, you could use binfmt_misc to running aarch64 on x86_64, ..
ifneq ($(shell uname -m),aarch64)
  CC = aarch64-linux-gnu-gcc
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
  TARGETS_C += nanosleep-c
  TARGETS_C += write-c write-c-loop
  TARGETS_C += exit-c

  TARGETS_ASM += branch

  TARGETS_S += main
  TARGETS_S += say_hello
  TARGETS_S += hello-puts
  TARGETS_S += hello-puts-infinite-loop
  TARGETS_S += hello-main
  TARGETS_S += read-main
  TARGETS_S += exit-main
  TARGETS_S += puts-main
  TARGETS_S += printf-main

  LDFLAGS += -lc
endif

ifdef STATIC
  CFLAGS += -static
  # Remove -lc
  LDFLAGS :=
  LDFLAGS += -static
  # FIXME: branch.asm no main() but call libc::printf(), I try 'gcc -nostdlib'
  # but it not works.
  TARGETS_ASM := $(filter-out branch, $(TARGETS_ASM))
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
main: main.o
hello-main: hello-main.o
read-main: read-main.o
exit-main: exit-main.o
puts-main: puts-main.o
printf-main: printf-main.o
say_hello: say_hello.o
exit: exit.o
nanosleep: nanosleep.o
hello_sve: hello_sve.o
daxpy: daxpy.o daxpy_sve.o daxpy-c.co
add-c: add-c.o
loop-c: loop-c.o
paciasp-c: paciasp-c.o
nanosleep-c: nanosleep-c.o
write-c: write-c.o
write-c-loop: write-c-loop.o
exit-c: exit-c.o
puts: puts.o
while: while.o
ldr: ldr.o
mov: mov.o

ASFLAGS_paciasp := -march=armv8.3-a
CFLAGS_paciasp-c := -march=armv8.3-a

CFLAGS_hello-puts-infinite-loop := -DINFINITE_LOOP=1
CFLAGS_write-c-loop := -DINFINITE_LOOP=1

%.o: %.asm
	@echo -e "  AS  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(AS) $(<) -o $(@) $(AS_ARGS) $(ASFLAGS_$(*))
	@$(OBJDUMP) -Dr $(@) > $(@).obj

%.co: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(<) -c -o $(@) $(CFLAGS) $(CFLAGS_$(*))

%.o: %.S
	@echo -e "  CC(S)  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(<) -c -o $(@) $(CFLAGS) $(CFLAGS_$(*))

%.o: %.c
	@echo -e "  CC(C)  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS_ASM): %:
	@echo -e "  LD(ASM)  \033[1;32m$(@)\033[m"
	@$(LD) -o $(@) $(^) $(LDFLAGS)

$(TARGETS_S) $(TARGETS_C): %:
	@echo -e "  LD(C,S)  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(CFLAGS)

test: $(TARGETS_ASM)
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	$(RUN_PFX) ./hello

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS_C) $(TARGETS_ASM) $(TARGETS_S)\033[m"
	${Q}rm -f ${TARGETS_ASM} ${TARGETS_S} ${TARGETS_C} *.o *.d core.* *.co *.obj
