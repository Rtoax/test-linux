# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - MPICC
# - MPIRUN
# - MPIEXEC
#
ifndef _MPICH_MK
_MPICH_MK = 1

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

ifdef DEBUG
  $(info - INFO MPICC = ${MPICC})
  $(info - INFO MPIRUN = ${MPIRUN})
  $(info - INFO MPIRUN = ${MPIRUN})
endif

endif
