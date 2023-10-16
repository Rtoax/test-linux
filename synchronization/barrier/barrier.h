#if defined(__aarch64__) || defined(__arm__)
#include "barrier-arm.h"
#elif defined(__x86_64__) || defined(__i386__)
#include "barrier-x86.h"
#endif
