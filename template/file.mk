# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2022-2026 Rong Tao
#
# Export functions:
# - reset_file($file)
#
ifndef _FILE_MK
export _FILE_MK = 1

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

endif
