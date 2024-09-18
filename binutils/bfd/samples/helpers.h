#pragma once

#include <bfd.h>

void tl_bfd_print_build_id(const struct bfd_build_id *bid);
const char *tl_bfd_pure_name(asymbol *sym, char *buf, int blen);
