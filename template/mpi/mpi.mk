# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Input definitions:
# - USE_OPENMPI
#
# Output definitions:
# - MPICC=
# - MPIRUN=
# - MPIEXEC=
#
ifndef _MPI_MPI_MK
_MPI_MPI_MK = 1

include mpi/mpich.mk
include mpi/openmpi.mk

ifdef USE_OPENMPI
  MPICC := ${OPENMPI_MPICC}
  MPIRUN := ${OPENMPI_MPIRUN}
  MPIEXEC := ${OPENMPI_MPIEXEC}
else
  MPICC := ${MPICH_MPICC}
  MPIRUN := ${MPICH_MPIRUN}
  MPIEXEC := ${MPICH_MPIEXEC}
endif

ifdef DEBUG
  $(info MPICC = ${MPICC})
  $(info MPIRUN = ${MPIRUN})
  $(info MPIRUN = ${MPIRUN})
endif

export MPICC MPIRUN MPIEXEC

endif
