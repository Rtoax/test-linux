#pragma once

/**
 * The cold attribute on a function informs the compiler that the function is
 * unlikely to be executed.
 *
 * The hot attribute on a function informs the compiler that the function is a
 * hot spot of the compiled program.
 */
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

#define __unused __attribute__((unused))

#define __user __attribute__((noderef, address_space(1)))

#ifndef __attribute_nonnull__
#define __attribute_nonnull__(params) __attribute__((__nonnull__ params))
#endif
#ifndef __nonnull
#define __nonnull(params) __attribute_nonnull__(params)
#endif
