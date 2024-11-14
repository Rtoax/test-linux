# SPDX-License-Identifier: GPL-3.0
SHELL = bash

text := 1.txt
text += 2.txt
text += 3.txt
text += 4.txt

src := 1.c
src += 2.c
src += 3.c

obj = $(patsubst %.c,%.o,$(src))

.PHONY: build
build:
	echo $(wordlist 1,3,$(text))
	echo $(obj)

