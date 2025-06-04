include ../../kconfig.mk

CFLAGS :=
LDFLAGS :=

TARGETS := main
TARGETS_LIBSO := libnvdso.so

NVDSO_ENV :=

ifdef DEBUG
  CFLAGS += -DNVDSO_DEBUG=1
  NVDSO_ENV += NVDSO_DEBUG=1
endif

ifdef ANON
  CFLAGS += -DNVDSO_ANON=1
  NVDSO_ENV += NVDSO_ANON=1
endif

ifeq (${CONFIG_ANON_VMA_NAME},y)
  $(info INFO: Support CONFIG_ANON_VMA_NAME)
  CFLAGS += -DCONFIG_ANON_VMA_NAME=1
endif

CFLAGS_main :=

TARGETS_POST := virt2phy
TARGETS_TEST := test-nvdso
TARGETS_CLEAN := clean-nvdso

include ../../template/main.mk

main: main.o
libnvdso.so: nvdso.so.o

virt2phy:
	$(Q)make -C ../../mm/ virt2phy
	$(Q)rm -f virt2phy
	$(Q)cp ../../mm/virt2phy .

test-nvdso:
	$(Q)${NVDSO_ENV} LD_PRELOAD=./libnvdso.so ./main

clean-nvdso:
	$(Q)rm -f *.out vdso.elf virt2phy
