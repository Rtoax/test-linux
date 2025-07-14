#!/bin/bash
set -e

declare -a git_rm_cmd rm_files
dry_run=

git_rm_cmd+=( git rm --cached --ignore-unmatch )

git_topdir=$(git rev-parse --show-toplevel 2>/dev/null || {
	echo >&2 "ERROR: You are not in git repo, not found .git/ in $PWD"
	exit 1
})

__usage__() {
	echo "
git-rm-permanent [--dry-run] <[-f file], ...>

  -f, --file [file]    specify remove file (may be listed multiple times)
  --dry-run            only dump command not execute

  --clean              clean cache, run after -f

  -h, --help           show this info

  After git-rm-permanent, you need to --clean, Then, push to each remote with

      $ git push --force --all
"
}

after_clean() {
	rm -rf ${git_topdir}/.git/refs/original/
	git reflog expire --expire=now --all
	git gc --prune=now
	git gc --aggressive --prune=now
}

__eval__() {
	if [[ ! -z ${dry_run} ]]; then
		echo "$@"
	else
		eval "$@"
	fi
}

# Start from here

ARGS=$(getopt \
	--options f:h \
	--long file: \
	--long clean \
	--long dry-run \
	--long help \
	-n git-rm-permanent -- "$@")

test $? != 0 && __usage__ 1

eval set -- "$ARGS"

while true; do
	case $1 in
	-f|--file)
		shift
		rm_files+=( $1 )
		shift
		;;
	--dry-run)
		shift
		dry_run=YES
		;;
	--clean)
		shift
		after_clean
		exit 0
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

if [[ -z "${rm_files[@]}" ]]; then
	echo "ERROR: Must specify -f, see -h"
	exit 1
fi

__eval__ \
"git filter-branch --force" \
	"--index-filter '${git_rm_cmd[@]} ${rm_files[@]}'" \
	"--prune-empty --tag-name-filter cat -- --all"
