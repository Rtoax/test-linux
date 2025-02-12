#!/bin/bash
set -e

readonly prog=bpftool-test

no_unlink=
verbose=
dry_run=

NAME=
TYPE=array
KEY=4
VALUE=4
ENTRIES=5

INNER_MAP_NAME=

SUPPORT_TYPES=(
	array percpu_array array_of_maps
	hash percpu_hash
)

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
	-n, --name [STR]   specify map name
	-t, --type [TYPE]  specify map type, default: ${TYPE}

	-k, --key [NUM]    specify key size (B), default: ${KEY}
	-v, --value [NUM]  specify value size (B), default: ${VALUE}
	-e, --entries [NUM] specify number of entries, default: ${ENTRIES}

	--inner_map_name [STR] specify inner_map_name for array_of_maps or hash_of_maps

	--no-unlink        do not unlink map in the end.
	-u, --dry-run      only show commands

	-V, --verbose      show verbose information
	-h, --help         show this help information

SEE ALSO
	bpftool(8), bpf(2).
"
	exit ${1-0}
}

# BPF_OBJ_NAME_LEN=16U, map name length need smaller than 15
# refs:
# - https://lore.kernel.org/lkml/tencent_26592A2BAF08A3A688A50600421559929708@qq.com/
check_map_name()
{
	local name=$1
	if [[ ${#name} -gt 15 ]]; then
		echo >&2 "WARNING: map name should be no longer than 15 chars"
	fi
}

ARGS=$(getopt --options n:t:k:v:e:uVh \
	--long name: \
	--long type: \
	--long key: \
	--long value: \
	--long entries: \
	--long inner_map_name: \
	--long no-unlink \
	--long dry-run \
	--long verbose \
	--long help \
	--name ${prog} -- "$@")

test $? != 0 && __usage__ 1

eval set -- "${ARGS}"

while true; do
	case $1 in
	-n | --name)
		shift
		NAME=$1
		shift
		;;
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
	-k | --key)
		shift
		KEY=$1
		shift
		;;
	-v | --value)
		shift
		VALUE=$1
		shift
		;;
	-e | --entries)
		shift
		ENTRIES=$1
		shift
		;;
	--inner_map_name)
		shift
		INNER_MAP_NAME=$1
		if ! [[ " array_of_maps hash_of_maps " =~ " ${TYPE} " ]]; then
			echo >&2 "ERROR: need type=[array_of_maps|hash_of_maps], ${TYPE}"
			exit 1
		fi
		shift
		;;
	--no-unlink)
		shift
		no_unlink=YES
		;;
	-h | --help)
		shift
		__usage__
		;;
	-V | --verbose)
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

[[ -z ${NAME} ]] && NAME=$(mktemp -u t_${TYPE}_XXXXXXXXXXXXXX)

check_map_name ${NAME}

NAME_truncate=${NAME:0:15}

declare -a create_args

case ${TYPE} in
array_of_maps)
	create_args+=( inner_map name ${INNER_MAP_NAME} )
	;;
esac

_eval sudo ${BPFTOOL} map create /sys/fs/bpf/${NAME} \
	type ${TYPE} \
	name ${NAME_truncate} \
	key ${KEY} value ${VALUE} entries ${ENTRIES} \
	${create_args[@]}

_eval sudo ${BPFTOOL} map show name ${NAME_truncate}
_eval sudo ${BPFTOOL} map dump name ${NAME_truncate}

case ${TYPE} in
array | percpu_array | hash | percpu_hash)
	_eval sudo ${BPFTOOL} map update name ${NAME_truncate} key 0 0 0 0 value 0 0 0 0
	_eval sudo ${BPFTOOL} map update name ${NAME_truncate} key 1 0 0 0 value 1 0 0 0
	_eval sudo ${BPFTOOL} map update name ${NAME_truncate} key 2 0 0 0 value 2 0 0 0
	_eval sudo ${BPFTOOL} map update name ${NAME_truncate} key 3 0 0 0 value 3 0 0 0
	_eval sudo ${BPFTOOL} map update name ${NAME_truncate} key 4 0 0 0 value 4 0 0 0
	;;
array_of_maps)
	_eval sudo ${BPFTOOL} map update pinned /sys/fs/bpf/${NAME_truncate} \
		key 0 0 0 0 value pinned /sys/fs/bpf/${INNER_MAP_NAME}
	_eval sudo ${BPFTOOL} map update name ${NAME_truncate} \
		key 1 0 0 0 value name ${INNER_MAP_NAME}
	;;
esac

_eval sudo ${BPFTOOL} map dump name ${NAME_truncate}

# Remove map from system
[[ ! ${no_unlink} ]] && _eval sudo unlink /sys/fs/bpf/${NAME}
