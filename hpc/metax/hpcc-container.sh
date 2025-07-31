#!/bin/bash
set -ex

IMAGE=registry.cn-shanghai.aliyuncs.com/insight-tech/x-deepspeed:hpcc2.32.0.5-torch2.4-py310-kylin2309a-arm64

sudo podman run --rm -ti --network=host --privileged \
	-v /home/rongtao/Git/tst-linux/:/root/Git/tst-linux \
	bash
