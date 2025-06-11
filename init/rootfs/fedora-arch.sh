#!/bin/bash
set -e
readonly prog=$0

. /etc/os-release

TARGET_ARCH=$(uname -m)
ROOTFS_DIR="${PWD}/${ID}${VERSION_ID}-${TARGET_ARCH}-rootfs"

verbose=
dry_run=

__usage__() {
	echo -e "
NAME
	${prog} - make rootfs for fedora liked distrobution

SYNOPSIS
	${prog} --rootfs=<DIR>

DESCRIPTION
	-r, --rootfs [DIR]      specify rootfs directory.

	-u, --dry-run           only show commands
	-v, --verbose           enable verbose mode.
	-h, --help              show this help information

EXAMPLES
	$ sudo ${prog} --rootfs tmp-rootfs.dir

SEE ALSO
	dnf(8)
"
	exit ${1-0}
}

TEMP_ARGS=$(getopt --options r:uhv \
	--long rootfs: \
	--long dry-run \
	--long verbose \
	--long help \
	--name ${prog} -- "$@")

test $? != 0 && __usage__ 1

eval set -- "$TEMP_ARGS"

while true; do
	case $1 in
	-r | --rootfs)
		shift
		ROOTFS_DIR=$1
		shift
		;;
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

if [[ -z ${ROOTFS_DIR} ]]; then
	echo >&2 "ERROR: Must speicfy rootfs directory"
	exit 1
fi

ROOTFS_DIR=$(realpath ${ROOTFS_DIR})

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

os_dnf() {
	_eval sudo dnf --installroot=${ROOTFS_DIR} \
		--releasever=${VERSION_ID} \
		--forcearch=${TARGET_ARCH} \
		--use-host-config -y \
		"$@"
}

_eval sudo mkdir -p ${ROOTFS_DIR}
os_dnf group install development-tools
os_dnf install dnf make sudo rpm vim glibc-static

echo >&2 "${ID} ${VERSION_ID} rootfs for ${TARGET_ARCH} has been created at ${ROOTFS_DIR}"
