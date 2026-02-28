#!/bin/bash
set -e
nvidia-smi -L
nvidia-smi --list-gpus
nvidia-smi --list-excluded-gpus
