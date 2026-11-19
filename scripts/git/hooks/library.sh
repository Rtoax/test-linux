#!/bin/bash
# Copyright (C) 2026 Rong Tao. All rights reserved.

readonly GIT_TOPDIR=$(git rev-parse --show-toplevel 2>/dev/null || :)

declare -a try_add try_del try_modify try_rename try_rename2 try_all

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
	try_rename2=( $(git_file_status ${is_amend} | grep ^R | awk '{print $4}' || true) )
	if [[ ${#try_rename[@]} -ne ${#try_rename2[@]} ]]; then
		echo >&2 "ERROR: git list rename files wrong"
		git_file_status >&2
		exit 1
	fi

	try_del+=( ${try_rename[@]} )
	try_add+=( ${try_rename2[@]} )

	try_all=( ${try_add[@]} ${try_del[@]} ${try_modify[@]} ${try_rename[@]} ${try_rename2[@]})
	popd >/dev/null
}

test_linux_docs_check() {
	if [[ ! -d ${GIT_TOPDIR}/Documentation ]]; then
		return 0
	fi

	# Detect documentation changed
	if [[ " ${try_all[@]} " =~ "Documentation" ]]; then
		# Not found version field is changed.
		if [[ ! " ${try_modify[@]} " =~ " Documentation/conf.py " ]] ||
		   [[ "$(git diff --staged ${GIT_TOPDIR}/Documentation/conf.py | \
				grep -o ^+version)" != "+version" ]]; then
			fatal "You need to change doc version in Documentation/conf.py"
		fi
	fi

	local f
	for f in README.md abbrev.md history.md
	do
		# no need try_rename[] here.
		if [[ " ${try_modify[@]} " =~ "${f}" ]] ||
		   [[ " ${try_add[@]} " =~ "${f}" ]]; then
			fatal "Don't modify/add ${f}, please move it to Documentation!"
		fi
	done

	if [[ "${try_all[@]}" =~ "abbrev" ]]; then
		${GIT_TOPDIR}/Documentation/abbrev.sh --check
	fi
}

test_linux_template_check() {
	local tests_mk=${GIT_TOPDIR}/template/tests.mk

	if [[ ! -d ${GIT_TOPDIR}/template ]]; then
		return 0
	fi

	# template was not changed.
	if ! [[ " ${try_all[@]} " =~ " template/" ]]; then
		return 0
	fi

	if ! [[ " ${try_modify[@]} " =~ " template/VERSION " ]]; then
		fatal "Forgot modify template/VERSION"
	fi

	if [[ " ${try_add[@]}" =~ " template/" ]]; then
		for orig_mk in ${try_add[@]}
		do
			if [[ ${orig_mk##*.} != mk ]]; then
				continue
			fi

			if [[ "${orig_mk} " =~ "Build.mk " ]] ||
			   [[ "${orig_mk} " =~ "Target.mk " ]]; then
				continue
			fi

			mk=$(echo ${orig_mk} | sed 's/^template\///g')

			# test all makefiles in tests.mk
			if ! grep -q "^include ${mk}" ${tests_mk}; then
				fatal "${orig_mk} is not included in ${tests_mk}"
			fi
		done
	fi

	if [[ " ${try_del[@]}" =~ " template/" ]]; then
		for orig_mk in ${try_del[@]}
		do
			if [[ ${orig_mk##*.} != mk ]]; then
				continue
			fi

			mk=$(echo ${orig_mk} | sed 's/^template\///g')

			# Need remove make from tests.mk
			if grep -q "^include ${mk}" ${tests_mk}; then
				fatal "'${orig_mk}' is removing, need remove from '${tests_mk}' too"
			fi
		done
	fi
}
