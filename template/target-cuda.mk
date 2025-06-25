# SPDX-License-Identifier: GPL-3.0
NVCC := $(shell which nvcc 2>/dev/null)
ifeq ($(wildcard $(NVCC)),)
  $(error Not found nvcc, install cuda first)
endif

%.cu.o: %.cu
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(NVCC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS_CUDA): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(NVCC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))
