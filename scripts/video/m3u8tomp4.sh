#!/bin/bash
# Copyright (C) 2025-2026 Rong Tao. All rights reserved.
# https://windowsloop.com/download-m3u8-video-with-ffmpeg/
#
# Google Chrome Procedures for none-TLS m3u8:
# 1. Click-Right
# 2. Inspect
# 3. Network -> [Search-m3u8]
# 4. Click-Right -> [Copy URL]
# 5. ./m3u8tomp4.sh URL [Star]
#
set -ex

url="$1"
star=$2

usage() {
	echo >&2 "Usage: m3u8tomp4 <URL> [STAR]"
}

if [[ -z ${url} ]]; then
	usage
	echo >&2 "ERROR: need URL"
	exit 1
fi

output_file="$(date '+%Y%m%d_%H%M%S')${star:+-star${star}}.mp4"

url_last_m3u8_basename="$(basename ${url} || true)"
url_last_m3u8_basename_match="$(echo ${url_last_m3u8_basename} | grep -E '^[-_|a-zA-Z0-9]+\.[-_|a-zA-Z0-9]+' || true)"
if [[ "${url_last_m3u8_basename}" == "${url_last_m3u8_basename_match}" ]]; then
	output_file=${url_last_m3u8_basename}${star:+-star${star}}.mp4
fi

url_inner_m3u8_basename="$(echo ${url} | grep -Eo '[a-zA-Z0-9]+\.m3u8')"
if [[ "${url_inner_m3u8_basename}" ]]; then
	output_file="${url_inner_m3u8_basename}.mp4"
fi

ffmpeg -i "${url}" -c copy -bsf:a aac_adtstoasc ${output_file}
