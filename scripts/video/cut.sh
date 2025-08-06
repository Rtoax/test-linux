#!/bin/bash
# Copyright (c) 2025 Rong Tao
set -e

prog=$0

input_video_name=
input_video_suffix=


input_video=$1
since=$2
until=$3
output_video=$4

usage() {
	echo -e -n "
SYNOPSIS
	${prog} <INPUT VIDEO> <SINCE> <UNTIL> [OUTPUT]

EXAMPLES
	${prog} ebpf.mp4 00:01:00 01:02:01 ebpf-cut.mp4
"
}

check_input_and_get_info() {
	if [[ ! -e ${input_video} ]]; then
		usage
		echo >&2 "ERROR: input <${input_video}> is not specified or not exist."
		exit 1
	fi

	input_video_name=${input_video%.*}
	input_video_suffix=${input_video##*.}

	if [[ -z ${input_video_suffix} ]]; then
		usage
		echo >&2 "ERROR: ${input_video} don't has suffix like '.mp4'"
		exit 1
	fi
}

check_time() {
	local time=$1
	local match=$(echo $time | grep -E '[0-9]{2}:[0-9]{2}:[0-9]{2}')
	if [[ ${time} != ${match} ]]; then
		usage
		echo >&2 "ERROR: bad time format"
		exit 1
	fi
}

# main start from here

check_input_and_get_info
check_time ${since}
check_time ${until}

if [[ -z ${output_video} ]]; then
	output_video=${input_video_name}-${since}-${until}.${input_video_suffix}
	output_video=$(echo ${output_video} | tr ':' '_')
fi

# -qscale value：使用固定的视频量化标度(VBR)，以value质量为基础的VBR，取值0.01-255，越小质量越好
# -g参数设置为1表示每帧都是关键帧，即关键帧密度最大化。当然，这样做会增加视频的大小，但可以解决卡顿问题。
ffmpeg \
	-accurate_seek \
	-i ${input_video} \
	-g 1 \
	-qscale 0 \
	-avoid_negative_ts 1 \
	-vcodec copy -acodec copy \
	-ss ${since} -to ${until} \
	${output_video}

