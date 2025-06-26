# SPDX-License-Identifier: GPL-3.0

FILES := a b c
PREFIX := dir/

FILES_PREFIX := $(addprefix ${PREFIX}, ${FILES})
FILES_SUFFIX := $(addsuffix .c, ${FILES})

$(info FILES: ${FILES})
$(info FILES_PREFIX: ${FILES_PREFIX})
$(info FILES_SUFFIX: ${FILES_SUFFIX})

.PHONY: build
build:
