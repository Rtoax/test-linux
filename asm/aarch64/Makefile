CC = gcc
AS = as
LD = ld
RUN_PFX =
AS_ARGS :=

TARGETS := hello
TARGETS += hello-stack

ifneq ($(shell lscpu | grep -w -e sve -e sve2),)
	TARGETS += hello_sve
	TARGETS += daxpy
	AS_ARGS := -march=armv8-a+sve2
endif

ifneq ($(shell uname -m),aarch64)
	AS = aarch64-linux-gnu-as
	LD = aarch64-linux-gnu-ld
	RUN_PFX = qemu-aarch64
endif

.PHONY: build
build: $(TARGETS)
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
hello: hello.o
hello-stack: hello-stack.o
hello_sve: hello_sve.o
daxpy: daxpy.o daxpy-c.co

%.o: %.asm
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(AS) $(<) -o $(@) $(AS_ARGS)

%.co: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(<) -c -o $(@) $(CFLAGS)

$(TARGETS): %.o:
	@echo -e "Target ld \033[1;32m$(@)\033[m"
	$(LD) -o $(@) $(^)

test: $(TARGETS)
	@echo -e "Test   \033[1;32m$(@)\033[m"
	$(RUN_PFX) ./hello

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d core.* *.co
