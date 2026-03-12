# SPDX-License-Identifier: GPL-3.0
subdir-y := map
target-shell-y := $(shell find -maxdepth 1 -type f -name '*.sh' -executable)
