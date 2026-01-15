#!/bin/bash
# The repository provides many header files (mk), but it is not desirable for
# all include to use relative paths. If you use MAKEFLAGS to add --include-dir=,
# older versions of make (such as GNU Make 4.3 RHEL 9) will not work, newer
# make(such as GNU Make 4.4.1 fedora 43) works fine.
#

make_tl() {
	local make_args
	local TEST_LINUX_ROOT=$(realpath $(dirname $(realpath ${BASH_SOURCE[0]}))/../../)
	if [[ " $(realpath .)" =~ " ${TEST_LINUX_ROOT}" ]] ||
	   [[ "$(realpath .)" =~ "ostools" ]] ||
	   [[ "$(realpath .)" =~ "test-linux" ]]; then
		make_args+=( __USE_TEST_LINUX_MAKE__=1 )
		make_args+=( -I${TEST_LINUX_ROOT}/template/ )
		make ${make_args[@]} $@
	else
		make $@
	fi
}

alias make="make_tl"
