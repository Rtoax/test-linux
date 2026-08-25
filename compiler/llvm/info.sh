#!/bin/bash
set -e

# or: clang --print-targets
clang -print-targets

llvm-config --components
