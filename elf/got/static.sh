#!/bin/bash
make clean
make STATIC=1 "$@"
