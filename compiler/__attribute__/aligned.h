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
#pragma once

#ifndef __packed
#define __packed __attribute__((packed))
#endif

#ifndef __aligned
#define __aligned(v) __attribute__((aligned(v)))
#endif

#ifndef __packed_aligned
#define __packed_aligned(v) __attribute__((packed, aligned(v)))
#endif
