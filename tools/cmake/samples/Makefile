# SPDX-License-Identifier: GPL-3.0
include shell.mk

target-prep-y := build0
target-clean-y := clean0

include main.mk

.PHONY: build0
build0:
	${Q}mkdir -p build && pushd build && cmake .. && make && popd

.PHONY: clean0
clean0:
	${Q}rm -rf build
