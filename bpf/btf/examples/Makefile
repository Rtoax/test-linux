# ref: https://www.kernel.org/doc/html/latest/bpf/btf.html
# 6. BTF Generation

include ../../../tlbuild.mk

PAHOLE := $(shell which pahole 2>/dev/null || true)

TARGETS :=

ifneq ($(PAHOLE),)
  TARGETS += t1 t2 t2.s
else
  $(warning Not support pahole, install dwarves)
endif

all: ${TARGETS}

t1:
	@echo -e "  T1  \033[1;32m$(@)\033[m"
	$(Q)gcc -c -O2 -g t.c
	$(Q)pahole -JV t.o

t2:
	@echo -e "  T2  \033[1;32m$(@)\033[m"
	$(Q)clang -c -g -O2 -target bpf t2.c
	$(Q)readelf -S t2.o > t2.o.readelf

t2.s:
	@echo -e "  T2.s  \033[1;32m$(@)\033[m"
	$(Q)clang -S -g -O2 -target bpf t2.c

clean:
	@echo -e "  CLEAN  \033[1;32m$(@)\033[m"
	$(Q)rm -f *.o *.s *.S *.readelf

