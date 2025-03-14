include ../../../tlbuild.mk


TARGETS :=
TARGETS += mode_strict
TARGETS += mode_filter mode_filter-no-scmp
TARGETS += filter-write

CC := gcc
CFLAGS :=

all: ${TARGETS}

mode_strict: mode_strict.o seccomp.o
mode_filter: mode_filter.o
mode_filter-no-scmp: mode_filter-no-scmp.o
filter-write: filter-write.o

CFLAGS_mode_filter-no-scmp := -DCONFIG_NO_SECCOMP=1

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o
