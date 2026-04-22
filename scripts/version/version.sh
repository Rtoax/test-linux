#!/bin/bash
# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2026 Rong Tao
set -e

readonly ROOTDIR=$(dirname $(realpath $0))
source ${ROOTDIR}/../liblog.sh
readonly CONFIG=${ROOTDIR}/config.json

# If symlink, just run actual command.
readonly symlink=$(basename $0)
if [[ ${symlink} != version.sh ]]; then
	${ROOTDIR}/version.sh -n ${symlink%.*} -V -- ${@}
	exit 0
fi

name=
check=

show_list=
show_keys=
declare -a show_k2n # key to name
declare -a show_e2n # extension to name
show_exts=
show_version=

declare -a version_parser_args

readonly common_vlens=( $(jq -r '.common.version.length[]' ${CONFIG}) )
readonly common_vargs=( $(jq -r '.common.version.command.argument[]' ${CONFIG}) )
readonly common_vsep=$(jq -r '.common.version.format.seperator' ${CONFIG})
readonly common_major=$(jq -r '.common.version.format.major' ${CONFIG})
readonly common_minor=$(jq -r '.common.version.format.minor' ${CONFIG})
readonly common_patch=$(jq -r '.common.version.format.patch' ${CONFIG})

readonly softwares=( $(jq -r '.software' ${CONFIG}  | jq -r 'keys[]') )

getswname() {
	local sw=$1
	local _name=$(jq -r --arg s "${sw}" '.software[$s].name' ${CONFIG} 2>/dev/null)
	if [[ ${_name} == null ]]; then
		warning "not found name for ${sw}, use ${sw} directly"
		_name=${sw}
	fi
	# name start with '$' will be replace to shell variable, such as $SHELL
	# will be replaced.
	if [[ ${_name:0:1} == $ ]]; then
		_name=$(eval "echo $_name")
	fi
	echo $(basename ${_name})
}

getswpaths() {
	local sw=$1
	jq -r --arg s "${sw}" '.software[$s].path[]' ${CONFIG} 2>/dev/null || true
}

getswsep() {
	local sw=$1
	local sep=$(jq -r --arg s "${sw}" '.software[$s].version.format.seperator' ${CONFIG} 2>/dev/null || true)
	[[ -z ${sep} || ${sep} == null ]] && sep=${common_vsep}
	echo ${sep}
}

getswcmds() {
	local sw=$1
	local orig_cmds=( $(jq -r --arg s "${sw}" '.software[$s].command[]' ${CONFIG} 2>/dev/null) )
	if [[ ${#orig_cmds[@]} -lt 1 ]]; then
		orig_cmds=( ${sw} )
	fi
	local cmd cmds
	for cmd in ${orig_cmds[@]}
	do
		# command start with '$' will be replace to shell variable,
		# such as $SHELL will be replaced.
		if [[ ${cmd:0:1} == $ ]]; then
			cmds+=( $(eval "echo $cmd") )
		else
			cmds+=( ${cmd} )
		fi
	done
	echo ${cmds[@]}
}

getswlibs() {
	local sw=$1
	jq -r --arg s "${sw}" '.software[$s].library[]' ${CONFIG} 2>/dev/null || true
}

getversion() {
	local sw=$1
	local cmd lib version

	local vargs=( $(jq -r --arg s "${sw}" '.software[$s].version.command.argument[]' ${CONFIG} 2>/dev/null || true) )
	local vlens=( $(jq -r --arg s "${sw}" '.software[$s].version.length[]' ${CONFIG} 2>/dev/null || true) )
	local vsep=$(getswsep ${sw})

	[[ ${#vargs} -eq 0 ]] && vargs=( ${common_vargs[@]} )
	[[ ${#vlens} -eq 0 ]] && vlens=( ${common_vlens[@]} )

	debug "get version of ${sw}"

	version_filter() {
		local greparg
		local sep=${vsep}
		[[ "${sep}" == "." ]] && sep="\\${sep}"
		local vlen
		for vlen in ${vlens[@]}
		do
			case ${vlen} in
			3)
				greparg="[0-9]+${sep}[0-9]+${sep}[0-9]+"
				;;
			2)
				greparg="[0-9]+${sep}[0-9]+"
				;;
			1)
				greparg="[0-9]+"
				;;
			*)
				error "version length only 1,2,3"
				;;
			esac
			version=$( echo "${@}" 2>&1 | \
					grep -Eo "${greparg}" 2>/dev/null | \
					head -1 )
			[[ ${version} ]] && break
		done # length

		[[ ${version} ]] && return 0
		return 0
	}

	replace_keys() {
		echo ${@} | sed "s|@ARCH@|$(uname -m)|g"
	}

	local cmds=( $(getswcmds ${sw}) )
	for cmd in ${cmds[@]};
	do
		cmd=$(replace_keys ${cmd})
		if [[ -z "$(which ${cmd} 2>/dev/null)" ]]; then
			warning "${sw}: not found command ${cmd}, skipping"
			continue
		fi
		local arg
		for arg in ${vargs[@]};
		do
			version_filter "$( ${cmd} ${arg} 2>&1 )"
			[[ ${version} ]] && break
		done # argument
		[[ ${version} ]] && break
	done # command

	if [[ -z ${version} ]]; then
		local libs=( $(getswlibs ${sw}) )
		for lib in ${libs[@]};
		do
			version_filter "$(ldconfig_libver ${lib})"
			[[ ${version} ]] && break
		done # library
	fi

	if [[ -z ${version} ]]; then
		local paths=( $(getswpaths ${sw}) )
		local path
		for path in ${paths[@]}
		do
			[[ ! -e ${path} ]] && continue
			version_filter "$(realpath ${path})"
			[[ ${version} ]] && break
		done
	fi

	if [[ -z ${version} ]]; then
		local deb rpm
		local debs=( $(jq -r --arg s "${sw}" '.software[$s].package.deb[]' ${CONFIG} 2>/dev/null) )
		for deb in ${debs[@]}
		do
			version_filter "$(dpkg-query -W -f='${Version}\n' ${deb} 2>/dev/null)"
			[[ ${version} ]] && break
		done
		if [[ -z ${version} ]]; then
			local rpms=( $(jq -r --arg s "${sw}" '.software[$s].package.rpm[]' ${CONFIG} 2>/dev/null) )
			for rpm in ${rpms[@]}
			do
				version_filter "$(rpm -q --queryformat='%{VERSION}-%{release}\n' ${rpm} 2>/dev/null)"
				[[ ${version} ]] && break
			done
		fi
	fi

	#echo "${sw}: ${cmds[@]}, ${vargs[@]}, ${vlens[@]}, ${vsep[@]}, ${version}"
	echo ${version}
}

check_one() {
	local sw=$1
	local versionfromjson=( $(getversion ${sw}) )
	local versionfromsh=( $(${ROOTDIR}/${sw}.sh) )

	if [[ "${versionfromjson[@]}" != "${versionfromsh[@]}" ]]; then
		error "${sw} failed to get version (<${versionfromjson[@]}> != <${versionfromsh[@]}>)"
	fi
	printf "%-16s %-10s %-10s\n" "${sw}" "${versionfromjson[@]}" "${versionfromsh[@]}"
}

check_all() {
	local sw
	for sw in ${softwares[@]}
	do
		check_one ${sw}
	done
}

extension_one() {
	local sw=$1
	local exts=( $(jq -r --arg s "${sw}" '.software[$s].extension[]' ${CONFIG} 2>/dev/null) )
	if [[ ${exts} == null ]]; then
		warning "not found extensions for ${sw}, skipping"
	fi
	echo ${exts[@]}
}

key_one() {
	local sw=$1
	local keys=( $(jq -r --arg s "${sw}" '.software[$s].keys[]' ${CONFIG} 2>/dev/null) )
	if [[ ${keys} == null ]]; then
		warning "not found keys for ${sw}, skipping"
	fi
	echo ${keys[@]}
}

# $1: library name, like libbpf.so, libxdp.so
ldconfig_libver() {
	# Opensuse has /sbin/ldconfig.
	local LDCONFIG=$(which ldconfig 2>/dev/null || ls /sbin/ldconfig 2>/dev/null)
	realpath $(${LDCONFIG} -p | grep ${1} 2>/dev/null | \
			awk '{print $NF}' | \
			head -1 || :) 2>/dev/null || :
}

# $1: software name
version_format_parser() {
	local sw=$1
	shift

	local major=$(jq -r --arg s "${sw}" '.software[$s].version.format.major' ${CONFIG} 2>/dev/null)
	local minor=$(jq -r --arg s "${sw}" '.software[$s].version.format.minor' ${CONFIG} 2>/dev/null)
	local patch=$(jq -r --arg s "${sw}" '.software[$s].version.format.patch' ${CONFIG} 2>/dev/null)

	[[ -z ${major} || ${major} == null ]] && major=${common_major}
	[[ -z ${minor} || ${minor} == null ]] && minor=${common_minor}
	[[ -z ${patch} || ${patch} == null ]] && patch=${common_patch}

	local name=$(getswname ${sw})
	local version=$(getversion ${sw})
	local vsep=$(getswsep ${sw})
	local ver_arr=( $(echo ${version} | tr "${vsep}" ' ') )

	local TEMP=$(getopt \
		--options Vh \
		--long name \
		--long pretty-name \
		--long ${major} \
		--long ${minor} \
		--long ${patch} \
		--long verbose \
		--long help \
		-n version-format-parser -- "$@")

	test $? != 0 && error "$0 parser args error"

	eval set -- "$TEMP"

	while true; do
		case $1 in
		--name)
			shift
			echo ${name}
			;;
		--pretty-name)
			shift
			# First letter uppercase
			echo ${name^}
			;;
		--${major})
			shift
			echo ${ver_arr[0]}
			;;
		--${minor})
			shift
			echo ${ver_arr[1]}
			;;
		--${patch})
			shift
			echo ${ver_arr[2]}
			;;
		-V|--verbose)
			shift
			export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
			set -x
			;;
		-h|--help)
			shift
			cat >&2 <<-EOF
			${name} help info:
			--name            show software name
			--pretty-name     show pretty name
			--${major}        show ${major} of version
			--${minor}        show ${minor} of version
			--${patch}        show ${patch} of version
			-V, --verbose     verbose mode
			-h, --help        show this information
			EOF
			;;
		--)
			shift
			break
			;;
		*)
			error "unknown ${1} of ${name}"
			;;
		esac
	done

	return 0
}

__version_usage__()
{
	echo -e "
-n, --name [NAME]        specify software name, like 'qemu', see --list

-L, --list               show software list
-K, --keys               show software keys
    --k2n                search softwares from key
-E, --ext                show software extensions
    --e2n                search softwares from key
-V, --version            show software version

--check                  check versions

-h, --help               show this help information
-v, --verbose            show detail during running
" | more
	exit ${1-0}
}

TEMP_ARGS=$(getopt \
	--options n:LKEVvh \
	--long name: \
	--long keys \
	--long k2n: \
	--long ext \
	--long e2n: \
	--long version \
	--long check \
	--long list \
	--long verbose \
	--long help \
	-n version -- "$@")

test $? != 0 && __version_usage__ 1

eval set -- "$TEMP_ARGS"

while true; do
	case $1 in
	-n|--name)
		shift
		name=$1
		if ! [[ " ${softwares[@]} ALL " =~ " ${name} " ]]; then
			error "unknown name ${name}, see --list"
		fi
		shift
		;;
	-L|--list)
		shift
		show_list=ON
		;;
	-K|--keys)
		shift
		show_keys=ON
		;;
	--k2n)
		shift
		show_k2n+=( ${1} )
		shift
		;;
	--e2n)
		shift
		show_e2n+=( ${1} )
		shift
		;;
	-E|--ext)
		shift
		show_exts=ON
		;;
	-V|--version)
		shift
		show_version=ON
		;;
	--check)
		shift
		check=ON
		;;
	-h|--help)
		shift
		__version_usage__
		;;
	-v|--verbose)
		shift
		export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
		set -x
		;;
	--)
		shift
		version_parser_args=( ${@} )
		break
		;;
	esac
done

if [[ ${show_list} ]]; then
	echo "${softwares[@]}"
fi

if [[ ${show_keys} ]]; then
	# Show all keys if name is ALL or empty
	if [[ ${name} == ALL ]] || [[ -z ${name} ]]; then
		for sw in ${softwares[@]}
		do
			key_one ${sw}
		done | tr ' ' '\n' | sort -u
	elif [[ ${name} ]]; then
		key_one ${name}
	fi
fi

key2name() {
	local key=$1
	jq -r --arg t "${key}" \
		'.software | to_entries[] | select(.value.keys | index($t)) | .key' ${CONFIG}
}

if [[ ${show_k2n} ]]; then
	for key in ${show_k2n[@]}
	do
		key2name ${key}
	done | sort -u
fi

if [[ ${show_exts} ]]; then
	if [[ ${name} == ALL ]] || [[ -z ${name} ]]; then
		for sw in ${softwares[@]}
		do
			extension_one ${sw}
		done | tr ' ' '\n' | sort -u
	elif [[ ${name} ]]; then
		extension_one ${name}
	fi
fi

ext2name() {
	local ext=$1
	jq -r --arg t "${ext}" \
		'.software | to_entries[] | select(.value.extension | index($t)) | .key' ${CONFIG}
}

if [[ ${show_e2n} ]]; then
	for ext in ${show_e2n[@]}
	do
		ext2name ${ext}
	done | sort -u
fi

if [[ ${show_version} ]] && [[ -z ${version_parser_args} ]]; then
	if [[ ${name} ]] && [[ ${name} != ALL ]]; then
		getversion ${name}
	fi
fi

if [[ ${name} ]] &&
   [[ -z "${show_list}${show_keys}${show_exts}${show_version}${check}${version_parser_args}" ]]; then
	if [[ ${name} == ALL ]]; then
		for sw in ${softwares[@]}
		do
			getswname ${sw}
		done
	else
		getswname ${name}
	fi
fi

if [[ ${check} ]]; then
	if [[ ${name} ]] && [[ ${name} != ALL ]]; then
		check_one ${name}
	else
		check_all
	fi
fi

if [[ ${name} ]] && [[ ${version_parser_args} ]]; then
	version_format_parser ${name} ${version_parser_args[@]}
fi
