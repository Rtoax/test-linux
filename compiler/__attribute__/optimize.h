#pragma once

#define _omit_frame_pointer	__attribute__((optimize("omit-frame-pointer")))

#if defined(__clang__)
#define _OPTIMIZE_O0 __attribute__((optnone))
#elif defined(__GNUC__)
#define _OPTIMIZE_O0 __attribute__((optimize("-O0")))
#endif
