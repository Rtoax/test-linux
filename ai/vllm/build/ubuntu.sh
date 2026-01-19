#!/bin/bash
# see vllm::docker/Dockerfile
set -e

sudo apt update -y
sudo apt install -y --no-install-recommends \
	ccache \
	software-properties-common \
	git \
	curl \
	sudo \
	python3-pip \
	libibverbs-dev
sudo pip install -r requirements/cuda.txt --break-system-packages
