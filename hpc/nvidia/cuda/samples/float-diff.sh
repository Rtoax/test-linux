#!/bin/bash
set -e

GPU_EXE=float

if which ls-smi; then
	GPU_EXE=float-luca
fi

sudo ./float-c nocolor ${@} > float-cpu.log
sudo ./${GPU_EXE} nocolor ${@} > float-gpu.log

diff -up float-gpu.log float-cpu.log
