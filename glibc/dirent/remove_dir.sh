#!/bin/bash
set -e

mkdir -p a.dir/a/b/c/d/e
touch a.dir/{a,b,c,d,e}.txt
./remove_dir
