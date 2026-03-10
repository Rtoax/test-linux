# SPDX-License-Identifier: GPL-3.0
include mpich.mk

OUTPUT = .output/
CC := ${MPICC}

target-y += MPI_Abort
target-y += MPI_Init
target-y += MPI_Initialized
target-y += MPI_Get_processor_name
target-y += MPI_Send MPI_Send-2 MPI_Send-3
target-y += MPI_Sendrecv MPI_Sendrecv_replace
target-y += MPI_Wtime MPI_Wtick

ifeq ($(wildcard $(CC)),)
  target-y :=
  $(warning Not install mpich or openmpi development software)
endif

# -O3:
#   glibc 2.28: /usr/include/features.h
#   warning _FORTIFY_SOURCE requires compiling with optimization (-O)
CFLAGS += -Wno-error=unused-result
CFLAGS_MPI_Sendrecv_replace := -DCONFIG_MPI_Sendrecv_replace=1

target-test-y := test0

include main.mk

test0:
	$(call log_tgt,TEST,$(@))
	$(Q)$(MPIRUN) -n 2 ./MPI_Init
	$(Q)$(MPIRUN) -n 2 ./MPI_Send
	$(Q)$(MPIRUN) -n 10 ./MPI_Send-2
