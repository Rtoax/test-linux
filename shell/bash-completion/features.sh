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
		# TODO: support a,b,c
		COMPREPLY=( $(compgen -W "${features[*]}" -- ${cur}) )
	fi
	echo ${COMPREPLY[@]}
}

comp
comp k
comp u
