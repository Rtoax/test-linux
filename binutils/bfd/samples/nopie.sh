#!/bin/bash
make clean
make NOPIE=1 "$@"
