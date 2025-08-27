# SPDX-License-Identifier: GPL-3.0
_BFD = 1

pound := \#

# Probe bfd_init() with non-output gcc command
BFD_HDR := '$(pound)include <stdio.h>\n'
BFD_HDR += '$(pound)include <bfd.h>\n'

BFD_INIT_PROBE_INIT_MAGIC := ${BFD_HDR}
BFD_INIT_PROBE_INIT_MAGIC += 'int main(void) {\n'
BFD_INIT_PROBE_INIT_MAGIC += '	int ret = bfd_init();\n'
BFD_INIT_PROBE_INIT_MAGIC += '	if (ret != BFD_INIT_MAGIC) {\n'
BFD_INIT_PROBE_INIT_MAGIC += '		exit(1)\n'
BFD_INIT_PROBE_INIT_MAGIC += '	}\n'
BFD_INIT_PROBE_INIT_MAGIC += '	return 0;\n'
BFD_INIT_PROBE_INIT_MAGIC += '}'

define probe_bfd_init_ret_magic
  $(shell printf '%b\n' $(BFD_INIT_PROBE_INIT_MAGIC) | \
    $(CC) -x c -Wall -Werror -lbfd - $(1) -S -o - >/dev/null 2>&1 \
      && echo 1)
endef


BFD_HAS_BFD_SECTION_VMA := ${BFD_HDR}
BFD_HAS_BFD_SECTION_VMA += 'int main(void) {\n'
BFD_HAS_BFD_SECTION_VMA += '	bfd_section_vma((asection *)NULL);\n'
BFD_HAS_BFD_SECTION_VMA += '	return 0;\n'
BFD_HAS_BFD_SECTION_VMA += '}'

define probe_bfd_has_bfd_section_vma
  $(shell printf '%b\n' $(BFD_HAS_BFD_SECTION_VMA) | \
    $(CC) -x c -Wall -Werror -lbfd - $(1) -S -o - >/dev/null 2>&1 \
      && echo 1)
endef


BFD_HAS_BFD_SECTION_VMA2 := ${BFD_HDR}
BFD_HAS_BFD_SECTION_VMA2 += 'int main(void) {\n'
BFD_HAS_BFD_SECTION_VMA2 += '	bfd_section_vma(NULL, (asection *)NULL);\n'
BFD_HAS_BFD_SECTION_VMA2 += '	return 0;\n'
BFD_HAS_BFD_SECTION_VMA2 += '}'

define probe_bfd_has_bfd_section_vma2
  $(shell printf '%b\n' $(BFD_HAS_BFD_SECTION_VMA2) | \
    $(CC) -x c -Wall -Werror -lbfd - $(1) -S -o - >/dev/null 2>&1 \
      && echo 1)
endef

BFD_HAS_BFD_SECTION_LMA := ${BFD_HDR}
BFD_HAS_BFD_SECTION_LMA += 'int main(void) {\n'
BFD_HAS_BFD_SECTION_LMA += '	bfd_section_lma((asection *)NULL);\n'
BFD_HAS_BFD_SECTION_LMA += '	return 0;\n'
BFD_HAS_BFD_SECTION_LMA += '}'

define probe_bfd_has_bfd_section_lma
  $(shell printf '%b\n' $(BFD_HAS_BFD_SECTION_LMA) | \
    $(CC) -x c -Wall -Werror -lbfd - $(1) -S -o - >/dev/null 2>&1 \
      && echo 1)
endef

BFD_HAS_BFD_SECTION_LMA2 := ${BFD_HDR}
BFD_HAS_BFD_SECTION_LMA2 += 'int main(void) {\n'
BFD_HAS_BFD_SECTION_LMA2 += '	bfd_section_lma(NULL, (asection *)NULL);\n'
BFD_HAS_BFD_SECTION_LMA2 += '	return 0;\n'
BFD_HAS_BFD_SECTION_LMA2 += '}'

define probe_bfd_has_bfd_section_lma2
  $(shell printf '%b\n' $(BFD_HAS_BFD_SECTION_LMA2) | \
    $(CC) -x c -Wall -Werror -lbfd - $(1) -S -o - >/dev/null 2>&1 \
      && echo 1)
endef

BFD_HAS_BFD_SECTION_NAME := ${BFD_HDR}
BFD_HAS_BFD_SECTION_NAME += 'int main(void) {\n'
BFD_HAS_BFD_SECTION_NAME += '	bfd_section_name((asection *)NULL);\n'
BFD_HAS_BFD_SECTION_NAME += '	return 0;\n'
BFD_HAS_BFD_SECTION_NAME += '}'

define probe_bfd_has_bfd_section_name
  $(shell printf '%b\n' $(BFD_HAS_BFD_SECTION_NAME) | \
    $(CC) -x c -Wall -Werror -lbfd - $(1) -S -o - >/dev/null 2>&1 \
      && echo 1)
endef

BFD_HAS_BFD_SECTION_NAME2 := ${BFD_HDR}
BFD_HAS_BFD_SECTION_NAME2 += 'int main(void) {\n'
BFD_HAS_BFD_SECTION_NAME2 += '	bfd_section_name(NULL, (asection *)NULL);\n'
BFD_HAS_BFD_SECTION_NAME2 += '	return 0;\n'
BFD_HAS_BFD_SECTION_NAME2 += '}'

define probe_bfd_has_bfd_section_name2
  $(shell printf '%b\n' $(BFD_HAS_BFD_SECTION_NAME2) | \
    $(CC) -x c -Wall -Werror -lbfd - $(1) -S -o - >/dev/null 2>&1 \
      && echo 1)
endef

BFD_HAS_BFD_SECTION_SIZE := ${BFD_HDR}
BFD_HAS_BFD_SECTION_SIZE += 'int main(void) {\n'
BFD_HAS_BFD_SECTION_SIZE += '	bfd_section_size((asection *)NULL);\n'
BFD_HAS_BFD_SECTION_SIZE += '	return 0;\n'
BFD_HAS_BFD_SECTION_SIZE += '}'

define probe_bfd_has_bfd_section_size
  $(shell printf '%b\n' $(BFD_HAS_BFD_SECTION_SIZE) | \
    $(CC) -x c -Wall -Werror -lbfd - $(1) -S -o - >/dev/null 2>&1 \
      && echo 1)
endef

BFD_HAS_BFD_SECTION_SIZE2 := ${BFD_HDR}
BFD_HAS_BFD_SECTION_SIZE2 += 'int main(void) {\n'
BFD_HAS_BFD_SECTION_SIZE2 += '	bfd_section_size(NULL, (asection *)NULL);\n'
BFD_HAS_BFD_SECTION_SIZE2 += '	return 0;\n'
BFD_HAS_BFD_SECTION_SIZE2 += '}'

define probe_bfd_has_bfd_section_size2
  $(shell printf '%b\n' $(BFD_HAS_BFD_SECTION_SIZE2) | \
    $(CC) -x c -Wall -Werror -lbfd - $(1) -S -o - >/dev/null 2>&1 \
      && echo 1)
endef

BFD_HAS_BFD_SECTION_ALIGNMENT := ${BFD_HDR}
BFD_HAS_BFD_SECTION_ALIGNMENT += 'int main(void) {\n'
BFD_HAS_BFD_SECTION_ALIGNMENT += '	bfd_section_alignment((asection *)NULL);\n'
BFD_HAS_BFD_SECTION_ALIGNMENT += '	return 0;\n'
BFD_HAS_BFD_SECTION_ALIGNMENT += '}'

define probe_bfd_has_bfd_section_alignment
  $(shell printf '%b\n' $(BFD_HAS_BFD_SECTION_ALIGNMENT) | \
    $(CC) -x c -Wall -Werror -lbfd - $(1) -S -o - >/dev/null 2>&1 \
      && echo 1)
endef

BFD_HAS_BFD_SECTION_ALIGNMENT2 := ${BFD_HDR}
BFD_HAS_BFD_SECTION_ALIGNMENT2 += 'int main(void) {\n'
BFD_HAS_BFD_SECTION_ALIGNMENT2 += '	bfd_section_alignment(NULL, (asection *)NULL);\n'
BFD_HAS_BFD_SECTION_ALIGNMENT2 += '	return 0;\n'
BFD_HAS_BFD_SECTION_ALIGNMENT2 += '}'

define probe_bfd_has_bfd_section_alignment2
  $(shell printf '%b\n' $(BFD_HAS_BFD_SECTION_ALIGNMENT2) | \
    $(CC) -x c -Wall -Werror -lbfd - $(1) -S -o - >/dev/null 2>&1 \
      && echo 1)
endef

BFD_HAS_BFD_SET_SECTION_VMA := ${BFD_HDR}
BFD_HAS_BFD_SET_SECTION_VMA += 'int main(void) {\n'
BFD_HAS_BFD_SET_SECTION_VMA += '	bfd_set_section_vma(NULL, 0);\n'
BFD_HAS_BFD_SET_SECTION_VMA += '	return 0;\n'
BFD_HAS_BFD_SET_SECTION_VMA += '}'

define probe_bfd_has_bfd_set_section_vma
  $(shell printf '%b\n' $(BFD_HAS_BFD_SET_SECTION_VMA) | \
    $(CC) -x c -Wall -Werror -lbfd - $(1) -S -o - >/dev/null 2>&1 \
      && echo 1)
endef

BFD_HAS_BFD_SET_SECTION_VMA2 := ${BFD_HDR}
BFD_HAS_BFD_SET_SECTION_VMA2 += 'int main(void) {\n'
BFD_HAS_BFD_SET_SECTION_VMA2 += '	bfd_set_section_vma(NULL, NULL, 0);\n'
BFD_HAS_BFD_SET_SECTION_VMA2 += '	return 0;\n'
BFD_HAS_BFD_SET_SECTION_VMA2 += '}'

define probe_bfd_has_bfd_set_section_vma2
  $(shell printf '%b\n' $(BFD_HAS_BFD_SET_SECTION_VMA2) | \
    $(CC) -x c -Wall -Werror -lbfd - $(1) -S -o - >/dev/null 2>&1 \
      && echo 1)
endef

BFD_HAS_BFD_SECTION_FLAGS := ${BFD_HDR}
BFD_HAS_BFD_SECTION_FLAGS += 'int main(void) {\n'
BFD_HAS_BFD_SECTION_FLAGS += '	bfd_section_flags(NULL);\n'
BFD_HAS_BFD_SECTION_FLAGS += '	return 0;\n'
BFD_HAS_BFD_SECTION_FLAGS += '}'

define probe_bfd_has_bfd_section_flags
  $(shell printf '%b\n' $(BFD_HAS_BFD_SECTION_FLAGS) | \
    $(CC) -x c -Wall -Werror -lbfd - $(1) -S -o - >/dev/null 2>&1 \
      && echo 1)
endef

BFD_HAS_BFD_ASYMBOL_SECTION := ${BFD_HDR}
BFD_HAS_BFD_ASYMBOL_SECTION += 'int main(void) {\n'
BFD_HAS_BFD_ASYMBOL_SECTION += '	bfd_asymbol_section(NULL);\n'
BFD_HAS_BFD_ASYMBOL_SECTION += '	return 0;\n'
BFD_HAS_BFD_ASYMBOL_SECTION += '}'

define probe_bfd_has_bfd_asymbol_section
  $(shell printf '%b\n' $(BFD_HAS_BFD_ASYMBOL_SECTION) | \
    $(CC) -x c -Wall -Werror -lbfd - $(1) -S -o - >/dev/null 2>&1 \
      && echo 1)
endef

BFD_HAS_BFD_GET_SYMBOL_VERSION_STRING := ${BFD_HDR}
BFD_HAS_BFD_GET_SYMBOL_VERSION_STRING += 'int main(void) {\n'
BFD_HAS_BFD_GET_SYMBOL_VERSION_STRING += '	bfd_get_symbol_version_string((bfd *)NULL, NULL, 1, NULL);\n'
BFD_HAS_BFD_GET_SYMBOL_VERSION_STRING += '	return 0;\n'
BFD_HAS_BFD_GET_SYMBOL_VERSION_STRING += '}'

define probe_bfd_has_bfd_get_symbol_version_string
  $(shell printf '%b\n' $(BFD_HAS_BFD_GET_SYMBOL_VERSION_STRING) | \
    $(CC) -x c -Wall -Werror -lbfd - $(1) -S -o - >/dev/null 2>&1 \
      && echo 1)
endef
