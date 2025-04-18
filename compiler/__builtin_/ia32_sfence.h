#if __x86_x64__
#define MEMORY_BARRIER() __builtin_ia32_sfence()
#else
#define MEMORY_BARRIER() __sync_synchronize()
#endif /* __x86_x64__ */