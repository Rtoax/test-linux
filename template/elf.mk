# SPDX-License-Identifier: GPL-3.0
ifndef _ELF_MK
_ELF_MK = 1

# return 'y' if is pie
define elf_is_pie
$(shell file $(1) | grep -io pie 1>/dev/null && echo y)
endef

endif
