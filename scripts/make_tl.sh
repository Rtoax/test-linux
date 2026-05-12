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

readonly sys_make=$(which make)

declare i ARGS makefile
declare workdir=$PWD
declare -a make_args
declare TEST_LINUX_ROOT=$(realpath $(dirname $(realpath ${BASH_SOURCE[0]}))/../)

# Use origin make command
if ! [[ " $(realpath .)" =~ " ${TEST_LINUX_ROOT}" ]] &&
   ! [[ "$(realpath .)" =~ "ostools" ]] &&
   ! [[ "$(realpath .)" =~ "test-linux" ]]; then
	${sys_make} $@
	return $?
fi

# FIXME: remove this check after a little while
if [[ -L /etc/profile.d/make_tl.sh ]]; then
	echo >&2 "ERROR: 'make uninstall' first, then 'make install' again"
	exit 1
fi

ARGS=( "${@}" )
for ((i = 0; i < ${#ARGS[@]}; i++)); do
	case ${ARGS[i]} in
	-C | --directory)
		workdir=${ARGS[$(( i + 1 ))]}
		;;
	-f | --file | --makefile)
		makefile=${ARGS[$(( i + 1 ))]}
		;;
	esac
done

make_args+=( __USE_TEST_LINUX_MAKE__=1 )
make_args+=( -I${TEST_LINUX_ROOT}/template/ )

if [[ -z ${makefile} ]] && [[ -f ${workdir}/Build.mk ]]; then
	# It is not supported to use Build.mk and Makefile at
	# the same time.
	if [[ -f ${workdir}/Makefile ]]; then
		echo >&2 "ERROR: Not allow Build.mk and Makefile at the same time"
		exit 1
	fi
	make_args+=( -f ${TEST_LINUX_ROOT}/scripts/Makefile.build )
elif [[ -z ${makefile} ]] && [[ -f ${workdir}/Kbuild ]]; then
	make_args+=( __KMOD__=1 )
	make_args+=( -f ${TEST_LINUX_ROOT}/scripts/Makefile.kmod )
fi

_eval() {
	if [[ ${VERBOSE} ]]; then
		echo >&2 -e "\033[1;32m${@}\033[m"
	fi
	eval "${@}"
}
_eval ${sys_make} ${make_args[@]} ${@}
