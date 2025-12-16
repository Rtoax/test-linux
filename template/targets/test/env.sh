#!/bin/bash
set -e

echo "${@}"
if [[ ${TEST_LINUX_TEMPLATE_TARGETS_SHELL_ENV} != rtoax ]]; then
	echo >&2 "ERROR: Could not found TEST_LINUX_TEMPLATE_TARGETS_SHELL_ENV"
	exit 1
fi
