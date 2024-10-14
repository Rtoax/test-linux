#!/bin/bash
set -e

make R_X86_64_JUMP_SLOT

readelf -rW R_X86_64_JUMP_SLOT | grep R_X86_64_JUMP_SLOT -B 2
objdump -d --section=.got.plt R_X86_64_JUMP_SLOT
