MPICC = $(shell which mpicc 2>/dev/null)
MPIRUN = $(shell which mpirun 2>/dev/null)
MPIEXEC = $(shell which mpiexec 2>/dev/null)

ifeq ($(MPICC),)
MPICC = /usr/lib64/mpich/bin/mpicc
MPIRUN = /usr/lib64/mpich/bin/mpirun
MPIEXEC = /usr/lib64/mpich/bin/mpiexec
endif

CC = ${MPICC}

TARGETS :=
# If not install mpich
ifneq ($(wildcard $(CC)),)
TARGETS += MPI_Init
TARGETS += MPI_Get_processor_name
TARGETS += MPI_Send MPI_Send-2
endif

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

LDFLAGS :=
LDLIBS :=

CFLAGS += -DDEBUG -O0 -g

.PHONY: build
build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
MPI_Init: MPI_Init.o
MPI_Get_processor_name: MPI_Get_processor_name.o
MPI_Send: MPI_Send.o
MPI_Send-2: MPI_Send-2.o

%.o: %.c
	@echo -e "CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S $(<) -o $(<:.c=.s)

$(TARGETS): %:
	@echo -e "LD   \033[1;32m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"
	$(MPIRUN) -n 2 ./MPI_Init
	$(MPIRUN) -n 2 ./MPI_Send
	$(MPIRUN) -n 10 ./MPI_Send-2

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.s *.o *.d
