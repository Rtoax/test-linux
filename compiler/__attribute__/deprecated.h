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
#pragma once

/* DPDK */
#ifndef ALLOW_EXPERIMENTAL_API
#define __rte_experimental \
	__attribute__((deprecated("Symbol is not yet part of stable ABI"), \
		section(".text.experimental")))
#else
#define __rte_experimental \
	__attribute__((section(".text.experimental")))
#endif

#define __deprecated __attribute__((deprecated("Symbol is not yet part of stable ABI")))
