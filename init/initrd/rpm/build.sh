#!/bin/bash

rpmbuild -ba \
	--define "_topdir $PWD" \
	initramfs.spec

