#!/bin/bash
set -e

filename=${PWD}/rongtao.tar.gz

printf "filename = %-16s\n" ${filename}
printf "%-16s = %-16s\n" "\${filename%%.*}" "${filename%%.*}"	# rongtao
printf "%-16s = %-16s\n" "\${filename%.*}"  "${filename%.*}"	# rongtao.tar
printf "%-16s = %-16s\n" "\${filename#*.}"  "${filename#*.}"	# tar.gz
printf "%-16s = %-16s\n" "\${filename##*.}" "${filename##*.}"	# gz
printf "%-16s = %-16s\n" "\${filename#${PWD}/}"  "${filename#${PWD}/}"	# rongtao.tar.gz
printf "%-16s = %-16s\n" "\${filename#__nonsense__}"  "${filename#__nonsense__}"	# ${filename}
