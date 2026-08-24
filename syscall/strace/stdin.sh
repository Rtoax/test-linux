#!/bin/bash
set -e

stdin=$(strace ls Build.mk 2>ls.stderr.log)
if [[ "${stdin}" != Build.mk ]]; then
	exit 1
fi

strace ls Build.mk >ls.stdout.log 2>&1
