#!/bin/bash
ld -v
[[ -e /usr/bin/rpm ]] && rpm -q binutils
