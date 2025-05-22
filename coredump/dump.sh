#!/bin/bash
set -e
file=$1
coredumpctl dump $file -o output.core
