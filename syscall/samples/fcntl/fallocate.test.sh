#!/bin/bash
set -e

make fallocate

./fallocate

od -c falloc.dat
od -c falloc.lseek.dat
du -sh falloc.dat falloc.lseek.dat
ls -l falloc.dat falloc.lseek.dat
