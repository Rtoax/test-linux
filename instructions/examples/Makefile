
###############################################################################
# Kernel
obj-m += invalid_opcode_kern.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

###############################################################################
# User
TARGETS :=
CFLAGS :=
ARCH_LIB_CPUID :=

# User
ifeq ($(shell uname -m),x86_64)
ifneq ($(shell lscpu | grep -w avx2),)
	CFLAGS += -mavx2 -mfma
	CFLAGS += -DCPU_HAVE_AVX2=1
endif
ifneq ($(shell lscpu | grep -w avx512f),)
	CFLAGS += -mavx512f -mfma
	CFLAGS += -DCPU_HAVE_AVX512F=1
endif
TARGETS += bts
TARGETS += invalid_opcode_user
TARGETS += rdtsc_user
TARGETS += rdtscp_user
TARGETS += rdtsc_cmp
TARGETS += rdtsc_evil
TARGETS += fsin
TARGETS += bswapl
TARGETS += _mm_clflush
TARGETS += vgetbv
TARGETS += stosb memset
TARGETS += nop
TARGETS += rdmsr
TARGETS += rdrand
TARGETS += rdseed

ARCH_LIB_CPUID += cpuid-x86.o
endif

ifeq ($(shell uname -m),aarch64)
# Check cpu flags
ifneq ($(shell lscpu | grep -w sve),)
CFLAGS += -DCPU_HAVE_SVE=1
endif
ifneq ($(shell lscpu | grep -w sve2),)
CFLAGS += -DCPU_HAVE_SVE2=1
endif

CFLAGS += -DCPU_HAVE_NEON=1
TARGETS += mrs

ARCH_LIB_CPUID += cpuid-arm64.o
endif

TARGETS += simd
TARGETS += cpuid_user

user: $(TARGETS)

kernel:
	make -C ${KERNELDIR} M=$(PWD) modules


bts: bts.o
bswapl: bswapl.o
invalid_opcode_user: invalid_opcode_user.o
cpuid_user: cpuid_user.o ${ARCH_LIB_CPUID}
rdtsc_user: rdtsc_user.o
rdtscp_user: rdtscp_user.o
rdtsc_cmp: rdtsc_cmp.o
rdtsc_evil: rdtsc_evil.o
_mm_clflush: _mm_clflush.o
fsin: fsin.o
vgetbv: vgetbv.o
stosb: stosb.o
memset: memset.o
nop: nop.o
rdmsr: rdmsr.o
mrs: mrs.o
simd: simd.o
rdrand: rdrand.o
rdseed: rdseed.o

#CFLAGS += -Werror -Wall
CFLAGS += -g -ggdb
CFLAGS += -D_GNU_SOURCE
CFLAGS += -O3
CFLAGS += -pthread
ifdef STATIC
CFLAGS += -static
$(info Defined STATIC)
endif

CFLAGS_rdrand := -mrdrnd
CFLAGS_rdseed := -mrdseed

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
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
