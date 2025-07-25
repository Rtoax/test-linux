TCMALLOC_HDR = /usr/include/gperftools/tcmalloc.h

targets :=
targets += tc_malloc tc_malloc_skip_new_handler
targets += tc_calloc
targets += tc_valloc
targets += tc_pvalloc
targets += tc_realloc
targets += tc_version
targets += tc_posix_memalign
targets += tc_nallocx
targets += tc_memalign
targets += tc_mallopt
targets += tc_malloc_stats
targets += tc_mallinfo
targets += tc_free_sized
targets += tc_cfree

targets-profile += GetHeapProfile
targets-profile += GetStackFrames
targets-profile += GetStackTrace
targets-profile += HeapProfilerStart
targets-profile += IsHeapProfilerRunning
targets-profile += MallocExtension_VerifyNewMemory
targets-profile += ProfilerStart
targets-profile += ProfilerStartWithOptions

ifdef PROFILE
  targets += $(targets-profile)
endif

ifeq ($(wildcard $(TCMALLOC_HDR)),)
  $(warning "WARNING: Must install gperftools/tcmalloc development header")
  # Compile nothing
  targets :=
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
