#!/bin/bash
strace -e trace=clone,clone3 "$@"
