#!/bin/bash
set -e
version=$(llvm-config --version 2>/dev/null || {
	llvm-objdump --version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null
	}
)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
