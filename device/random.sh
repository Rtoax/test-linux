#!/bin/bash
set -ex

od -N 32 -t x1 /dev/random
od -N 32 -t x2 /dev/random
od -An -N 32 -t x2 /dev/random
