#!/bin/bash
set -e

readonly LAST_TAG=$(git describe --tags --abbrev=0)

git diff --stat --name-only HEAD^ HEAD

# Generate patch between two tags or two commits
git diff v2.4.6-Kappa v2.4.8-Memory > v2.4.6-v2.4.8.patch
git diff v2.4.6-Kappa v2.4.8-Memory ../../Makefile > v2.4.6-v2.4.8-Makefile.patch
git diff v2.4.6-Kappa f60590715b59 ../../Makefile > v2.4.6-f60590715b59-Makefile.patch
git diff cd04f2f29bb6 dcbc5cf45eb1 > os-almalinux-kylin-opencloudos.patch
git diff ${LAST_TAG} HEAD > ${LAST_TAG}-HEAD.patch

# Do some checks
if [[ "$(diff -up v2.4.6-v2.4.8-Makefile.patch v2.4.6-f60590715b59-Makefile.patch)" ]]; then
	echo >&2 "ERROR: git diff test failed"
	exit 1
fi
