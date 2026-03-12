include tcmalloc.mk

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

LDFLAGS += ${tcmalloc-ldflags}
LDFLAGS += -lpthread
