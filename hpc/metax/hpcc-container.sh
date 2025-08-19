#!/bin/bash
set -ex

IMAGE=sw-harbor-lg.mxcr.io/ai-release/hpcc/modelzoo.llm.vllm:hpcc.ai2.33.1.3-torch2.6-py310-kylin2309a-arm64
#IMAGE=registry.cn-shanghai.aliyuncs.com/insight-tech/x-modelzoo.vllm:hpcc2.31.0.4-torch2.4-py310-kylin2309a-arm64
#IMAGE=registry.cn-shanghai.aliyuncs.com/insight-tech/x-deepspeed:hpcc2.32.0.5-torch2.4-py310-kylin2309a-arm64

sudo podman run --rm -ti --network=host --privileged \
	-v /home/rongtao/:/root/ ${IMAGE} \
	bash
