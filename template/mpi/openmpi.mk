# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
#
# Output definitions:
# - HAVE_OPENMPI=[y|n]
# - OPENMPI_MPICC=
# - OPENMPI_MPIRUN=
# - OPENMPI_MPIEXEC=
#
ifndef _MPI_OPENMPI_MK
_MPI_OPENMPI_MK = 1

include define.mk

# Debian
ifneq ($(wildcard /usr/bin/mpicc.openmpi),)
  OPENMPI_MPICC := /usr/bin/mpicc.openmpi
  OPENMPI_MPIRUN := /usr/bin/mpirun.openmpi
  OPENMPI_MPIEXEC := /usr/bin/mpiexec.openmpi
# Fedora
else ifneq ($(wildcard /usr/lib64/openmpi/bin/mpicc),)
  OPENMPI_MPICC := /usr/lib64/openmpi/bin/mpicc
  OPENMPI_MPIRUN := /usr/lib64/openmpi/bin/mpirun
  OPENMPI_MPIEXEC := /usr/lib64/openmpi/bin/mpiexec
else
  OPENMPI_MPICC := __nonsense__
endif

$(call check_file_and_def,${OPENMPI_MPICC},HAVE_OPENMPI)

ifdef DEBUG
  $(info HAVE_OPENMPI = ${HAVE_OPENMPI})
  $(info OPENMPI_MPICC = ${OPENMPI_MPICC})
  $(info OPENMPI_MPIRUN = ${OPENMPI_MPIRUN})
  $(info OPENMPI_MPIEXEC = ${OPENMPI_MPIEXEC})
endif

export HAVE_OPENMPI
export OPENMPI_MPICC OPENMPI_MPIRUN OPENMPI_MPIEXEC

endif
