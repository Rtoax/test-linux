#!/bin/bash
set -e

common_vlens=( $(jq '.common.version.length[]' config.json) )
common_vargs=( $(jq '.common.version.argument[]' config.json) )
common_vseps=( $(jq '.common.version.seperator[]' config.json) )

softwares=( $(jq '.software' config.json  | jq 'keys[]') )

for sw in ${softwares[@]}
do
	cmds=( $(jq ".software.${sw}.command[]" config.json 2>/dev/null) )
	vargs=( $(jq ".software.${sw}.version.argument[]" config.json 2>/dev/null || true) )
	vlens=( $(jq ".software.${sw}.version.length[]" config.json 2>/dev/null || true) )
	vseps=( $(jq ".software.${sw}.version.seperator[]" config.json 2>/dev/null || true) )

	[[ ${#vargs} -eq 0 ]] && vargs=( ${common_vargs[@]} )
	[[ ${#vlens} -eq 0 ]] && vlens=( ${common_vlens[@]} )
	[[ ${#vseps} -eq 0 ]] && vseps=( ${common_vseps[@]} )

	echo "${sw}: ${cmds[@]}, ${vargs[@]}, ${vlens[@]}, ${vseps[@]}"
done
