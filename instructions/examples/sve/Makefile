# SPDX-License-Identifier: GPL-3.0
SHELL = bash

CC := gcc
CFLAGS :=
RUN_PFX :=
TARGETS :=
TARGETS += neon-sve

# Cross compile
ifdef CROSS_COMPILE
  ifndef SYSROOT
    $(error "Must define SYSROOT if CROSS_COMPILE")
  endif
  ifneq ($(shell uname -m),aarch64)
    CC = aarch64-linux-gnu-gcc
    AS = aarch64-linux-gnu-as
    LD = aarch64-linux-gnu-ld
    # This root could be created by Docker Image Tar Archive
    # see: aarch64-linux-gnu-gcc -print-sysroot
    CFLAGS += --sysroot=${SYSROOT}
    RUN_PFX = qemu-aarch64 --sysroot=${SYSROOT}
  else
    $(error "$(shell uname -m) is not support CROSS_COMPILE")
  endif
endif

ifdef STATIC
  CFLAGS += -static
endif

# All CC set done here
include ../../../scripts/compiler.mk
feature-sve2 := $(findstring 1,$(call check_compiler_option,$(CC),-march=armv8-a+sve+sve2))

ifeq (${feature-sve2},1)
  $(info feature-sve2 = ${feature-sve2})

  TARGETS += sve-width
  TARGETS += add_array
  TARGETS += svaddlb

  CFLAGS += -march=armv8-a+sve+sve2
  CFLAGS += -DCPU_HAVE_NEON=1
  CFLAGS += -DCPU_HAVE_SVE=1
endif

all: $(TARGETS)

sve-width: sve-width.o
add_array: add_array.o
svaddlb: svaddlb.o
neon-sve: neon-sve.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

# Help information
help:
	@echo ""
	@echo "Usage: make [options]"
	@echo ""
	@echo "Options:"
	@echo "       STATIC=1"
	@echo "       CROSS_COMPILE=1"
	@echo "       SYSROOT=/path/to/rootfs"
	@echo ""

test:
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	$(RUN_PFX) ./sve-width

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f $(TARGETS) *.o
