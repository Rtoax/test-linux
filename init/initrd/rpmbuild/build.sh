#!/bin/bash
set -e

rpmbuild -ba \
	--define "_topdir $PWD" \
	initramfs.spec
