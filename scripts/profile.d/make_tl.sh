#!/bin/bash
# The repository provides many header files (mk), but it is not desirable for
# all include to use relative paths. If you use MAKEFLAGS to add --include-dir=,
# older versions of make (such as GNU Make 4.3 RHEL 9) will not work, newer
# make(such as GNU Make 4.4.1 fedora 43) works fine.
#
# If your account was created by useradd, you'd better change
# /etc/default/useradd file SHELL=/bin/bash, because /bin/sh(dash) not support
# `if [[]]` syntax. And, you'd better modify /etc/gdm3/Xsession shebang to
# /bin/bash too.

sys_make=$(which make)

make_tl() {
	local make_args=()
	local TEST_LINUX_ROOT=$(realpath $(dirname $(realpath ${BASH_SOURCE[0]}))/../../)
	if [[ " $(realpath .)" =~ " ${TEST_LINUX_ROOT}" ]] ||
	   [[ "$(realpath .)" =~ "ostools" ]] ||
	   [[ "$(realpath .)" =~ "test-linux" ]]; then
		make_args+=( __USE_TEST_LINUX_MAKE__=1 )
		make_args+=( -I${TEST_LINUX_ROOT}/template/ )

		# FIXME: When use make -C, this statement check will be wrong.
		if [[ -f Tbuild.mk ]]; then
			# It is not supported to use Tbuild.mk and Makefile at
			# the same time.
			if [[ -f Makefile ]]; then
				echo >&2 "ERROR: Not allow Tbuild.mk and Makefile at the same time"
				exit 1
			fi
			make_args+=( -f ${TEST_LINUX_ROOT}/scripts/Makefile.tbuild )
		fi

		# The build is added by default because we can put `post`
		# before `include main.mk` in the Makefile or Tbuild.mk.
		# FIXME: We should never add target, because we could specify
		# one.
		if ! [[ " ${@} " =~ " build " ]] &&
		   ! [[ " ${@} " =~ " test " ]] &&
		   ! [[ " ${@} " =~ " clean " ]]; then
			make_args+=( build )
		fi
		${sys_make} ${make_args[@]} $@
	else
		${sys_make} $@
	fi
}

alias make="make_tl"

# Not call from alias, call script directly
if [[ $(basename $0) == make_tl ]] || \
   [[ $(basename $0) == make_tl.sh ]]; then
	make_tl "$@"
fi
