#if defined(SPIN_NONE)
#include "none.h"
#elif defined(SPIN_ORIG)
#include "original.h"
#elif defined(SPIN_PTHREAD)
#include "pthread_spin.h"
#endif
