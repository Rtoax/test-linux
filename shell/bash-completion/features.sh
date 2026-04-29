#!/bin/bash
set -e

# --no-feature feature1,feature2,...
features=( kprobe_multi kprobe_session uprobe_multi )
prev=--no-feature

comp() {
	local cur=${1}
	if [[ -z ${cur} ]]; then
		COMPREPLY=( $(compgen -W "${features[*]}" -- ${cur}) )
	else
		if [[ ${cur:${#cur}-1} == , ]]; then
			local prevfeatures=( $(echo ${cur} | tr ',' ' ') )
			local leftfeatures=( )
			for pf in ${features[@]}
			do
				if [[ ! " ${prevfeatures[@]} " =~ " ${pf} " ]]; then
					leftfeatures+=( ${pf} )
				fi
			done
			local hints=( )
			for f in ${leftfeatures[@]}
			do
				hints+=( ${cur}${f} )
			done
			COMPREPLY=( $(compgen -W "${hints[*]}" -- ${cur}) )
		else
			return 0
		fi
	fi
	echo ${COMPREPLY[@]}
	return 0
}

comp
comp k
comp kprobe_
comp kprobe_m
comp u
comp uprobe_multi,
comp uprobe_multi,kprobe_multi,
comp kprobe_multi,uprobe_multi,kprobe_session
