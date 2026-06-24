# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2022-2026 Rong Tao
#
# Export functions:
# - reset_file($file)
# - is_newer($file1, $file2)=[y|n]
#
ifndef _FILE_MK
_FILE_MK = 1

include shell.mk

# Rename file to file.old, by recursion, old files are not deleted.
# $1: filename
define reset_file
  function __reset_file() { \
    if [[ -e $${1} ]]; then \
      if [[ -e $${1}.old ]]; then \
        __reset_file $${1}.old; \
      fi; \
      mv $${1} $${1}.old; \
    fi; \
  }; \
  __reset_file $1
endef

# FILE1 is newer (modification date) than FILE2
# $1: FILE1
# $2: FILE2
# @return: if FILE1 newer then FILE2, return 'y', else or if file not exist,
#          return 'n'.
define is_newer
$(shell if [[ ${1} -nt ${2} ]]; then echo y; else echo n; fi)
endef

# do some tests
ifneq ($(call is_newer,/etc/os-release,/etc/os-release),n)
  $(error is_newer: expect n, but y)
endif
ifneq ($(call is_newer,__non_exist__/nonsense,/etc/os-release),n)
  $(error is_newer: expect n, but y)
endif
ifneq ($(call is_newer,/var/log/messages,/etc/os-release),y)
  $(error is_newer: /var/log/messages should newer than /etc/os-release)
endif

endif
