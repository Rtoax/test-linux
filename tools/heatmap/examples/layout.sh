#!/bin/bash

declare -a args

args+=( '--gran-cl3' )

while :;
do
	case $1 in
	-v|--verbose)
		shift
		export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
		set -x
		;;
	-t | --text)
		shift
		args+=( "--text-only" )
		;;
	*)
		break
		;;
	esac
done

hmctl heatmap -i layout-orig.txt --min 0x00000000001bc0 --max 0x00000000002000 ${args[@]}
hmctl heatmap -i layout-fdo.txt --min 0x00000000001528 --max 0x00000000001a28 ${args[@]}
hmctl heatmap -i layout-autofdo.txt --min 0x00000000001200 --max 0x00000000001600 ${args[@]}

