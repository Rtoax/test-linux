
default:
	@echo "make [kernel|user]"

###############################################################################
# Kernel
obj-m += invalid_opcode_kern.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

kernel:
	make -C ${KERNELDIR} M=$(PWD) modules

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
endif
ifeq ($(shell uname -m),aarch64)
endif

invalid_opcode_user: invalid_opcode_user.o
cpuid_user: cpuid_user.o
rdtsc_user: rdtsc_user.o
rdtscp_user: rdtscp_user.o
rdtsc_cmp: rdtsc_cmp.o

CFLAGS += -D_GNU_SOURCE
CFLAGS += -O3
CFLAGS += -pthread

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

user: $(TARGETS)


test:
	@echo "empty, [cd $(PWD)] to insmod"

clean:
	rm -f \
		*.o \
		invalid_opcode_user \
		cpuid_user \
		rdtsc_user \
		rdtscp_user \
		rdtsc_cmp
	make -C ${KERNELDIR} M=$(PWD) clean
