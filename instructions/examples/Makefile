
###############################################################################
# Kernel
obj-m += invalid_opcode_kern.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

###############################################################################
# User
TARGETS :=

# User
ifeq ($(shell uname -m),x86_64)
TARGETS += invalid_opcode_user
TARGETS += cpuid_user
TARGETS += rdtsc_user
TARGETS += rdtscp_user
TARGETS += rdtsc_cmp
TARGETS += rdtsc_evil
TARGETS += fsin
TARGETS += bswapl
endif
ifeq ($(shell uname -m),aarch64)
endif

user: $(TARGETS)

kernel:
	make -C ${KERNELDIR} M=$(PWD) modules


bswapl: bswapl.o
invalid_opcode_user: invalid_opcode_user.o
cpuid_user: cpuid_user.o
rdtsc_user: rdtsc_user.o
rdtscp_user: rdtscp_user.o
rdtsc_cmp: rdtsc_cmp.o
rdtsc_evil: rdtsc_evil.o
fsin: fsin.o

CFLAGS += -g -ggdb
CFLAGS += -D_GNU_SOURCE
CFLAGS += -O3
CFLAGS += -pthread

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

help:
	@echo "make [kernel|user|help]"
	@echo " default: user"

test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	rm -f $(TARGETS) \
		*.o
	make -C ${KERNELDIR} M=$(PWD) clean
