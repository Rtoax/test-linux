# SPDX-License-Identifier: GPL-3.0
MPICC := $(shell which mpicc 2>/dev/null)
MPIRUN := $(shell which mpirun 2>/dev/null)
MPIEXEC := $(shell which mpiexec 2>/dev/null)

ifeq ($(MPICC),)
  ifdef OPENMPI
    MPICC := /usr/lib64/openmpi/bin/mpicc
    MPIRUN := /usr/lib64/openmpi/bin/mpirun
    MPIEXEC := /usr/lib64/openmpi/bin/mpiexec
  # fallback to mpich
  else
    MPICC := /usr/lib64/mpich/bin/mpicc
    MPIRUN := /usr/lib64/mpich/bin/mpirun
    MPIEXEC := /usr/lib64/mpich/bin/mpiexec
  endif
endif

CC := ${MPICC}

ifdef DEBUG
  $(info - INFO MPICC = ${MPICC})
  $(info - INFO MPIRUN = ${MPIRUN})
  $(info - INFO MPIRUN = ${MPIRUN})
endif

targets :=
targets += MPI_Abort
targets += MPI_Init
targets += MPI_Initialized
targets += MPI_Get_processor_name
targets += MPI_Send MPI_Send-2 MPI_Send-3
targets += MPI_Sendrecv MPI_Sendrecv_replace
targets += MPI_Wtime MPI_Wtick

ifeq ($(wildcard $(CC)),)
  targets :=
  $(warning Not install mpich or openmpi development software)
endif

CFLAGS :=
LDFLAGS :=

# -O3:
#   glibc 2.28: /usr/include/features.h
#   warning _FORTIFY_SOURCE requires compiling with optimization (-O)
CFLAGS += -Wno-error=unused-result
CFLAGS_MPI_Sendrecv_replace := -DCONFIG_MPI_Sendrecv_replace=1

targets-test := test0

include ../../../../template/main.mk

MPI_Abort: MPI_Abort.o
MPI_Init: MPI_Init.o
MPI_Initialized: MPI_Initialized.o
MPI_Get_processor_name: MPI_Get_processor_name.o
MPI_Send: MPI_Send.o
MPI_Send-2: MPI_Send-2.o
MPI_Send-3: MPI_Send-3.o
MPI_Sendrecv: MPI_Sendrecv.o
MPI_Sendrecv_replace: MPI_Sendrecv_replace.o
MPI_Wtime: MPI_Wtime.o
MPI_Wtick: MPI_Wtick.o

test0:
	$(call log_tgt_obj,TEST,,$(@))
	$(Q)$(MPIRUN) -n 2 ./MPI_Init
	$(Q)$(MPIRUN) -n 2 ./MPI_Send
	$(Q)$(MPIRUN) -n 10 ./MPI_Send-2
