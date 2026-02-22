#!/bin/bash 

kpatch-build --skip-compiler-check \
	-s . \
	-v ./vmlinux\
	-c /boot/config-5.14.0 \
	cmdline.patch
