MPICC =
MPIRUN =
MPIEXEC =

MPICC = /usr/lib64/mpich/bin/mpicc
MPIRUN = /usr/lib64/mpich/bin/mpirun
MPIEXEC = /usr/lib64/mpich/bin/mpiexec

CC = ${MPICC}

TARGETS := MPI_Init

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

CFLAGS_main.user := -D_MAIN_USER=1

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S $(<) -o $(<:.c=.s)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"
	$(MPIRUN) -n 2 ./MPI_Init

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.s *.o *.d
