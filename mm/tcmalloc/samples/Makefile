SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TCMALLOC_HDR = /usr/include/gperftools/tcmalloc.h

TARGETS :=
TARGETS += tc_malloc tc_malloc_skip_new_handler
TARGETS += tc_calloc
TARGETS += tc_valloc
TARGETS += tc_pvalloc
TARGETS += tc_realloc
TARGETS += tc_version
TARGETS += tc_posix_memalign
TARGETS += tc_nallocx
TARGETS += tc_memalign
TARGETS += tc_mallopt
TARGETS += tc_malloc_stats
TARGETS += tc_mallinfo
TARGETS += tc_free_sized
TARGETS += tc_cfree

ifdef PROFILE
TARGETS += GetHeapProfile
TARGETS += GetStackFrames
TARGETS += GetStackTrace
TARGETS += HeapProfilerStart
TARGETS += IsHeapProfilerRunning
TARGETS += MallocExtension_VerifyNewMemory
TARGETS += ProfilerStart
TARGETS += ProfilerStartWithOptions
endif

ifeq ($(wildcard $(TCMALLOC_HDR)),)
$(warning "WARNING: Must install gperftools/tcmalloc development header")
# Compile nothing
TARGETS :=
endif

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes
CFLAGS += -ltcmalloc
CFLAGS += -ltcmalloc_and_profiler
CFLAGS += -ltcmalloc_debug
CFLAGS += -ltcmalloc_minimal
CFLAGS += -ltcmalloc_minimal_debug
CFLAGS += -lpthread

LDFLAGS :=
LDLIBS :=

.PHONY: build
build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
tc_malloc: tc_malloc.o
tc_malloc_skip_new_handler: tc_malloc_skip_new_handler.o
tc_calloc: tc_calloc.o
tc_valloc: tc_valloc.o
tc_pvalloc: tc_pvalloc.o
tc_realloc: tc_realloc.o
tc_version: tc_version.o
tc_posix_memalign: tc_posix_memalign.o
tc_nallocx: tc_nallocx.o
tc_memalign: tc_memalign.o
tc_mallopt: tc_mallopt.o
tc_malloc_stats: tc_malloc_stats.o
tc_mallinfo: tc_mallinfo.o
tc_free_sized: tc_free_sized.o
tc_cfree: tc_cfree.o

GetHeapProfile: GetHeapProfile.o
GetStackFrames: GetStackFrames.o
GetStackTrace: GetStackTrace.o
HeapProfilerStart: HeapProfilerStart.o
IsHeapProfilerRunning: IsHeapProfilerRunning.o
MallocExtension_VerifyNewMemory: MallocExtension_VerifyNewMemory.o
ProfilerStart: ProfilerStart.o
ProfilerStartWithOptions: ProfilerStartWithOptions.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.s *.o *.d
