#!/bin/bash
# ref: https://build.nvidia.com/spark/vllm/instructions
set -e

# sudo podman commit vllm-rt nvcr.io/nvidia/vllm:25.11-py3-rt
# sudo podman run ... vllm serve "Qwen/Qwen2.5-Math-1.5B-Instruct"
sudo docker run --rm -ti --privileged \
	--name vllm-rt \
	-v /dev:/dev \
	-v /etc/apt/sources.list.d/:/etc/apt/sources.list.d/ \
	--network host \
	--gpus all -p 8000:8000 \
	nvcr.io/nvidia/vllm:25.11-py3-rt bash
