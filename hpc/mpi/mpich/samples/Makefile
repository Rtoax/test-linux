# SPDX-License-Identifier: GPL-3.0
include ../../../../tlbuild.mk

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

$(info - INFO MPICC = ${MPICC})
$(info - INFO MPIRUN = ${MPIRUN})
$(info - INFO MPIRUN = ${MPIRUN})

TARGETS :=
TARGETS += MPI_Abort
TARGETS += MPI_Init
TARGETS += MPI_Initialized
TARGETS += MPI_Get_processor_name
TARGETS += MPI_Send MPI_Send-2 MPI_Send-3
TARGETS += MPI_Sendrecv MPI_Sendrecv_replace
TARGETS += MPI_Wtime MPI_Wtick

ifeq ($(wildcard $(CC)),)
  TARGETS :=
  $(warning Not install mpich or openmpi development software)
endif

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

LDFLAGS :=

# -O3:
#   glibc 2.28: /usr/include/features.h
#   warning _FORTIFY_SOURCE requires compiling with optimization (-O)
CFLAGS += -DDEBUG -O3 -g
CFLAGS += -Wno-error=unused-result
CFLAGS_MPI_Sendrecv_replace := -DCONFIG_MPI_Sendrecv_replace=1

.PHONY: build
build: ${TARGETS}
	@echo "TARGETS = ${TARGETS}"
	@echo -e " \033[1;33m Done \033[m"

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

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S $(<) -o $(<:.c=.s)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	$(MPIRUN) -n 2 ./MPI_Init
	$(MPIRUN) -n 2 ./MPI_Send
	$(MPIRUN) -n 10 ./MPI_Send-2

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.s *.o *.d
