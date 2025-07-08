#pragma once

/**
 * clang error: unknown attribute 'optimize'
 */
#if !defined(__clang__)
#define _omit_frame_pointer	__attribute__((optimize("omit-frame-pointer")))
#else
#define _omit_frame_pointer
#endif

#if defined(__clang__)
#define _OPTIMIZE_O0 __attribute__((optnone))
#elif defined(__GNUC__)
#define _OPTIMIZE_O0 __attribute__((optimize("-O0")))
#endif
