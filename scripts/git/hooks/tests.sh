#!/bin/bash
set -e

HAVE_CLANG_FORMAT=$(which git-clang-format 2>/dev/null || :)

if [[ -z ${HAVE_CLANG_FORMAT} ]]; then
	export FCF=1
fi

./pre-commit
