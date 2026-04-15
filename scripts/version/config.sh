#!/bin/bash
set -e

common_vlens=( $(jq '.common.version.length[]' config.json) )
common_vargs=( $(jq '.common.version.argument[]' config.json) )
common_vseps=( $(jq '.common.version.seperator[]' config.json) )

softwares=( $(jq '.software' config.json  | jq 'keys[]') )

for sw in ${softwares[@]}
do
	cmds=( $(jq ".software.${sw}.command[]" config.json 2>/dev/null) )
	vlens=( $(jq ".software.${sw}.version.length[]" config.json 2>/dev/null || true) )
	[[ ${#vlens} -eq 0 ]] && vlens=( ${common_vlens[@]} )
	echo "${sw}: ${cmds[@]}, ${vlens[@]}"
done
