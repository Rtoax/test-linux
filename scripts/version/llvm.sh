#!/bin/bash
# This script only display LLVM version, do not display other anything,
# because the git/hooks will use it.
set -e
version=$(llvm-config --version 2>/dev/null || {
	llvm-objdump --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null
	}
)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
