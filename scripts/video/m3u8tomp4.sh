#!/bin/bash
# https://windowsloop.com/download-m3u8-video-with-ffmpeg/
#

url=$1
star=$2

usage() {
	echo >&2 "Usage: m3u8tomp4 <URL> [STAR]"
}

if [[ -z ${url} ]]; then
	usage
	echo >&2 "ERROR: need URL"
	exit 1
fi

ffmpeg -i ${url} -c copy -bsf:a aac_adtstoasc $(date '+%Y%m%d_%H%M%S')${star:+-star${star}}.mp4

