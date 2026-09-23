#!/bin/bash
# Copyright (C) 2026 Rong Tao. All rights reserved.

# $1: is amend commit
git_file_status() {
	if [[ -n ${1} ]]; then
		git show --name-status --pretty=format: -M HEAD
	else
		git status --short
	fi
}
