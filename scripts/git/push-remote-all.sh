#!/bin/bash
set -e

readonly git_root=$(git rev-parse --show-toplevel)
readonly git_remotes=( $(git remote show) )

declare -a git_args

git_args+=( "$@" )

# Use shell name to determine push tags or not.
if [[ $0 =~ tags ]]; then
	echo "INFO: Push all tags"
	git_args+=( --tags )
fi

for remote in ${git_remotes[@]}
do
	echo -e "\033[1;32m=== Push to remote ${remote} ===\033[m"
	git push ${remote} ${git_args[@]}
done
