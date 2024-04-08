#!/bin/bash
make clean
make CXX=clang++ -j$(nproc)
