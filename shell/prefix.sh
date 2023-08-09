#!/bin/bash

filename=rongtao.tar.gz

echo "${filename%%.*}"	# rongtao
echo "${filename%.*}"	# rongtao.tar
echo "${filename#*.}"	# tar.gz
echo "${filename##*.}"	# gz

