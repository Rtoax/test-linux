#!/bin/bash
set -e
source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- $(getver2 gdb)
