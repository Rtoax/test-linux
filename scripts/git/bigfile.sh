#!/bin/bash

nr_file=10
dry_run=""
abs_path=""
with_size=""
exist_only=""
non_exist_only=""
colorful=YES
declare -a uuids files

git_topdir=$(git rev-parse --show-toplevel || {
	echo "ERROR: You are not in git repo"
	exit 1
})

__usage__() {
	echo "
git-bigfile [--dry-run]

  -n, --num  [NUM]     specify file number to list, default: ${nr_file}
  -e, --exist          print current exist only, default: off
      --non-exist      print non-exist only, default: off
  -a, --abs-path       print absolute path, default: off

  -s, --size           print file size (X means non-exist)

  --no-color           print without color

  --dry-run            only dump command not execute

  -h, --help           show this info
"
	exit ${1-0}
}

__eval__() {
	if [[ ! -z ${dry_run} ]]; then
		echo "$@"
	else
		eval "$@"
	fi
}

TEMP=$(getopt \
		--options n:eash \
		--long num: \
		--long exist \
		--long non-exist \
		--long no-color \
		--long abs-path \
		--long size \
		--long dry-run \
		--long help \
		-n git-bigfile -- "$@")

test $? != 0 && __usage__ 1

eval set -- "$TEMP"

while true; do
	case $1 in
	-n|--num)
		shift
		nr_file=$(grep '^[[:digit:]]*$' <<< $1)
		if [[ -z ${nr_file} ]]; then
			echo "ERROR: -n need a digit"
			exit 1
		fi
		shift
		;;
	-e|--exist)
		shift
		exist_only=YES
		;;
	--non-exist)
		shift
		non_exist_only=YES
		;;
	--no-color)
		shift
		colorful=""
		;;
	-a|--abs-path)
		shift
		abs_path=YES
		;;
	-s|--size)
		shift
		with_size=YES
		;;
	--dry-run)
		shift
		dry_run=YES
		;;
	-h|--help)
		shift
		__usage__ | more
		exit 0
		;;
	--)
		shift
		break
		;;
	esac
done


uuids=( $(git verify-pack -v ${git_topdir}/.git/objects/pack/pack-*.idx | \
			sort -k 3 -g | \
			tail -${nr_file} | \
			awk '{print $1}') )

for uuid in ${uuids[@]}
do
	__eval__ "files+=( $(git rev-list --objects --all | grep $uuid | awk '{print $2}') )"
done

for ((i = 0; i < ${#files[@]}; i++))
do
	if [[ ! -z ${exist_only} ]] && [[ ! -e ${git_topdir}/${files[$i]} ]]; then
		continue
	elif [[ ! -z ${non_exist_only} ]] && [[ -e ${git_topdir}/${files[$i]} ]]; then
		continue
	else
		# Determine the output color
		color=""
		color_reset=""
		if [[ ${colorful} ]]; then
			if [[ -e ${git_topdir}/${files[$i]} ]]; then
				color="\033[33m"
				color_reset="\033[m"
			else
				color="\033[9m"
				color_reset="\033[m"
			fi
		fi

		size=""
		if [[ ${with_size} ]]; then
			if [[ -e ${git_topdir}/${files[$i]} ]]; then
				size=$(du -sh ${git_topdir}/${files[$i]} | awk '{print $1}')
			else
				size='X'
			fi
		fi

		# Print
		echo -e "${color}${abs_path:+${git_topdir}/}${files[$i]}${color_reset}${size:+ ${size}}"
	fi
done
