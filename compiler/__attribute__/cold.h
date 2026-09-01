/**
 * The cold attribute on a function informs the compiler that the function is
 * unlikely to be executed.
 *
 * The hot attribute on a function informs the compiler that the function is a
 * hot spot of the compiled program.
 */
#pragma once

#ifdef __GNUC__
#if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 2))
#define __cold __attribute__((cold))
#else
#define __cold
#endif
#else
#define __cold
#endif

#define __hot __attribute__((hot))
