include ../../tlbuild.mk


sub-dir := breakfast

TARGETS :=
ifeq ($(shell uname -m),x86_64)
TARGETS += int3
endif
ifeq ($(shell uname -m),aarch64)
TARGETS += brk
endif

include ../../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build) $(TARGETS)

int3: int3.o
brk: brk.o

.PHONY: clean
clean: $(sub-dir-clean)
	rm -f $(TARGETS) *.o

include ../../template/subdir-footer.mk
