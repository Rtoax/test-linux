include kconfig.mk

target-y := main
target-libso-y := libnvdso.so

libnvdso.so-objs := nvdso.so.o

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

target-post-y += virt2phy
target-post-y += post-nvdso
target-clean-y += clean-nvdso
