#!/bin/bash
set -e

clang -print-targets

llvm-config --components
