TARGETS :=
TARGETS += tc_malloc
TARGETS += tc_calloc
TARGETS += tc_valloc
TARGETS += tc_pvalloc
TARGETS += tc_realloc
TARGETS += tc_version
TARGETS += tc_posix_memalign
TARGETS += tc_nallocx
TARGETS += tc_memalign
TARGETS += tc_mallopt

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes
CFLAGS += -ltcmalloc
CFLAGS += -lpthread

LDFLAGS :=
LDLIBS :=

.PHONY: build
build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
tc_malloc: tc_malloc.o
tc_calloc: tc_calloc.o
tc_valloc: tc_valloc.o
tc_pvalloc: tc_pvalloc.o
tc_realloc: tc_realloc.o
tc_version: tc_version.o
tc_posix_memalign: tc_posix_memalign.o
tc_nallocx: tc_nallocx.o
tc_memalign: tc_memalign.o
tc_mallopt: tc_mallopt.o

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.s *.o *.d
