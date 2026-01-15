// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#pragma once

#include <bfd.h>

#define __unused __attribute((unused))
#if defined(BFD_HAS_BFD_SECTION_NAME)
# define tl_bfd_section_name(asect)	bfd_section_name(asect)
#elif defined(BFD_HAS_BFD_SECTION_NAME2)
# define tl_bfd_section_name(asect)	bfd_section_name(abfd, asect)
#endif

#if defined(BFD_HAS_BFD_SECTION_FLAGS)
# define tl_bfd_section_flags(asect) bfd_section_flags(asect)
#else
# define tl_bfd_section_flags(asect) asect->flags
#endif

void tl_bfd_init(void);
void tl_bfd_print_build_id(const struct bfd_build_id *bid);
const char *tl_bfd_strbid(const struct bfd_build_id *bid, char *buf, int blen);
const char *tl_bfd_pure_name(asymbol *sym, char *buf, int blen);

