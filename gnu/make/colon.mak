# SPDX-License-Identifier: GPL-3.0

targets := a
targets += b\:01

.PHONY: build
build: ${targets}

${targets}:
	${Q}echo "========${@}========="
