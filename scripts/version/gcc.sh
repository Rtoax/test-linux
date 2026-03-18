#!/bin/bash
set -e
version=$(gcc -dumpfullversion -dumpversion)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
