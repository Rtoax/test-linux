#!/bin/bash

rpmbuild -ba \
	--define "_topdir $PWD" \
	SPECS/initramfs.spec

