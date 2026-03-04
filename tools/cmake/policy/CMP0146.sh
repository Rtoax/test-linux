#!/bin/bash
set -e
# The FindCUDA module is removed, call the enable_language() command with CUDA.
cmake --help-policy CMP0146
