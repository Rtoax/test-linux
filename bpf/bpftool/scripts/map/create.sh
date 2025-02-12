#!/bin/bash
set -e

readonly prog=bpftool-test

verbose=
dry_run=
TYPE=array

SUPPORT_TYPES=( array hash )

[[ -z ${BPFTOOL} ]] && BPFTOOL=bpftool

__usage__()
{
	echo -e "
NAME
	${prog} - Test bpftool

SYNOPSIS
	${prog} [--dry-run]

DESCRIPTION
	Test bpftool.

ARGUMENT
	-t, --type [TYPE]  specify map type, default: ${TYPE}

	-u, --dry-run      only show commands

	-v, --verbose      show verbose information
	-h, --help         show this help information

SEE ALSO
	bpftool(8), bpf(2).
"
	exit ${1-0}
}

ARGS=$(getopt --options t:uvh \
	--long type: \
	--long dry-run \
	--long verbose \
	--long help \
	--name ${prog} -- "$@")

test $? != 0 && __usage__ 1

eval set -- "${ARGS}"

while true; do
	case $1 in
	-t | --type)
		shift
		if [[ " ${SUPPORT_TYPES[*]} " =~ " ${1} " ]]; then
			TYPE=$1
		else
			echo >&2 "ERROR: Not support type=${1}, support: ${SUPPORT_TYPES[@]}"
			exit 1
		fi
		shift
		;;
	-h | --help)
		shift
		__usage__
		;;
	-v | --verbose)
		shift
		verbose=YES
		export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
		set -x
		;;
	-u | --dry-run)
		shift
		dry_run=YES
		;;
	--)
		shift
		break
		;;
	esac
done

_eval()
{
	if [[ -z ${dry_run} ]]; then
		echo >&2 -e "\033[1;32m$@\033[m"
		eval "$@"
	else
		echo "$@"
	fi
}

# BPF_OBJ_NAME_LEN=16U, map name length need smaller than 15
# refs:
# - https://lore.kernel.org/lkml/tencent_26592A2BAF08A3A688A50600421559929708@qq.com/
NAME=$(mktemp -u t_${TYPE}_XXXXXXXXXXXXXX)
NAME_truncate=${NAME:0:15}

_eval sudo ${BPFTOOL} map create /sys/fs/bpf/${NAME} \
	type ${TYPE} \
	name ${NAME_truncate} \
	key 4 value 4 entries 5

_eval sudo ${BPFTOOL} map show name ${NAME_truncate}
_eval sudo ${BPFTOOL} map dump name ${NAME_truncate}

case ${TYPE} in
array | hash)
	_eval sudo ${BPFTOOL} map update name ${NAME_truncate} key 0 0 0 0 value 0 0 0 0
	_eval sudo ${BPFTOOL} map update name ${NAME_truncate} key 1 0 0 0 value 1 0 0 0
	_eval sudo ${BPFTOOL} map update name ${NAME_truncate} key 2 0 0 0 value 2 0 0 0
	_eval sudo ${BPFTOOL} map update name ${NAME_truncate} key 3 0 0 0 value 3 0 0 0
	_eval sudo ${BPFTOOL} map update name ${NAME_truncate} key 4 0 0 0 value 4 0 0 0
	;;
esac

_eval sudo ${BPFTOOL} map dump name ${NAME_truncate}

# Remove map from system
_eval sudo unlink /sys/fs/bpf/${NAME}
