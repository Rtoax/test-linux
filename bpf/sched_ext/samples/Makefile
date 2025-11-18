# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

target-y := hello

target-bpf-y := $(patsubst %,${OUTPUT}%.bpf.o,${target-y})

include main.mk

define define_target
${OUTPUT}${1}.o: ${OUTPUT}${1}.skel.h
${1}: ${OUTPUT}${1}.o
endef

$(eval $(call define_target,hello))
