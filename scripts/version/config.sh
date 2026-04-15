#!/bin/bash
set -e

source $(dirname $(realpath $0))/libversion.sh

readonly common_vlens=( $(jq -r '.common.version.length[]' config.json) )
readonly common_vargs=( $(jq -r '.common.version.argument[]' config.json) )
readonly common_vseps=( $(jq -r '.common.version.seperator[]' config.json) )

readonly softwares=( $(jq -r '.software' config.json  | jq -r 'keys[]') )

getversion() {
	local sw=$1
	local cmd lib version
	local cmds=( $(jq -r --arg s "${sw}" '.software[$s].command[]' config.json 2>/dev/null) )
	if [[ ${#cmds[@]} -lt 1 ]]; then
		cmds=( ${sw} )
	fi
	local libs=( $(jq -r --arg s "${sw}" '.software[$s].library[]' config.json 2>/dev/null) )

	local vargs=( $(jq -r --arg s "${sw}" '.software[$s].version.argument[]' config.json 2>/dev/null || true) )
	local vlens=( $(jq -r --arg s "${sw}" '.software[$s].version.length[]' config.json 2>/dev/null || true) )
	local vseps=( $(jq -r --arg s "${sw}" '.software[$s].version.seperator[]' config.json 2>/dev/null || true) )

	[[ ${#vargs} -eq 0 ]] && vargs=( ${common_vargs[@]} )
	[[ ${#vlens} -eq 0 ]] && vlens=( ${common_vlens[@]} )
	[[ ${#vseps} -eq 0 ]] && vseps=( ${common_vseps[@]} )

	version_filter() {
		local greparg
		local sep
		for sep in ${vseps[@]}
		do
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
					echo >&2 "ERROR: version length only 1,2,3"
					exit 1
					;;
				esac
				version=$( echo "${@}" 2>&1 | \
						grep -Eo "${greparg}" 2>/dev/null | \
						head -1 )
				[[ ${version} ]] && break
			done # length
			[[ ${version} ]] && break
		done # seperator
	}

	for cmd in ${cmds[@]};
	do
		if [[ -z "$(which ${cmd} 2>/dev/null)" ]]; then
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

	for lib in ${libs[@]};
	do
		version_filter "$(ldconfig_libver ${lib})"
		[[ ${version} ]] && break
	done # library

	if [[ -z ${version} ]]; then
		local deb rpm
		local debs=( $(jq -r --arg s "${sw}" '.software[$s].package.deb[]' config.json 2>/dev/null) )
		for deb in ${debs}
		do
			version_filter "$(dpkg-query -W -f='${Version}\n' numactl 2>/dev/null)"
			[[ ${version} ]] && break
		done
		[[ ${version} ]] && break
		local rpms=( $(jq -r --arg s "${sw}" '.software[$s].package.rpm[]' config.json 2>/dev/null) )
		for rpm in ${rpms}
		do
			version_filter "$(rpm -q --queryformat='%{VERSION}\n' numactl 2>/dev/null)"
			[[ ${version} ]] && break
		done
	fi

	#echo "${sw}: ${cmds[@]}, ${vargs[@]}, ${vlens[@]}, ${vseps[@]}, ${version}"
	echo ${version}
}

check_one() {
	local sw=$1
	local versionfromjson=$(getversion ${sw})
	local versionfromsh=$(./${sw}.sh)
	if [[ ${versionfromjson} != ${versionfromsh} ]]; then
		echo >&2 "ERROR: ${sw} failed to get version (<${versionfromjson}> != <${versionfromsh}>)"
		exit 1
	fi
	printf "%-16s %-10s %-10s\n" "${sw}" "${versionfromjson}" "${versionfromsh}"
}

check_all() {
	local sw
	for sw in ${softwares[@]}
	do
		check_one ${sw}
	done
}

if [[ -z $1 ]]; then
	check_all
else
	check_one $1
fi
