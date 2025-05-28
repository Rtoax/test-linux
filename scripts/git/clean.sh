#!/bin/bash
set -e

answer=N
[[ ! -z $1 ]] && answer=$1

readonly git_root=$(git rev-parse --show-toplevel 2>/dev/null || true)

declare -a no_add_files no_commit_files ignore_files

get_no_add_files() {
	no_add_files=( $(git status --porcelain | grep '^??' | cut -c4- | tr -d ' ') )
}

get_no_commit_files() {
	no_commit_files=( $(git status --porcelain | grep '^A' | cut -c4- | tr -d ' ') )
}

get_ignore_files() {
	ignore_files=( $(git clean -dfx --dry-run | sed 's/Would remove//g' | tr -d ' ') )
}

print_list() {
	local list=( $@ )
	local i
	for ((i = 0; i < ${#list[@]}; i++))
	do
		printf "\t%s\n" ${list[$i]}
	done
}

pre_check() {
	local -a no_add_valid_files

	get_no_add_files
	get_no_commit_files
	get_ignore_files

	# Filter no-add files
	for f in ${no_add_files}
	do
		read -r -N 8 bin < $f
		case $bin in
		$'\x7f'ELF* | $'!<arch>\n')
			;;
		*)
			no_add_valid_files+=( $f )
		esac
	done

	if [[ "${no_add_valid_files[@]}" ]]; then
		echo "ERROR: There are no-add new files in git repo!!"
		echo "       Handle them manually!!"
		print_list ${no_add_valid_files[@]}
		exit 1
	fi

	if [[ -z "${no_commit_files[@]}" ]] && [[ -z "${ignore_files[@]}" ]]; then
		echo "Nothing to clean"
		exit 0
	fi

	if [[ "${no_commit_files[@]}" ]]; then
		echo "Files not committed will not be removed:"
		print_list ${no_commit_files[@]}
	fi

	if [[ "${ignore_files[@]}" ]]; then
		echo "Files ignored will be removed:"
		print_list ${ignore_files[@]}
	fi
}

if [[ -z ${git_root} ]]; then
	echo >&2 "ERROR: Your not in git-repo!!!!"
	exit 1
fi

if [[ ${answer} != y ]] && [[ -z ${FORCE} ]]; then
	while pre_check && read -p "Are you sure? [N/y] " answer
	do
		case $answer in
		[Yy]|[Yy][Ee]|[Yy][Ee][Ss])
			break
			;;
		[Nn]|[Nn][On])
			echo "Bye!"
			exit 0
			;;
		*)
			echo "WARNING: Unknown $answer"
			continue
			;;
		esac
	done
fi

sudo git clean -dfx
echo "Clean git"
