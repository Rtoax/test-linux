#!/bin/bash
# The repository provides many header files (mk), but it is not desirable for
# all include to use relative paths. If you use MAKEFLAGS to add --include-dir=,
# older versions of make (such as GNU Make 4.3 RHEL 9) will not work, newer
# make(such as GNU Make 4.4.1 fedora 43) works fine.
#

make_tl() {
	local TEST_LINUX_ROOT=$(realpath $(dirname $(realpath ${BASH_SOURCE[0]}))/../../)
	if [[ " $(realpath .)" =~ " ${TEST_LINUX_ROOT}" ]]; then
		local args
		args+=( -I${TEST_LINUX_ROOT}/template/ )

		make ${args[@]} $@
	else
		make $@
	fi
}

alias make="make_tl"
