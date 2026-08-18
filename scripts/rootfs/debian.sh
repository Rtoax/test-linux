#!/bin/bash
# Copyright (C) 2026 Rong Tao
#
# Build debian/ubuntu like operate system's rootfs with dnf/rpm package manager.
#
set -e

readonly prog=rootfs-debian
readonly ROOTFS_DEBIAN_DIR=$(dirname $(realpath $0))

. ${ROOTFS_DEBIAN_DIR}/../liblog.sh
. /etc/os-release

declare TARGET_ARCH=$(uname -m)

declare verbose
declare dry_run

__usage__() {
	echo -e "
NAME
	${prog} - make rootfs for fedora liked distrobution

SYNOPSIS
	${prog} --rootfs=<DIR> [--image=<vm.raw|vm.qcow2>]

DESCRIPTION

	-u, --dry-run           only show commands
	-v, --verbose           enable verbose mode.
	-h, --help              show this help information

EXAMPLES

SEE ALSO
	apt(8), dpkg(8)
"
	exit ${1-0}
}

TEMP_ARGS=$(getopt --options uhv \
	--long dry-run \
	--long verbose \
	--long help \
	--name ${prog} -- "$@")

test $? != 0 && __usage__ 1

eval set -- "$TEMP_ARGS"

while true; do
	case $1 in
	-h | --help)
		shift
		__usage__
		;;
	-u | --dry-run)
		shift
		dry_run=YES
		;;
	-v | --verbose)
		shift
		verbose=YES
		;;
	--)
		shift
		break
		;;
	esac
done

if [[ ${verbose} ]]; then
	export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
	set -x
fi

_eval()
{
	if [[ -z ${dry_run} ]]; then
		echo >&2 -e "\033[1;32mStartup: $@\033[m"
		eval "$@"
		echo >&2 -e "\033[1;33mDone: $@\033[m"
	else
		echo "$@"
	fi
}

# TODO
