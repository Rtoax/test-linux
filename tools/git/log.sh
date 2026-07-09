#!/bin/bash
set -e
readonly LAST_TAG=$(git describe --tags --abbrev=0)

git log v2.3.16^..v2.3.17 -p ../../Makefile | cat
git log v2.4.6-Kappa..v2.4.7-Lamada --oneline | tee v2.4.6-Kappa..v2.4.7-Lamada.log
git log 6d1db619e0f2..v2.4.7-Lamada --oneline | tee 6d1db619e0f2..v2.4.7-Lamada.log
git log ${LAST_TAG}..HEAD --oneline | tee ${LAST_TAG}..HEAD.log


# Do some checks
if [[ "$(diff -up v2.4.6-Kappa..v2.4.7-Lamada.log 6d1db619e0f2..v2.4.7-Lamada.log)" ]]; then
	echo >&2 "ERROR: git log test failed"
	exit 1
fi
