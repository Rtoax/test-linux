#!/bin/bash
# eval return 141
# Downstream pipeline exits early, upstream write fails, then eval will return
# 141.
set -e

# TODO
eval 'for ((i=0;i<100;i++)); do echo $i; sleep 0.01; done | cat'
