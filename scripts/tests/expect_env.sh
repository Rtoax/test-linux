#!/bin/bash
set -e

if [[ "${ENV_EXPECT}" != "THISISAEXPECTENV" ]]; then
	echo "ERROR: Bad env ENV_EXPECT"
	exit 1
fi
