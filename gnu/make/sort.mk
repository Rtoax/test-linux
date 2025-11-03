# SPDX-License-Identifier: GPL-3.0

srcs := a.c y.c b.c a.c

srcs_expect := a.c b.c y.c
srcs_sort := $(sort ${srcs})

$(info srcs = ${srcs})
$(info srcs_sort = ${srcs_sort})

# TODO: why !=
ifneq (${srcs},${srcs_expect})
  $(error <${srcs_expect}> != <${srcs_sort}>)
endif

.PHONY: build
build:
