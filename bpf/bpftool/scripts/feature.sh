#!/bin/bash
set -ex

sudo bpftool feature
bpftool feature list_builtins prog_types
bpftool feature list_builtins map_types
