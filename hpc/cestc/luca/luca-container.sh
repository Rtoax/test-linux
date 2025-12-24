#!/bin/bash
set -ex

IMAGE=image.cestc.cn/luca/megatron-lm:v1-arm64

sudo podman run --rm -ti --network=host --privileged \
	-v /home/rongtao/:/root/ \
	-v /home/g/:/root/g/ \
	${IMAGE} \
	bash
