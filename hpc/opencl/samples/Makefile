# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


include ../../../scripts/compiler.mk

TARGETS :=

TARGETS_CL := clGetPlatformIDs

CC = gcc

CFLAGS :=

LDFLAGS :=
LDLIBS :=

have_libopencl := $(findstring 1,$(call check_compiler_option,$(CC),-lOpenCL))

ifeq (${have_libopencl},1)
  $(info Found OpenCL)
  CFLAGS += -lOpenCL
  LDFLAGS += -lOpenCL
  TARGETS += $(TARGETS_CL)
endif

CFLAGS += -DDEBUG -O0 -g
CFLAGS += -DCL_TARGET_OPENCL_VERSION=100

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

clGetPlatformIDs: clGetPlatformIDs.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*)) $(LDFLAGS)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.s *.o *.d
