
TARGETS := hello
TARGETS += hello-stack

AS = as
LD = ld
RUN_PFX =

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

%.o: %.asm
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(AS) $(<) -o $(@)

$(TARGETS): %.o:
	@echo -e "Target ld \033[1;32m$(@)\033[m"
	$(LD) -o $(@) $(^)

test: $(TARGETS)
	@echo -e "Test   \033[1;32m$(@)\033[m"
	$(RUN_PFX) ./hello

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d core.*
