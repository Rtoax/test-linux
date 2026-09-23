#!/bin/bash
# Copyright (C) 2026 Rong Tao. All rights reserved.

readonly GIT_TOPDIR=$(git rev-parse --show-toplevel 2>/dev/null || :)

declare -a try_add try_del try_modify try_rename try_all

# $1: is amend commit
git_file_status() {
	if [[ -n ${1} ]]; then
		git show --name-status --pretty=format: -M HEAD
	else
		git status --short
	fi
}

# $1: is amend commit
statistic_file_changes() {
	local is_amend=${1}

	pushd ${GIT_TOPDIR} >/dev/null
	try_add=( $(git_file_status ${is_amend} | grep ^A | awk '{print $2}' || true) )
	try_del=( $(git_file_status ${is_amend} | grep ^D | awk '{print $2}' || true) )
	try_modify=( $(git_file_status ${is_amend} | grep ^M | awk '{print $2}' || true) )
	try_rename=( $(git_file_status ${is_amend} | grep ^R | awk '{print $2}' || true) )
	try_all=( ${try_add[@]} ${try_del[@]} ${try_modify[@]} ${try_rename} )
	popd >/dev/null
}
