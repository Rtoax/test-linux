#!/bin/bash
set -e
source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} --seperator '-' -- $(getver2 dracut)
