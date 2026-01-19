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
	libibverbs-dev \
	ffmpeg \
	libsm6 \
	libxext6 \
	libgl1
sudo pip install -r requirements/cuda.txt --break-system-packages
sudo pip install -r requirements/build.txt --break-system-packages
sudo pip install -r requirements/dev.txt --break-system-packages
