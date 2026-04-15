#!/bin/bash
set -e

readonly common_vlens=( $(jq -r '.common.version.length[]' config.json) )
readonly common_vargs=( $(jq -r '.common.version.argument[]' config.json) )
readonly common_vseps=( $(jq -r '.common.version.seperator[]' config.json) )

readonly softwares=( $(jq -r '.software' config.json  | jq -r 'keys[]') )

getversion() {
	local sw=$1
	local cmd version
	local cmds=( $(jq -r ".software.${sw}.command[]" config.json 2>/dev/null) )
	if [[ ${#cmds[@]} -lt 1 ]]; then
		exit 0
	fi
	local vargs=( $(jq -r ".software.${sw}.version.argument[]" config.json 2>/dev/null || true) )
	local vlens=( $(jq -r ".software.${sw}.version.length[]" config.json 2>/dev/null || true) )
	local vseps=( $(jq -r ".software.${sw}.version.seperator[]" config.json 2>/dev/null || true) )

	[[ ${#vargs} -eq 0 ]] && vargs=( ${common_vargs[@]} )
	[[ ${#vlens} -eq 0 ]] && vlens=( ${common_vlens[@]} )
	[[ ${#vseps} -eq 0 ]] && vseps=( ${common_vseps[@]} )

	for cmd in ${cmds[@]};
	do
		local arg
		for arg in ${vargs[@]};
		do
			local sep
			for sep in ${vseps[@]}
			do
				local vlen
				for vlen in ${vlens[@]}
				do
					local greparg
					case ${vlen} in
					3)
						greparg="[0-9]+${sep}[0-9]+${sep}[0-9]+"
						;;
					2)
						greparg="[0-9]+${sep}[0-9]+"
						;;
					*)
						echo >&2 "ERROR: version length only 2,3"
						exit 1
						;;
					esac
					version=$( ${cmd} ${arg} | grep -Eo "${greparg}" 2>/dev/null | head -1 || true )
					[[ ${version} ]] && break
				done # length
				[[ ${version} ]] && break
			done # seperator
			[[ ${version} ]] && break
		done # argument
		[[ ${version} ]] && break
	done # command

	echo "${sw}: ${cmds[@]}, ${vargs[@]}, ${vlens[@]}, ${vseps[@]}, ${version}"
}

for sw in ${softwares[@]}
do
	getversion ${sw}
done
