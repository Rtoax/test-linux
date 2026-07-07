#!/bin/bash
# https://git-scm.com/docs/githooks
set -e

# Skip if none git
if [[ -z "$(which git)" ]] ||
   [[ -z "$(git rev-parse --show-toplevel 2>/dev/null)" ]]; then
	exit 0
fi

git config core.hooksPath scripts/git/hooks/ 2>/dev/null
# This script called in top Makefile, need this 'get'.
git config get core.hooksPath 2>/dev/null || {
	# git version compat
	git config core.hooksPath 2>/dev/null
}
