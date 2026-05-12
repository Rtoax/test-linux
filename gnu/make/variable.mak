# SPDX-License-Identifier: GPL-3.0

_mk./abc := a

$(info _mk./abc = ${_mk./abc})

.PHONY: build
build:
