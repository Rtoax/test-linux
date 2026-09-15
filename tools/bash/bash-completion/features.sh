#!/bin/bash
set -e

comp() {
	echo >&2 "------------ ${@} -------------"
	COMPREPLY=()

	local cur=${1}
	# --no-feature feature1,feature2,...
	local features=( kprobe_multi kprobe_session uprobe_multi )
	local prev="--no-feature"

	if [[ ${cur} ]]; then
		local prevfeatures=( $(echo ${cur} | tr ',' ' ') )
		local leftfeatures=( )

		for pf in ${features[@]}
		do
			if [[ ! " ${prevfeatures[@]} " =~ " ${pf} " ]]; then
				leftfeatures+=( ${pf} )
			fi
		done

		# if cur end with ',', just complete left features
		if [[ ${cur:${#cur}-1} == , ]]; then
			local hints=( )
			for f in ${leftfeatures[@]}
			do
				hints+=( ${cur}${f} )
			done
			COMPREPLY=( $(compgen -W "${hints[*]}" -- ${cur}) )
		# only one feature and cur not end with ','
		elif [[ ${#prevfeatures[@]} -eq 1 ]]; then
			COMPREPLY=( $(compgen -W "${features[*]}" -- ${cur}) )
		# for example: 'kprobe_multi,kprobe_'
		elif [[ ${#prevfeatures[@]} -gt 1 ]]; then
			local lastfeature=${prevfeatures[-1]}
			local hints=( )
			for f in ${leftfeatures[@]}
			do
				if [[ " ${f} " =~ " ${lastfeature}" ]]; then
					hints+=( ${cur:0:-${#lastfeature}}${f} )
				fi
			done
			if [[ ${hints} ]]; then
				COMPREPLY=( $(compgen -W "${hints[*]}" -- ${cur}) )
			fi
		fi
	else
		COMPREPLY=( $(compgen -W "${features[*]}" -- ${cur}) )
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
comp kprobe_multi,uprobe_
comp uprobe_multi,k
comp uprobe_multi,kprobe_m
