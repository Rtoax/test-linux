#!/bin/bash
set -e

readonly common_vlens=( $(jq '.common.version.length[]' config.json) )
readonly common_vargs=( $(jq '.common.version.argument[]' config.json) )
readonly common_vseps=( $(jq '.common.version.seperator[]' config.json) )

readonly softwares=( $(jq '.software' config.json  | jq 'keys[]') )

getversion() {
	local sw=$1
	local cmds=( $(jq ".software.${sw}.command[]" config.json 2>/dev/null) )
	if [[ ${#cmds[@]} -lt 1 ]]; then
		exit 0
	fi
	local vargs=( $(jq ".software.${sw}.version.argument[]" config.json 2>/dev/null || true) )
	local vlens=( $(jq ".software.${sw}.version.length[]" config.json 2>/dev/null || true) )
	local vseps=( $(jq ".software.${sw}.version.seperator[]" config.json 2>/dev/null || true) )

	[[ ${#vargs} -eq 0 ]] && vargs=( ${common_vargs[@]} )
	[[ ${#vlens} -eq 0 ]] && vlens=( ${common_vlens[@]} )
	[[ ${#vseps} -eq 0 ]] && vseps=( ${common_vseps[@]} )

	echo "${sw}: ${cmds[@]}, ${vargs[@]}, ${vlens[@]}, ${vseps[@]}"
}

for sw in ${softwares[@]}
do
	getversion ${sw}
done
