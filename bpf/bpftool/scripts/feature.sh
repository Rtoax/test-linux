#!/bin/bash
set -ex

BPFTOOL=$1
[[ -z ${BPFTOOL} ]] && BPFTOOL=bpftool

sudo ${BPFTOOL} feature
sudo ${BPFTOOL} feature probe
sudo ${BPFTOOL} feature list_builtins prog_types
sudo ${BPFTOOL} feature list_builtins map_types
