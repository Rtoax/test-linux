# SPDX-License-Identifier: GPL-3.0
NVCC := $(shell which nvcc 2>/dev/null)
ifeq ($(wildcard $(NVCC)),)
  $(error Not found nvcc, install cuda first)
endif

%.cu.o: %.cu
	$(call log_tgt_obj,NVCC,$(<),$(@))
	${Q}$(NVCC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS_CUDA): %:
	$(call log_tgt_exe,NVCC LD,$(<),$(@))
	${Q}$(NVCC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))
