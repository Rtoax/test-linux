#!/bin/bash
strace -e trace=fork,vfork "$@"
