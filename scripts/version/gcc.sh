#!/bin/bash
# This script only display gcc version, do not display other anything,
# and don't execute failed, because the git/hooks will use it.
#
# Usage: gcc.sh [--major|--minor|--patchlevel]
#
set -e
version=$(gcc -dumpfullversion -dumpversion)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
