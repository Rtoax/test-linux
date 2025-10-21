TCMALLOC_HDR = /usr/include/gperftools/tcmalloc.h

target-y :=
target-y += tc_malloc tc_malloc_skip_new_handler
target-y += tc_calloc
target-y += tc_valloc
target-y += tc_pvalloc
target-y += tc_realloc
target-y += tc_version
target-y += tc_posix_memalign
target-y += tc_nallocx
target-y += tc_memalign
target-y += tc_mallopt
target-y += tc_malloc_stats
target-y += tc_mallinfo
target-y += tc_free_sized
target-y += tc_cfree

profiles += GetHeapProfile
profiles += GetStackFrames
profiles += GetStackTrace
profiles += HeapProfilerStart
profiles += IsHeapProfilerRunning
profiles += MallocExtension_VerifyNewMemory
profiles += ProfilerStart
profiles += ProfilerStartWithOptions

ifdef PROFILE
  target-y += $(profiles)
endif

ifeq ($(wildcard $(TCMALLOC_HDR)),)
  $(warning "WARNING: Must install gperftools/tcmalloc development header")
  # Compile nothing
  target-y :=
endif

LDFLAGS :=
LDFLAGS += -ltcmalloc
LDFLAGS += -ltcmalloc_and_profiler
LDFLAGS += -ltcmalloc_debug
LDFLAGS += -ltcmalloc_minimal
LDFLAGS += -ltcmalloc_minimal_debug
LDFLAGS += -lpthread

include ../../../template/main.mk

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
