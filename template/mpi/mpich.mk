# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_MPICH=[y|n]
# - MPICH_MPICC=
# - MPICH_MPIRUN=
# - MPICH_MPIEXEC=
#
ifndef _MPI_MPICH_MK
_MPI_MPICH_MK = 1

include define.mk

MPICH_MPICC := /usr/lib64/mpich/bin/mpicc
MPICH_MPIRUN := /usr/lib64/mpich/bin/mpirun
MPICH_MPIEXEC := /usr/lib64/mpich/bin/mpiexec

$(call check_file_and_def,${MPICH_MPICC},HAVE_MPICH)

ifdef DEBUG
  $(info HAVE_MPICH = ${HAVE_MPICH})
  $(info MPICH_MPICC = ${MPICH_MPICC})
  $(info MPICH_MPIRUN = ${MPICH_MPIRUN})
  $(info MPICH_MPIEXEC = ${MPICH_MPIEXEC})
endif

export HAVE_MPICH
export MPICH_MPICC MPICH_MPIRUN MPICH_MPIEXEC

endif
