SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS :=
TARGETS += malloc
TARGETS += mallinfo
TARGETS += mallopt
TARGETS += malloc_get_state
TARGETS += malloc_info
TARGETS += malloc_stats
TARGETS += posix_memalign
TARGETS += realloc
TARGETS += malloc_trim
TARGETS += malloc_usable_size
TARGETS += memalign
TARGETS += pvalloc

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

CFLAGS_mallinfo := -Wno-error=deprecated-declarations
CFLAGS_helpers := -Wno-error=deprecated-declarations

# Add more object.o file
malloc: malloc.o
mallinfo: mallinfo.o helpers.o
mallopt: mallopt.o
malloc_get_state: malloc_get_state.o
malloc_info: malloc_info.o
malloc_stats: malloc_stats.o
posix_memalign: posix_memalign.o
realloc: realloc.o
malloc_trim: malloc_trim.o helpers.o
malloc_usable_size: malloc_usable_size.o
memalign: memalign.o
pvalloc: pvalloc.o


%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.xml
