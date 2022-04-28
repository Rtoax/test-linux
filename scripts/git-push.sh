#!/bin/bash 
# 

set -euo pipefail

if [ $# -lt 1 ]; then
	echo "need commit string"
	exit 1
fi

git add --all
git status
git commit -m "$*"
if [ $? = 0 ]; then
	git push
fi

git_sync()
{
	cd .. && ./gittools sync test-linux && cd -
}

test ! -z ../gittools && git_sync
