#!/bin/bash
# see vllm::docker/Dockerfile
set -e

sudo pip install -r requirements/cuda.txt --break-system-packages

