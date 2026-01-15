#!/bin/bash
# Copyright (C) 2025-2026 Rong Tao
set -e

readonly GIT_TOPDIR=$(git rev-parse --show-toplevel 2>/dev/null || :)

# '^?' for not added new files
# '^ ' for not added modified files
files=( $(realpath $(git status --short | grep -v -e '^?' -e '^ ' | awk '{print $NF}') 2>/dev/null) )

for f in ${files[@]}
do
	echo ${f#$GIT_TOPDIR}
done
