#!/bin/bash
# see bash(1) Process Substitution
set -e

foo() {
	echo stdout
	echo >&2 stderr
}

# test 1
foo \
	2> >(tee stderr1.log) \
	> >(tee stdout1.log)

# test 2
exec 3> >(tee stdout2.log)
exec 4> >(tee stderr2.log)
foo >&3 2>&4
exec 3>&- 4>&-

if [[ "$(cat stderr1.log)" != "$(cat stderr2.log)" ]] ||
   [[ "$(cat stdout1.log)" != "$(cat stdout2.log)" ]]; then
	echo >&2 "ERROR: failed compare"
	exit 1
fi
