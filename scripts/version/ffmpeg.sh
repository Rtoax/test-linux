#!/bin/bash
set -e
FFMPEG=$(which ffmpeg 2>/dev/null || :)

if [[ -z ${FFMPEG} ]]; then
	echo >&2 "ERROR: not found FFMPEG in your system"
	exit 0
fi
version=$(${FFMPEG} -version | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' 2>/dev/null | head -1 || true)

source $(dirname $(realpath $0))/libversion.sh

version_parser ${@} -- ${version}
