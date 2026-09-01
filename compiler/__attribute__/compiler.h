#pragma once

#define __weak_alias(name) __attribute__((weak, alias(name)))

#define weak_alias(name, aliasname) \
	extern typeof(name) aliasname __attribute__((weak, alias(#name)))

/**
 * aligned
 * aligned (alignment)
 *
 * This attribute applies to functions, variables, typedefs, structs, and
 * structure fields.
 *
 * packed
 *
 * This attribute can be attached to a struct, union, or C++ class definition,
 * to a member of one, or to an enum definition.
 */
#ifndef __packed
#define __packed __attribute__((packed))
#endif

#ifndef __aligned
#define __aligned(v) __attribute__((aligned(v)))
#endif

#ifndef __packed_aligned
#define __packed_aligned(v) __attribute__((packed, aligned(v)))
#endif

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

/**
 * deprecated
 * deprecated (msg)
 *
 * This attribute can appear on function, variable, type, or enumerator
 * declarations.
 *
 * The deprecated attribute results in a warning if the entity it applies to is
 * used anywhere in the source file. This is useful when identifying functions
 * that are expected to be removed in a future version of a program.
 *
 * Refs:
 * - gcc: https://gcc.gnu.org/onlinedocs/gcc/Common-Attributes.html#index-deprecated
 */
#define __deprecated \
	__attribute__((deprecated("Symbol is not yet part of stable ABI")))

#define __unused __attribute__((unused))

#define __user __attribute__((noderef, address_space(1)))

#define __noinline __attribute__((noinline))

#ifndef __attribute_nonnull__
#define __attribute_nonnull__(params) __attribute__((__nonnull__ params))
#endif
#ifndef __nonnull
#define __nonnull(params) __attribute_nonnull__(params)
#endif

#if __has_attribute(__counted_by__)
#define __counted_by(member) __attribute__((__counted_by__(member)))
#else
#define __counted_by(member)
#endif
